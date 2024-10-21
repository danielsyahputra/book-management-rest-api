#ifndef CRUD_BORROWDB_HPP
#define CRUD_BORROWDB_HPP

#include "dto/BorrowDto.hpp"
#include "oatpp-sqlite/orm.hpp"
#include "oatpp/base/Log.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class BorrowDb : public oatpp::orm::DbClient {
public:
    BorrowDb(const std::shared_ptr<oatpp::orm::Executor>& executor) : oatpp::orm::DbClient(executor) {
        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(3, DATABASE_MIGRATIONS "/003_borrow.sql");
        migration.migrate();

        auto version = executor->getSchemaVersion();
        OATPP_LOGd("BorrowDB", "Migration - OK. Version={}", version);
    }

    QUERY(createBorrow,
          "INSERT INTO Borrow "
          "(userId, bookId, borrowDate, returnDate) VALUES "
          "(:borrow.userId, :borrow.bookId, :borrow.borrowDate, :borrow.returnDate);",
          PARAM(oatpp::Object<BorrowDto>, borrow))

    QUERY(updateBorrow,
          "UPDATE Borrow SET "
          "userId = :borrow.userId, "
          "bookId = :borrow.bookId, "
          "borrowDate = :borrow.borrowDate, "
          "returnDate = :borrow.returnDate "
          "WHERE id = :borrow.id;",
          PARAM(oatpp::Object<BorrowDto>, borrow))

    QUERY(getBorrowById,
          "SELECT * FROM Borrow WHERE id = :id;",
          PARAM(oatpp::Int32, id))

    QUERY(getAllBorrows,
          "SELECT * FROM Borrow LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(deleteBorrowById,
          "DELETE FROM Borrow WHERE id = :id;",
          PARAM(oatpp::Int32, id))

    QUERY(getBorrowsByUserId,
          "SELECT * FROM Borrow WHERE userId = :userId LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::Int32, userId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(getBorrowsByBookId,
          "SELECT * FROM Borrow WHERE bookId = :bookId LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::Int32, bookId),
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))
};

#include OATPP_CODEGEN_END(DbClient)

#endif