#include "unity.h"
#include "pneumatics.h"


#define LATDbits.LATD2 1


void setUp(void)
{
    /* This is run before EACH TEST */
}

void tearDown(void)
{
    /* This is run after EACH TEST */	
}

void test_allValvesOpen(void)
{

}

int main(void)
{
    UNITY_BEGIN();
    TEST_ASSERT_EQUAL_HEX8(84, 84);
    
    return UNITY_END();
}