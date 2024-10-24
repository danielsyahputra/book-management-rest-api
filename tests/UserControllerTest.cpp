#include "UserControllerTest.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"

#include "controller/UserController.hpp"

#include "app/TestClient.hpp"
#include "app/TestComponent.hpp"

#include <cstdio>
#include <iostream>

void UserControllerTest::onRun() {
    OATPP_LOGi(TAG, "DB-File='{}'", TESTDATABASE_FILE);

    std::remove(TESTDATABASE_FILE);

    TestComponent component;

    oatpp::test::web::ClientServerTestRunner runner;

    runner.addController(std::make_shared<UserController>());

    runner.run([this, &runner] {

        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers);

        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        auto client = TestClient::createShared(requestExecutor,
                                                contentMappers->getMapper("application/json"));

        auto dto = UserDto::createShared();

        dto->userName = "danielsyahputra";
        dto->email = "dnlshp@gmail.com";
        dto->password = "password";

        auto addedUserResponse = client->createUser(dto);

        OATPP_ASSERT(addedUserResponse->getStatusCode() == 200);

        auto addedUserDto = addedUserResponse->readBodyToDto<oatpp::Object<UserDto>>(
            contentMappers->selectMapperForContent(addedUserResponse->getHeader("Content-Type"))
        );

        int addedUserId = addedUserDto->id;

        auto newUserResponse = client->getUserById(addedUserId);

        OATPP_ASSERT(newUserResponse->getStatusCode() == 200);

        auto newUserDto = newUserResponse->readBodyToDto<oatpp::Object<UserDto>>(
            contentMappers->selectMapperForContent(addedUserResponse->getHeader("Content-Type"))
        );

        OATPP_ASSERT(newUserDto->id == addedUserId);

        auto deletedUserResponse = client->deleteUserById(addedUserId);

        OATPP_ASSERT(deletedUserResponse->getStatusCode() == 200);

        }, std::chrono::minutes(10)
    );

    /* wait all server threads finished */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* stop db connection pool */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider);
    dbConnectionProvider->stop();

}