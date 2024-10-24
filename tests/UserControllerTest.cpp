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

        /*
        First scneario: add the first user and check if the user inserted is trully the same as what I inserted before.
        */
        auto dto1 = UserDto::createShared();

        dto1->userName = "danielsyahputra";
        dto1->email = "dnlshp@gmail.com";
        dto1->password = "password";

        auto addedUserResponse1 = client->createUser(dto1);

        OATPP_ASSERT(addedUserResponse1->getStatusCode() == 200);

        auto addedUserDto1 = addedUserResponse1->readBodyToDto<oatpp::Object<UserDto>>(
            contentMappers->selectMapperForContent(addedUserResponse1->getHeader("Content-Type"))
        );

        OATPP_ASSERT(addedUserDto1->userName == dto1->userName);
        OATPP_ASSERT(addedUserDto1->email == dto1->email);

        /*
        Second scenario scneario: add the second user
        */
        auto dto2 = UserDto::createShared();
        dto2->userName = "testuser";
        dto2->email = "test@gmail.com";
        dto2->password = "password";

        auto addedUserResponse2 = client->createUser(dto2);

        OATPP_ASSERT(addedUserResponse1->getStatusCode() == 200);

        auto addedUserDto2 = addedUserResponse2->readBodyToDto<oatpp::Object<UserDto>>(
            contentMappers->selectMapperForContent(addedUserResponse2->getHeader("Content-Type"))
        );

        OATPP_ASSERT(addedUserDto2->userName == dto2->userName);
        OATPP_ASSERT(addedUserDto2->email == dto2->email);

        /*
        Check if the new user is already inserted
        */
        int addedUserId1 = addedUserDto1->id;

        auto newUserResponse = client->getUserById(addedUserId1);

        OATPP_ASSERT(newUserResponse->getStatusCode() == 200);

        auto newUserDto = newUserResponse->readBodyToDto<oatpp::Object<UserDto>>(
            contentMappers->selectMapperForContent(addedUserResponse1->getHeader("Content-Type"))
        );

        OATPP_ASSERT(newUserDto->id == addedUserId1);


        /*Check if the total count users is trully 2.
        */
        auto allUsersResponse1 = client->getAllUsers(0, 10);
        OATPP_ASSERT(allUsersResponse1->getStatusCode() == 200);

        auto allUsersDto1 = allUsersResponse1->readBodyToDto<oatpp::Object<UsersPageDto>>(
            contentMappers->selectMapperForContent(allUsersResponse1->getHeader("Content-Type"))
        );
        OATPP_ASSERT(allUsersDto1->count == 3);


        /*Delete one user and check if the total user now is exactly one.
        */
        auto deletedUserResponse = client->deleteUserById(addedUserId1);

        OATPP_ASSERT(deletedUserResponse->getStatusCode() == 200);

        auto allUsersResponse2 = client->getAllUsers(0, 10);
        OATPP_ASSERT(allUsersResponse2->getStatusCode() == 200);

        auto allUsersDto2 = allUsersResponse2->readBodyToDto<oatpp::Object<UsersPageDto>>(
            contentMappers->selectMapperForContent(allUsersResponse2->getHeader("Content-Type"))
        );

        OATPP_ASSERT(allUsersDto2->count == 2);

        }, std::chrono::minutes(10)
    );

    /* wait all server threads finished */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* stop db connection pool */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider);
    dbConnectionProvider->stop();

}