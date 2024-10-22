#ifndef CRUD_DATABASECOMPONENT_HPP
#define CRUD_DATABASECOMPONENT_HPP

#include "db/UserDb.hpp"
#include "db/BookDb.hpp"
#include "db/BorrowDb.hpp"

class DatabaseComponent {
public:

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([] {
        try {
            OATPP_LOGd("DatabaseComponent", "Initializing connection provider with db file: %s", DATABASE_FILE);
            auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);
            
            auto connection = connectionProvider->get();
            if (!connection) {
                OATPP_LOGe("DatabaseComponent", "Failed to establish initial database connection");
                throw std::runtime_error("Failed to establish database connection");
            }
            
            OATPP_LOGd("DatabaseComponent", "Creating connection pool");
            return oatpp::sqlite::ConnectionPool::createShared(connectionProvider, 
                                                             10,  // max connections 
                                                             std::chrono::seconds(5));  // connection lifetime
        } catch (const std::exception& e) {
            OATPP_LOGe("DatabaseComponent", "Failed to create connection provider: %s", e.what());
            throw;
        }
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {
        try {
            OATPP_LOGd("DatabaseComponent", "Initializing UserDb");
            
            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);
            
            auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);
            
            /* Create UserDb */
            auto db = std::make_shared<UserDb>(executor);
            OATPP_LOGd("DatabaseComponent", "UserDb initialized successfully");
            return db;
        } catch (const std::exception& e) {
            OATPP_LOGe("DatabaseComponent", "Failed to create UserDb: %s", e.what());
            throw;
        }
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<BookDb>, bookDb)([] {
        try {
            OATPP_LOGd("DatabaseComponent", "Initializing BookDb");
            
            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);
            
            auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);
            
            auto db = std::make_shared<BookDb>(executor);
            OATPP_LOGd("DatabaseComponent", "BookDb initialized successfully");
            return db;
        } catch (const std::exception& e) {
            OATPP_LOGe("DatabaseComponent", "Failed to create BookDb: %s", e.what());
            throw;
        }
    }());


    OATPP_CREATE_COMPONENT(std::shared_ptr<BorrowDb>, borrowDb)([] {
        try {
            OATPP_LOGd("DatabaseComponent", "Initializing BorrowDb");
            
            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);
            
            auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);
            
            auto db = std::make_shared<BorrowDb>(executor);
            OATPP_LOGd("DatabaseComponent", "BorrowDb initialized successfully");
            return db;
        } catch (const std::exception& e) {
            OATPP_LOGe("DatabaseComponent", "Failed to create BorrowDb: %s", e.what());
            throw;
        }
    }());

public:

    DatabaseComponent() {
        OATPP_LOGd("DatabaseComponent", "Checking database initialization...");
        try {
            OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);
            OATPP_COMPONENT(std::shared_ptr<UserDb>, userDb);
            OATPP_COMPONENT(std::shared_ptr<BookDb>, bookDb);
            OATPP_COMPONENT(std::shared_ptr<BorrowDb>, borrowDb);
            
            OATPP_LOGd("DatabaseComponent", "All database components initialized successfully");
        } catch (const std::exception& e) {
            OATPP_LOGe("DatabaseComponent", "Database initialization failed: %s", e.what());
            throw;
        }
    }
};

#endif