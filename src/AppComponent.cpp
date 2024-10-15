#include "AppComponent.hpp"

#include "controller/UserController.hpp"
#include "controller/StaticController.hpp"

#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"

#include <iostream>

void run() {
    
}

int main(int argc, const char *argv[]) {
    oatpp::Environment::init();

    run();

    oatpp::Environment::destroy();
    return 0;
}