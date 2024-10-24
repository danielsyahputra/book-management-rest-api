#ifndef BorrowControllerTest_hpp
#define BorrowControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class BorrowControllerTest: public oatpp::test::UnitTest {
    public:
        BorrowControllerTest(): oatpp::test::UnitTest("TEST[BorrowControllerTest]") {}
        void onRun() override;
};

#endif