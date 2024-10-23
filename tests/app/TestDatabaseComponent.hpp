#ifndef TEST_DATABASECOMPONENT_HPP
#define TEST_DATABASECOMPONENT_HPP

#include "db/UserDb.hpp"

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
};

#endif