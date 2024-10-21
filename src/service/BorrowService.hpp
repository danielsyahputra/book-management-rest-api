#ifndef CRUD_BORROWSERVICE_HPP
#define CRUD_BORROWSERVICE_HPP

#include "db/BorrowDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/macro/component.hpp"

class BorrowService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<BorrowDb>, database);
public:
    oatpp::Object<BorrowDto> createBorrow(const oatpp::Object<BorrowDto>& dto);
    oatpp::Object<BorrowDto> updateBorrow(const oatpp::Object<BorrowDto>& dto);
    oatpp::Object<BorrowDto> getBorrowById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
    oatpp::Object<PageDto<oatpp::Object<BorrowDto>>> getAllBorrows(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDto> deleteBorrowById(const oatpp::Int32& id);
    oatpp::Object<PageDto<oatpp::Object<BorrowDto>>> getBorrowsByUserId(const oatpp::Int32& userId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<PageDto<oatpp::Object<BorrowDto>>> getBorrowsByBookId(const oatpp::Int32& bookId, const oatpp::UInt32& offset, const oatpp::UInt32& limit);
};

#endif