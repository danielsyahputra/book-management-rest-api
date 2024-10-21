#ifndef BookDto_hpp
#define BookDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDto : public oatpp::DTO {
    DTO_INIT(BookDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, title, "title");
    DTO_FIELD(String, author, "author");
    DTO_FIELD(String, publishedDate, "publishedDate");
    DTO_FIELD(String, description, "description");
    DTO_FIELD(Boolean, isAvailable, "isAvailable");
};

#include OATPP_CODEGEN_END(DTO)

#endif