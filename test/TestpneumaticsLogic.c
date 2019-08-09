#include "unity.h"
#include "pneumaticsLogic.h"

void setUp(void)
{
    /* This is run before EACH TEST */
}

void tearDown(void)
{
    /* This is run after EACH TEST */	
}

void test_getValveStateLogic_FourCases(void) {
    TEST_ASSERT_EQUAL_INT(getValveStateLogic(0, 0), VALVESOPEN);
    TEST_ASSERT_EQUAL_INT(getValveStateLogic(1, 1), VALVESCLOSED);
    TEST_ASSERT_EQUAL_INT(getValveStateLogic(1, 0), VALVESAIROPEN);
    TEST_ASSERT_EQUAL_INT(getValveStateLogic(0, 1), VALVESVACUUMOPEN);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getValveStateLogic_FourCases);
    return UNITY_END();
}