#ifndef TEST_DATABASECOMPONENT_HPP
#define TEST_DATABASECOMPONENT_HPP

#include "db/UserDb.hpp"
#include "db/BookDb.hpp"
#include "db/BorrowDb.hpp"

class TestDatabaseComponent {
    public:
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([] {
            auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(TESTDATABASE_FILE);
            return oatpp::sqlite::ConnectionPool::createShared(connectionProvider, 10, std::chrono::seconds(5));
        }());

        OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {

            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

            auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

            return std::make_shared<UserDb>(executor);

        }());

        OATPP_CREATE_COMPONENT(std::shared_ptr<BookDb>, bookDb)([] {

            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

            auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

            return std::make_shared<BookDb>(executor);

        }());

        OATPP_CREATE_COMPONENT(std::shared_ptr<BorrowDb>, borrowDb)([] {

            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

            auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

            return std::make_shared<BorrowDb>(executor);

        }());
};

#endif