//#include "../../src/logic.h"
#include "../../src/logic.cpp"
#include "../../../../.platformio/packages/tool-unity/unity.h"
#include <unity.h>

//declare here

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_function_logic_logic(void) {
    TEST_ASSERT_EQUAL(2, logic(1, 1));
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_logic_logic);
    UNITY_END();

    return 0;
}
