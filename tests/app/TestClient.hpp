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

    /*
    BookController
    */
    API_CALL("POST", "/books", createBook, BODY_DTO(Object<BookDto>, bookDto))
    API_CALL("GET", "/books/{bookId}", getBookById, PATH(Int32, bookId))
    API_CALL("PUT", "/books/{bookId}", updateBook, 
        PATH(Int32, bookId),
        BODY_DTO(Object<BookDto>, bookDto))
    API_CALL("GET", "/books/offset/{offset}/limit/{limit}", getAllBooks,
        PATH(Int32, offset),
        PATH(Int32, limit))
    API_CALL("DELETE", "/books/{bookId}", deleteBookById, PATH(Int32, bookId))

    /*
    BorrowController
    */
    API_CALL("POST", "/borrows", createBorrow, BODY_DTO(Object<BookDto>, bookDto))
    API_CALL("GET", "/borrows/{borrowId}", getBorrowById, PATH(Int32, borrowId))
    API_CALL("PUT", "/borrows/{borrowId}", updateBorrow, 
        PATH(Int32, borrowId),
        BODY_DTO(Object<BorrowDto>, borrowDto))
    API_CALL("GET", "/borrows/offset/{offset}/limit/{limit}", getAllBorrows,
        PATH(Int32, offset),
        PATH(Int32, limit))
    API_CALL("DELETE", "/borrows/{borrowId}", deleteBorrowById, PATH(Int32, borrowId))
    API_CALL("GET", "/borrows/{userId}/offset/{offset}/limit/{limit}", getBorrowsByUserId,
        PATH(Int32, userId),
        PATH(Int32, offset),
        PATH(Int32, limit))
    API_CALL("GET", "/borrows/{bookId}/offset/{offset}/limit/{limit}", getBorrowsByBookId,
        PATH(Int32, bookId),
        PATH(Int32, offset),
        PATH(Int32, limit))

};

#include OATPP_CODEGEN_END(ApiClient)

#endif