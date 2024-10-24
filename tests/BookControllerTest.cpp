#include "BookControllerTest.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"

#include "controller/BookController.hpp"

#include "app/TestClient.hpp"
#include "app/TestComponent.hpp"

#include <cstdio>
#include <iostream>

void BookControllerTest::onRun() {
    OATPP_LOGi(TAG, "DB-File='{}'", TESTDATABASE_FILE);

    std::remove(TESTDATABASE_FILE);

    TestComponent component;

    oatpp::test::web::ClientServerTestRunner runner;

    runner.addController(std::make_shared<BookController>());

    runner.run([this, &runner] {

        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers);

        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        auto client = TestClient::createShared(requestExecutor,
                                                contentMappers->getMapper("application/json"));
        
        auto dtoBook1 = BookDto::createShared();
        dtoBook1->title = "Book2";
        dtoBook1->author = "Daniel";
        dtoBook1->publishedDate = "2024-10-24";
        dtoBook1->description = "This is Book2";
        dtoBook1->isAvailable = 1;

        auto addedBookResponse1 = client->createBook(dtoBook1);
        OATPP_ASSERT(addedBookResponse1->getStatusCode() == 200);

        auto addedBookDto1 = addedBookResponse1->readBodyToDto<oatpp::Object<BookDto>>(
            contentMappers->selectMapperForContent(addedBookResponse1->getHeader("Content-Type"))
        );

        // Check if the new book is already inserted
        int addedBookId1 = addedBookDto1->id;
        auto newBookResponse = client->getBookById(addedBookId1);
        OATPP_ASSERT(newBookResponse->getStatusCode() == 200);
        auto newBookDto = newBookResponse->readBodyToDto<oatpp::Object<BookDto>>(
            contentMappers->selectMapperForContent(newBookResponse->getHeader("Content-Type"))
        );
        OATPP_ASSERT(newBookDto->id == addedBookId1);

        auto allBookResponse1 = client->getAllBooks(0, 10);
        OATPP_ASSERT(allBookResponse1->getStatusCode() == 200);
        auto allBookDto1 = allBookResponse1->readBodyToDto<oatpp::Object<BooksPageDto>>(
            contentMappers->selectMapperForContent(allBookResponse1->getHeader("Content-Type"))
        );
        OATPP_ASSERT(allBookDto1->count == 2);

        // Delete
        auto deletedBookResponse = client->deleteBookById(addedBookId1);
        OATPP_ASSERT(deletedBookResponse->getStatusCode() == 200);
        auto allBookResponse2 = client->getAllBooks(0, 10);
        OATPP_ASSERT(allBookResponse2->getStatusCode() == 200);
        auto allBookDto2 = allBookResponse2->readBodyToDto<oatpp::Object<BooksPageDto>>(
            contentMappers->selectMapperForContent(allBookResponse2->getHeader("Content-Type"))
        );
        OATPP_ASSERT(allBookDto2->count == 1);

        }, std::chrono::minutes(10)
    );

    /* wait all server threads finished */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* stop db connection pool */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider);
    dbConnectionProvider->stop();
}