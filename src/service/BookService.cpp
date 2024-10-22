#include "BookService.hpp"

oatpp::Object<BookDto> BookService::createBook(const oatpp::Object<BookDto>& dto) {

    auto dbResult = database->createBook(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto bookId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getBookById((v_int32) bookId);

}

oatpp::Object<BookDto> BookService::updateBook(const oatpp::Object<BookDto>& dto) {

    auto dbResult = database->updateBook(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getBookById(dto->id);

}

oatpp::Object<BookDto> BookService::getBookById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {
    
    auto dbResult = database->getBookById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Book not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<BookDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Object<PageDto<oatpp::Object<BookDto>>> BookService::getAllBooks(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

    oatpp::UInt32 countToFetch = limit;

    if(limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = database->getAllBooks(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<BookDto>>>();

    auto page = PageDto<oatpp::Object<BookDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;

}

oatpp::Object<StatusDto> BookService::deleteBookById(const oatpp::Int32& bookId) {
    auto dbResult = database->deleteBookById(bookId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Book was successfully deleted";
    return status;
}