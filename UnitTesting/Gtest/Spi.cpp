#include "gtest/gtest.h"
#include <stdio.h>

// TEST(TestCaseName, TestName) {
TEST(Funstion1, Test1){
    // EXPECT_EQ( expected, actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);



    return RUN_ALL_TESTS();
}