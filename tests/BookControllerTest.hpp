#ifndef BookControllerTest_hpp
#define BookControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class BookControllerTest: public oatpp::test::UnitTest {
    public:
        BookControllerTest(): oatpp::test::UnitTest("TEST[BookControllerTest]") {}
        void onRun() override;
};

#endif