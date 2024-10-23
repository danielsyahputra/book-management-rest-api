#ifndef BorrowController_hpp
#define BorrowController_hpp

#include "service/BorrowService.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class BorrowController: public oatpp::web::server::api::ApiController {
    public:
        BorrowController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
        : oatpp::web::server::api::ApiController(apiContentMappers)
        {}
    private:
        BorrowService borrowService;

    public:
        static std::shared_ptr<BorrowController> createShared(
            OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers)
        ){
            return std::make_shared<BorrowController>(apiContentMappers);
        }

        ENDPOINT_INFO(createBorrow) {
            info->summary = "Create new borrow";
            info->tags = std::list<oatpp::String>({"Borrows"});

            info->addConsumes<Object<BorrowDto>>("application/json");

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }
        ENDPOINT("POST", "borrows", createBorrow, BODY_DTO(oatpp::Object<BorrowDto>, borrowDto)) {
            return createDtoResponse(Status::CODE_200, borrowService.createBorrow(borrowDto));
        }

        ENDPOINT_INFO(updateBorrow) {
            info->summary = "Update borrow by borrowId";
            info->tags = std::list<oatpp::String>({"Borrows"});
            info->addConsumes<Object<BorrowDto>>("application/json");

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("PUT", "borrows/{borrowId}", updateBorrow,
            PATH(Int32, borrowId),
            BODY_DTO(Object<BorrowDto>, borrowDto)) 
        {
            borrowDto->id = borrowId;
            return createDtoResponse(Status::CODE_200, borrowService.updateBorrow(borrowDto));
        }

        ENDPOINT_INFO(getBorrowById) {
            info->summary = "Get one borrow by borrowId";
            info->tags = std::list<oatpp::String>({"Borrows"});

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("GET", "borrows/{borrowId}", getBorrowById,
            PATH(Int32, borrowId)) 
        {
            return createDtoResponse(Status::CODE_200, borrowService.getBorrowById(borrowId));
        }

        ENDPOINT_INFO(getBorrows) {
            info->summary = "Get all borrows";
            info->tags = std::list<oatpp::String>({"Borrows"});

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("GET", "borrows/offset/{offset}/limit/{limit}", getBorrows,
            PATH(UInt32, offset),
            PATH(UInt32, limit))
        {
            return createDtoResponse(Status::CODE_200, borrowService.getAllBorrows(offset, limit));
        }

        ENDPOINT_INFO(deleteBorrow) {
            info->summary = "Delete borrow by borrowId";
            info->tags = std::list<oatpp::String>({"Borrows"});

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("DELETE", "borrows/{borrowId}", deleteBorrow,
            PATH(Int32, borrowId)) 
        {
            return createDtoResponse(Status::CODE_200, borrowService.deleteBorrowById(borrowId));
        }

        ENDPOINT_INFO(getBorrowsByUserId) {
            info->summary = "Get all borrows by userId";
            info->tags = std::list<oatpp::String>({"Borrows"});            

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("GET", "borrows/{userId}/offset/{offset}/limit/{limit}", getBorrowsByUserId,
            PATH(Int32, userId),
            PATH(UInt32, offset),
            PATH(UInt32, limit)) 
        {
            return createDtoResponse(Status::CODE_200, borrowService.getBorrowsByUserId(userId, offset, limit));
        }

        ENDPOINT_INFO(getBorrowsByBookId) {
            info->summary = "Get all borrows by bookId";
            info->tags = std::list<oatpp::String>({"Borrows"});

            info->addResponse<Object<BorrowDto>>(Status::CODE_200, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
            info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        }

        ENDPOINT("GET", "borrows/{bookId}/offset/{offset}/limit/{limit}", getBorrowsByBookId,
            PATH(Int32, bookId),
            PATH(UInt32, offset),
            PATH(UInt32, limit)) 
        {
            return createDtoResponse(Status::CODE_200, borrowService.getBorrowsByUserId(bookId, offset, limit));
        }
};


#include OATPP_CODEGEN_END(ApiController)

#endif