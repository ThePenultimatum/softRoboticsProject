#include "unity.h"
#include "pneumatics.h"

void setUp(void)
{
    /* This is run before EACH TEST */
}

void tearDown(void)
{
    /* This is run after EACH TEST */	
}

int test_getValveStateLogic_allValvesOpen(void)
{
	return getValveStateLogic(0, 0);
}

int test_getValveStateLogic_allValvesClosed(void)
{
	return getValveStateLogic(1, 1);
}

int test_getValveStateLogic_valvesAirOpen(void)
{
	return getValveStateLogic(1, 0);
}

int test_getValveStateLogic_valvesVacuumOpen(void)
{
	return getValveStateLogic(0, 1);
}

int main(void)
{
    UNITY_BEGIN();
    TEST_ASSERT_EQUAL_HEX8(test_getValveStateLogic_allValvesOpen(), VALVESOPEN);
    TEST_ASSERT_EQUAL_HEX8(test_getValveStateLogic_allValvesClosed(), VALVESCLOSED);
    TEST_ASSERT_EQUAL_HEX8(test_getValveStateLogic_valvesAirOpen(), VALVESAIROPEN);
    TEST_ASSERT_EQUAL_HEX8(test_getValveStateLogic_valvesVacuumOpen(), VALVESVACUUMOPEN);
    
    return UNITY_END();
}