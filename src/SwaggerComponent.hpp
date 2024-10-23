#ifndef SwaggerComponent_hpp
#define SwaggerComponent_hpp

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/macro/component.hpp"

class SwaggerComponent {
    public:
        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
            oatpp::swagger::DocumentInfo::Builder builder;

            builder
            .setTitle("Book Management Service")
            .setDescription("Book Management RESTful API")
            .setVersion("1.0")
            .setContactName("Daniel Syahputra")
            .setContactUrl("https://github.com/danielsyahputra")
            .setLicenseName("MIT License")
            .setLicenseUrl("https://opensource.org/license/mit")
            .addServer("http://localhost:9999", "localhost server");

            return builder.build();
        }());

        OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
            return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
        }());
};

#endif