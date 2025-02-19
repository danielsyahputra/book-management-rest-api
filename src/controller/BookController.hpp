#ifndef BookController_hpp
#define BookController_hpp

#include "service/BookService.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class BookController: public oatpp::web::server::api::ApiController {
    public:
        BookController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
        :oatpp::web::server::api::ApiController(apiContentMappers){}
    private:
        BookService bookService;
    public:
        static std::shared_ptr<BookController> createShared(
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers)
        ) {
            return std::make_shared<BookController>(apiContentMappers);
        }

        ENDPOINT_INFO(createBook) {
            info->summary = "Create a new book";
            info->tags = std::list<oatpp::String>({"Books"});

            info->addConsumes<Object<BookDto>>("application/json");

            info->addResponse<Object<BookDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("POST", "books", createBook, BODY_DTO(oatpp::Object<BookDto>, bookDto)) {
            return createDtoResponse(Status::CODE_200, bookService.createBook(bookDto));
        }

        ENDPOINT_INFO(putBook) {
            info->summary = "Update Book by bookId";
            info->tags = std::list<oatpp::String>({"Books"});

            info->addConsumes<Object<BookDto>>("application/json");

            info->addResponse<Object<BookDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

            info->pathParams["bookId"].description = "book Identifier";
        }
        ENDPOINT("PUT", "books/{bookId}", putBook,
                PATH(Int32, bookId),
                BODY_DTO(Object<BookDto>, bookDto))
        {
            bookDto->id = bookId;
            return createDtoResponse(Status::CODE_200, bookService.updateBook(bookDto));
        }


        ENDPOINT_INFO(getBookById) {
            info->summary = "Get one Book by bookId";
            info->tags = std::list<oatpp::String>({"Books"});

            info->addResponse<Object<BookDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

            info->pathParams["bookId"].description = "Book Identifier";
        }
        ENDPOINT("GET", "books/{bookId}", getBookById,
                PATH(Int32, bookId))
        {
            return createDtoResponse(Status::CODE_200, bookService.getBookById(bookId));
        }


        ENDPOINT_INFO(getBooks) {
            info->summary = "get all stored books";
            info->tags = std::list<oatpp::String>({"Books"});

            info->addResponse<oatpp::Object<BooksPageDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }
        ENDPOINT("GET", "books/offset/{offset}/limit/{limit}", getBooks,
                PATH(UInt32, offset),
                PATH(UInt32, limit))
        {
            return createDtoResponse(Status::CODE_200, bookService.getAllBooks(offset, limit));
        }


        ENDPOINT_INFO(deleteBook) {
            info->summary = "Delete Book by bookId";
            info->tags = std::list<oatpp::String>({"Books"});

            info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

            info->pathParams["bookId"].description = "Book Identifier";
        }
        ENDPOINT("DELETE", "books/{bookId}", deleteBook,
            PATH(Int32, bookId))
        {
            return createDtoResponse(Status::CODE_200, bookService.deleteBookById(bookId));
        }
};

#include OATPP_CODEGEN_END(ApiController)

#endif