
#include "../maths/mat3.h"
#include "../maths/vec3.h"

using namespace maths;

uint32_t success = 0;
uint32_t fail = 0;
#define PRINT_TEST(test) \
    std::printf("Test %s: ", #test); \
    if (test) { std::printf("SUCCESS\n"); success++; } else { std::printf("FAILED\n"); fail++; }

int main(int argc, char** argv)
{    
    auto eq1 = vec3(0, 1, 2);
    auto eq2 = vec3(0, 1, 2);
    PRINT_TEST(eq1 == eq2)

    auto ineq1 = vec3(0, 1, 2);
    auto ineq2 = vec3(3, 4, 5);
    PRINT_TEST(ineq1 != ineq2)
    
    auto assign1 = vec3(0);
    auto assign2 = vec3(3, 3, 3);
    assign1 = assign2;
    assign2 = vec3(2, 2, 2);
    auto assignExpected1 = vec3(3, 3, 3);
    auto assignExpected2 = vec3(2, 2, 2);
    PRINT_TEST(assign1 == assignExpected1)
    PRINT_TEST(assign2 == assignExpected2)

    auto add1 = vec3(0, 1, 2);
    auto add2 = vec3(3, 2, 1);
    auto addExpected = vec3(3, 3, 3);
    PRINT_TEST(add1 + add2 == addExpected)

    auto sub1 = vec3(0, 1, 2);
    auto sub2 = vec3(0, 1, 2);
    auto subExpected = vec3(0, 0, 0);
    PRINT_TEST(sub1 - sub2 == subExpected)

    auto minus1 = vec3(0, 1, 2);
    auto minusExpected = vec3(0, -1, -2);
    PRINT_TEST(-minus1 == minusExpected)

    auto addEq1 = vec3(0, 1, 2);
    auto addEq2 = vec3(3, 2, 1);
    addEq1 += addEq2;
    auto addEqExpected = vec3(3, 3, 3);
    PRINT_TEST(addEq1 == addExpected)

    auto subEq1 = vec3(0, 1, 2);
    auto subEq2 = vec3(0, 1, 2);
    subEq1 -= subEq2;
    auto subEqExpected = vec3(0, 0, 0);
    PRINT_TEST(subEq1 == subExpected)

    auto addf1 = vec3(0, 1, 2);
    auto addf2 = 1.0f;
    auto addfExpected = vec3(1, 2, 3);
    PRINT_TEST(addf1 + addf2 == addfExpected)

    auto subf1 = vec3(0, 1, 2);
    auto subf2 = 1.0f;
    auto subfExpected = vec3(-1, 0, 1);
    PRINT_TEST(subf1 - subf2 == subfExpected)

    auto mulf1 = vec3(0, 1, 2);
    auto mulf2 = 2.0f;
    auto mulfExpected = vec3(0, 2, 4);
    PRINT_TEST(mulf1 * mulf2 == mulfExpected)

    auto divf1 = vec3(0, 1, 2);
    auto divf2 = 2.0f;
    auto divfExpected = vec3(0, .5, 1);
    PRINT_TEST(divf1 / divf2 == divfExpected)

    auto addfEq1 = vec3(0, 1, 2);
    auto addfEq2 = 1.0f;
    addfEq1 += addfEq2;
    auto addfEqExpected = vec3(1, 2, 3);
    PRINT_TEST(addfEq1 == addfExpected)

    auto subfEq1 = vec3(0, 1, 2);
    auto subfEq2 = 1.0f;
    subfEq1 -= subfEq2;
    auto subfEqExpected = vec3(-1, 0, 1);
    PRINT_TEST(subfEq1 == subfExpected)

    auto mulfEq1 = vec3(0, 1, 2);
    auto mulfEq2 = 2.0f;
    mulfEq1 *= mulfEq2;
    auto mulfEqExpected = vec3(0, 2, 4);
    PRINT_TEST(mulfEq1 == mulfExpected)

    auto divfEq1 = vec3(0, 1, 2);
    auto divfEq2 = 2.0f;
    divfEq1 /= divfEq2;
    auto divfEqExpected = vec3(0, .5, 2);
    PRINT_TEST(divfEq1 == divfExpected)

    auto dot1 = vec3(1, 0, 0);
    auto dot2 = vec3(-1, 0, 0);
    PRINT_TEST(dot1.dot(dot2) == -1.0f)
    
    auto dot3 = vec3(0, 1, 0);
    PRINT_TEST(dot1.dot(dot3) == 0.0f)

    auto cross1 = vec3(1, 0, 0);
    auto cross2 = vec3(0, 1, 0);
    auto crossExpected = vec3(0, 0, 1);
    PRINT_TEST(cross1.cross(cross2) == crossExpected)

    auto magn1 = vec3(1, 0, 0);
    PRINT_TEST(magn1.magnitude() == 1.0f)

    auto norm1 = vec3(1, 0, 0);
    auto norm1Expected = vec3(1, 0, 0);
    PRINT_TEST(norm1.normalized() == norm1Expected)

    auto norm2 = vec3(1, 1, 0);
    auto norm2Expected = vec3(1.0f/sqrt(2.0f), 1.0f/sqrt(2.0f), 0);
    PRINT_TEST(norm2.normalized() == norm2Expected)

    auto norm3 = vec3(1, 1, 0);
    auto norm3Expected = vec3(1.0f/sqrt(2.0f), 1.0f/sqrt(2.0f), 0);
    norm3.normalize();
    PRINT_TEST(norm3 == norm3Expected)

    auto reflect1 = vec3(0, 1, 0);
    auto reflect2 = vec3(1, -1, 0).normalized();
    auto reflectExpected = vec3(1, 1, 0).normalized();
    PRINT_TEST(reflect2.reflect(reflect1) == reflectExpected)

    auto bracket = vec3(3, 2, 1);
    PRINT_TEST(bracket[0] == 3 && bracket[1] == 2 && bracket[2] == 1)

    std::printf("%u tests succeeded, %u tests failed.", success, fail);

    return 0;
}