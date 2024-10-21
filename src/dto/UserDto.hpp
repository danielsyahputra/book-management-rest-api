#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

Enum(Role, v_int32,
    Value(GUEST, 0, "Guest"),
    Value(ADMIN, 1, "ADMIN")
)

class UserDto: public oatpp::DTO {
    DTO_INIT(UserDto, DTO)
    DTO_FIELD(Int32, id);
    DTO_FIELD(String, username, "username");
    DTO_FIELD(String, email, "email");
    DTO_FIELD(String, password, "password");
    DTO_FIELD(Enum<Role>::AsString, role, "role");
};

#include OATPP_CODEGEN_END(DTO)

#endif