#ifndef ConfigurationComponent_hpp
#define ConfigurationComponent_hpp

#include "dto/ConfigDto.hpp"
#include "utils/dotenv.h"
#include "oatpp/macro/component.hpp"
#include <cstdlib>

class ConfigurationComponent {
    private:
        static oatpp::Object<ConfigDto> createConfig() {
            auto config = ConfigDto::createShared();

            dotenv::init();

            auto port = dotenv::getenv("APP_PORT", "9999");
            config->port = static_cast<v_uint16>(std::stoi(port));
            
            config->host = dotenv::getenv("APP_HOST", "0.0.0.0");

            return config;
        }

    public:
        OATPP_CREATE_COMPONENT(oatpp::Object<ConfigDto>, config)([] {
            return ConfigurationComponent::createConfig();
    }());
};

#endif