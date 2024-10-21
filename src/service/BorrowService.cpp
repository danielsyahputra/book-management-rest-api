#include "BorrowService.hpp"

oatpp::Object<BorrowDto> BorrowService::createBorrow(const oatpp::Object<BorrowDto>& dto) {
    auto dbResult = database->createBorrow(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto borrowId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());
    return getBorrowById((v_int32) borrowId);
}

oatpp::Object<BorrowDto> BorrowService::updateBorrow(const oatpp::Object<BorrowDto>& dto) {
    auto dbResult = database->updateBorrow(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getBorrowById(dto->id);
}

oatpp::Object<BorrowDto> BorrowService::getBorrowById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {
    auto dbResult = database->getBorrowById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Borrow record not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<BorrowDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
    return result[0];
}

oatpp::Object<PageDto<oatpp::Object<BorrowDto>>> BorrowService::getAllBorrows(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = database->getAllBorrows(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<BorrowDto>>>();

    auto page = PageDto<oatpp::Object<BorrowDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDto> BorrowService::deleteBorrowById(const oatpp::Int32& borrowId) {
    auto dbResult = database->deleteBorrowById(borrowId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Borrow record was successfully deleted";
    return status;
}

oatpp::Object<PageDto<oatpp::Object<BorrowDto>>> BorrowService::getBorrowsByUserId(const oatpp::Int32& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = database->getBorrowsByUserId(userId, offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<BorrowDto>>>();

    auto page = PageDto<oatpp::Object<BorrowDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<PageDto<oatpp::Object<BorrowDto>>> BorrowService::getBorrowsByBookId(const oatpp::Int32& bookId, const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if (limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = database->getBorrowsByBookId(bookId, offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<BorrowDto>>>();

    auto page = PageDto<oatpp::Object<BorrowDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}