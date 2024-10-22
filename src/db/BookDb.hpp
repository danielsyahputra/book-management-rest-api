#ifndef CRUD_BOOKDB_HPP
#define CRUD_BOOKDB_HPP

#include "dto/BookDto.hpp"
#include "oatpp-sqlite/orm.hpp"
#include "oatpp/base/Log.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class BookDb: public oatpp::orm::DbClient {
    public:
        BookDb(const std::shared_ptr<oatpp::orm::Executor>& executor): oatpp::orm::DbClient(executor) {
            oatpp::orm::SchemaMigration migration(executor);
            OATPP_LOGd("BookDB", "Migration file path: {}", DATABASE_MIGRATIONS "/002_init.sql");
            migration.addFile(1, DATABASE_MIGRATIONS "/002_init.sql");
            migration.migrate();

            auto version = executor->getSchemaVersion();
            OATPP_LOGd("BookDB", "Migration - OK. Version={}", version);
        }

        QUERY(createBook,
            "INSERT INTO Book"
            "(title, author, publishedDate, description, isAvailable) VALUES "
            "(:book.title, :book.author, :book.publishedDate, :book.description, :book.isAvailable);",
            PARAM(oatpp::Object<BookDto>, book)
        )

        QUERY(updateBook,
            "UPDATE Book SET "
            "title = :book.title, "
            "author = :book.author, "
            "publishedData = :book.publishedDate, "
            "description = :book.description, "
            "isAvailable = :book.isAvailable "
            "WHERE id = :book.id;",
            PARAM(oatpp::Object<BookDto>, book)
        )

        QUERY(getBookById,
            "SELECT * FROM Book WHERE id = :id;",
            PARAM(oatpp::Int32, id))

        QUERY(getAllBooks,
            "SELECT * FROM Book LIMIT :limit OFFSET :offset;",
            PARAM(oatpp::UInt32, offset),
            PARAM(oatpp::UInt32, limit))

        QUERY(deleteBookById,
            "DELETE FROM Book WHERE id = :id;",
            PARAM(oatpp::Int32, id))
};

#include OATPP_CODEGEN_END(DbClient)

#endif