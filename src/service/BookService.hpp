#ifndef CRUD_BOOKSERVICE_HPP
#define CRUD_BOOKSERVICE_HPP

#include "db/BookDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/macro/component.hpp"

class BookService {
    private:
        typedef oatpp::web::protocol::http::Status Status;
    private:
        OATPP_COMPONENT(std::shared_ptr<BookDb>, database);
    public:
        oatpp::Object<BookDto> createBook(const oatpp::Object<BookDto>& dto);
        oatpp::Object<BookDto> updateBook(const oatpp::Object<BookDto>& dto);
        oatpp::Object<BookDto> getBookById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
        oatpp::Object<PageDto<oatpp::Object<BookDto>>> getAllBooks(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
        oatpp::Object<StatusDto> deleteBookById(const oatpp::Int32& id);
}

#endif