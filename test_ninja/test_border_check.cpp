#include <ctest.h>

#include "helper.h"
#include "letters.h"
#include <iostream>

CTEST(check_border_test, test_1)
{
    Letters A;
    Letters B(0, 960, 22, 0);
    Letters C(0, 970, 22, 0);

    ASSERT_EQUAL(A.Delete_letter_beyond(A.Get_coordinate_y(), 3), 0);
    ASSERT_EQUAL(B.Delete_letter_beyond(B.Get_coordinate_y(), 3), 1);
    ASSERT_EQUAL(C.Delete_letter_beyond(C.Get_coordinate_y(), 3), 1);
}
