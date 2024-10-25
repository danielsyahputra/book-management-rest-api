#ifndef ConfigDto_hpp
#define ConfigDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigDto : public oatpp::DTO {
    DTO_INIT(ConfigDto, DTO)

    DTO_FIELD(UInt16, port) = 9999;
    DTO_FIELD(String, host) = "localhost";

};

#include OATPP_CODEGEN_END(DTO)

#endif