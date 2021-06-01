#include <ctest.h>

#include "helper.h"
#include "letters.h"
#include <iostream>

CTEST(check_key_test, test_1)
{
    Letters A;
    Letters B(0, 960, 22, 0);
    Letters C(0, 970, 22, 0);
    int score = 5;
    int flag = 0;

    ASSERT_EQUAL(A.Check_code_key(22, score, flag), 1);
    ASSERT_EQUAL(B.Check_code_key(22, score, flag), 1);
    ASSERT_EQUAL(C.Check_code_key(20, score, flag), 0);
}