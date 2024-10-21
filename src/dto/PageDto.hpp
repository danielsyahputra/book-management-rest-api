#ifndef CRUD_PAGEDTO_HPP
#define CRUD_PAGEDTO_HPP

#include "UserDto.hpp"
#include "BookDto.hpp"
#include "BorrowDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto: public oatpp::DTO {
    DTO_INIT(PageDto, DTO)

    DTO_FIELD(UInt32, offset);
    DTO_FIELD(UInt32, limit);
    DTO_FIELD(UInt32, count);
    DTO_FIELD(Vector<T>, items);
};

class UsersPageDto: public PageDto<oatpp::Object<UserDto>> {
    DTO_INIT(UsersPageDto, PageDto<oatpp::Object<UserDto>>)
};

class BooksPageDto: public PageDto<oatpp::Object<BookDto>> {
    DTO_INIT(BooksPageDto, PageDto<oatpp::Object<BookDto>>)
};

class BorrowsPageDto: public PageDto<oatpp::Object<BorrowDto>> {
    DTO_INIT(BorrowsPageDto, PageDto<oatpp::Object<BorrowDto>>)
};

#include OATPP_CODEGEN_END(DTO)
#endif