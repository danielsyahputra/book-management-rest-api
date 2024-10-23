#ifndef DatabaseTestClient_hpp
#define DatabaseTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/macro/codegen.hpp"

#include "dto/UserDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class TestClient: public oatpp::web::client::ApiClient {
    API_CLIENT_INIT(TestClient)

    /*
    UserController
    */
    API_CALL("POST", "/users", createUser, BODY_DTO(Object<UserDto>, userDto))
    API_CALL("GET", "/users/{userId}", getUserById, PATH(Int32, userId))
    API_CALL("PUT", "/users/{userId}", updateUser,
            PATH(Int32, userId),
            BODY_DTO(Object<UserDto>, userDto))
    API_CALL("GET", "/users/offset/{offset}/limit/{limit}", getAllUsers,
            PATH(Int32, offset),
            PATH(Int32, limit))
    API_CALL("DELETE", "/users/{userId}", deleteUserById, PATH(Int32, userId))

};

#include OATPP_CODEGEN_END(ApiClient)

#endif