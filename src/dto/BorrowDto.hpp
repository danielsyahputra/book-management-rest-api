#ifndef BorrowDto_hpp
#define BorrowDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"
#include "UserDto.hpp"
#include "BookDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BorrowDto: public oatpp::DTO {
    DTO_INIT(BorrowDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(Int32, userId, "userId");
    DTO_FIELD(Int32, bookId, "bookId");
    DTO_FIELD(String, borrowDate, "borrowDate");
    DTO_FIELD(String, returnDate, "returnDate");
};

#include OATPP_CODEGEN_END(DTO)

#endif