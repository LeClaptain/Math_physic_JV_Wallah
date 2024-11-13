
#include "../maths/mat3.h"
#include "../maths/vec3.h"
#include "../maths/mat4.h"
#include "../maths/quaternion.h"

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


    // ####################### Tests Mat3 ##############################

    auto mat3_eq1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_eq2 = mat3(0,1,2,3,4,5,6,7,8);
    PRINT_TEST(mat3_eq1 == mat3_eq2)

    auto mat3_det = mat3(0,1,2,3,4,5,6,7,8);
    PRINT_TEST(mat3_det.det() == 0);

    auto mat3_add1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_add2 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_add3 = mat3(0,2,4,6,8,10,12,14,16);
    PRINT_TEST(mat3_add1 + mat3_add2 == mat3_add3)

    auto mat3_addEq1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_addEq2 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_addEq3 = mat3(0,2,4,6,8,10,12,14,16);
    mat3_addEq1 += mat3_addEq2;
    PRINT_TEST(mat3_addEq1 == mat3_addEq3)

    auto mat3_sub1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_sub2 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_sub3 = mat3(0,0,0,0,0,0,0,0,0);
    PRINT_TEST(mat3_sub1 - mat3_sub2 == mat3_sub3)

    auto mat3_subEq1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_subEq2 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_subEq3 = mat3(0,0,0,0,0,0,0,0,0);
    mat3_subEq1 -= mat3_subEq2;
    PRINT_TEST(mat3_subEq1 == mat3_subEq3)

    auto mat3_mul1 = mat3(1,0,0,0,1,0,0,0,1);
    auto mat3_mul2 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_mul3 = mat3(0,1,2,3,4,5,6,7,8);
    PRINT_TEST(mat3_mul1 * mat3_mul2 == mat3_mul3)

    auto mat3_mulEq1 = mat3(1,0,0,0,1,0,0,0,1);
    auto mat3_mulEq2 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_mulEq3 = mat3(0,1,2,3,4,5,6,7,8);
    mat3_mulEq1 *= mat3_mulEq2;
    PRINT_TEST(mat3_mulEq1 == mat3_mulEq3)

    auto mat3_opposite1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_opposite2 = mat3(0,-1,-2,-3,-4,-5,-6,-7,-8);
    PRINT_TEST(-mat3_opposite1 == mat3_opposite2)

    auto mat3_addFloat1 = mat3(0,1,2,3,4,5,6,7,8);
    float mat3_addFloat2 = 2.0;
    auto mat3_addFloatExpected = mat3(2,3,4,5,6,7,8,9,10);
    PRINT_TEST(mat3_addFloat1 + mat3_addFloat2 == mat3_addFloatExpected)

    auto mat3_addEqFloat1 = mat3(0,1,2,3,4,5,6,7,8);
    float mat3_addEqFloat2 = 2.0;
    auto mat3_addEqFloat3 = mat3_addEqFloat1 += mat3_addEqFloat2;
    auto mat3_addEqFloatExpected = mat3(2,3,4,5,6,7,8,9,10);
    PRINT_TEST(mat3_addEqFloat3 == mat3_addEqFloatExpected)

    auto mat3_subFloat1 = mat3(0,1,2,3,4,5,6,7,8);
    float mat3_subFloat2 = 2.0;
    auto mat3_subFloatExpected = mat3(-2,-1,0,1,2,3,4,5,6);
    PRINT_TEST(mat3_subFloat1 - mat3_subFloat2 == mat3_subFloatExpected)

    auto mat3_subEqFloat1 = mat3(0,1,2,3,4,5,6,7,8);
    float mat3_subEqFloat2 = 2.0;
    auto mat3_subEqFloat3 = mat3_subEqFloat1 -= mat3_subEqFloat2;
    auto mat3_subEqFloatExpected = mat3(-2,-1,0,1,2,3,4,5,6);
    PRINT_TEST(mat3_subEqFloat3 == mat3_subEqFloatExpected)

    auto mat3_mulFloat1 = mat3(0,1,2,3,4,5,6,7,8);
    float mat3_mulFloat2 = 2.0;
    auto mat3_mulFloatExpected = mat3(0,2,4,6,8,10,12,14,16);
    PRINT_TEST(mat3_mulFloat1 * mat3_mulFloat2 == mat3_mulFloatExpected)

    auto mat3_mulEqFloat1 = mat3(0,1,2,3,4,5,6,7,8);
    float mat3_mulEqFloat2 = 2.0;
    auto mat3_mulEqFloat3 = mat3_mulEqFloat1 *= mat3_mulEqFloat2;
    auto mat3_mulEqFloatExpected = mat3(0,2,4,6,8,10,12,14,16);
    PRINT_TEST(mat3_mulEqFloat3 == mat3_mulFloatExpected)

    auto mat3_divEqFloat1 = mat3(0,2,4,6,8,10,12,14,16);
    float mat3_divEqFloat2 = 2.0;
    auto mat3_divEqFloat3 = mat3_divEqFloat1 /= mat3_divEqFloat2;
    auto mat3_divEqFloatExpected = mat3(0,1,2,3,4,5,6,7,8);
    PRINT_TEST(mat3_divEqFloat3 == mat3_divEqFloatExpected);

    auto mat3_mulVec1 = mat3(0,1,2,3,4,5,6,7,8);
    vec3 mat3_mulVec2 = vec3(0,1,2);
    auto mat3_mulVecExpected = vec3(5,14,23);
    PRINT_TEST(mat3_mulVec1 * mat3_mulVec2 == mat3_mulVecExpected);

    auto mat3_transpose1 = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_transpose2 = mat3_transpose1.transpose();
    auto mat3_transposeExpected = mat3(0,3,6,1,4,7,2,5,8);
    PRINT_TEST(mat3_transpose2 == mat3_transposeExpected)

    auto mat3_inverse1 = mat3(2,1,-2,3,2,2,5,4,3);
    auto mat3_inverse2 = mat3_inverse1.inverse();
    auto mat3_inverseExpected = mat3(2,11,-6,-1,-16,10,-2,3,-1) * (1.0f/7);
    PRINT_TEST(mat3_inverse2 == mat3_inverseExpected);

    auto mat3_identite = mat3::identity();
    auto mat3_identiteExpected = mat3(1,0,0,0,1,0,0,0,1);
    PRINT_TEST(mat3_identite == mat3_identiteExpected)

    auto mat3_get = mat3(0,1,2,3,4,5,6,7,8);
    auto mat3_get11 = mat3_get[0];
    auto mat3_get11Expected = 0;
    PRINT_TEST(mat3_get11 == mat3_get11Expected);

    // ####################### Tests Mat4 ##############################

    auto mat4_eq1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_eq2 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    PRINT_TEST(mat4_eq1 == mat4_eq2);

    auto mat4_det = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    PRINT_TEST(mat4_det.det() == 0);

    auto mat4_add1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_add2 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_addExpected = maths::mat4(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
    PRINT_TEST(mat4_add1 + mat4_add2 == mat4_addExpected);

    auto mat4_addEq1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_addEq2 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    mat4_addEq1 += mat4_addEq2;
    PRINT_TEST(mat4_addEq1 == mat4_addExpected);

    auto mat4_sub1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_sub2 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_subExpected = maths::mat4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    PRINT_TEST(mat4_sub1 - mat4_sub2 == mat4_subExpected);

    auto mat4_subEq1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    mat4_subEq1 -= mat4_sub2;
    PRINT_TEST(mat4_subEq1 == mat4_subExpected);

    auto mat4_mul1 = maths::mat4::identity();
    auto mat4_mul2 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_mul3 = mat4_mul1 * mat4_mul2;
    PRINT_TEST(mat4_mul3 == mat4_mul2);

    auto mat4_mulEq1 = maths::mat4::identity();
    auto mat4_mulEq2 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_mulEq3 = mat4_mulEq1 *= mat4_mulEq2;
    PRINT_TEST(mat4_mulEq3 == mat4_mulEq2);

    auto mat4_opposite1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_oppositeExpected = maths::mat4(0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15);
    PRINT_TEST(-mat4_opposite1 == mat4_oppositeExpected);

    auto mat4_addFloat1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    float mat4_addFloat2 = 2.0f;
    auto mat4_addFloatExpected = maths::mat4(2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17);
    PRINT_TEST(mat4_addFloat1 + mat4_addFloat2 == mat4_addFloatExpected);

    auto mat4_addEqFloat1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    float mat4_addEqFloat2 = 2.0f;
    auto mat4_addEqFloat3 = mat4_addEqFloat1 += mat4_addEqFloat2;
    auto mat4_addEqFloatExpected = maths::mat4(2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17);
    PRINT_TEST(mat4_addEqFloat3 == mat4_addEqFloatExpected);

    auto mat4_subFloatExpected = maths::mat4(-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13);
    PRINT_TEST(mat4_addFloat1 - mat4_addFloat2 == mat4_subFloatExpected);

    auto mat4_subEqFloat1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    float mat4_subEqFloat2 = 2.0f;
    auto mat4_subEqFloat3 = mat4_subEqFloat1 -= mat4_subEqFloat2;
    auto mat4_subEqFloatExpected = maths::mat4(-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13);
    PRINT_TEST(mat4_subEqFloat3 == mat4_subEqFloatExpected);

    auto mat4_mulFloatExpected = maths::mat4(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
    PRINT_TEST(mat4_addFloat1 * mat4_addFloat2 == mat4_mulFloatExpected);

    auto mat4_mulEqFloat1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    float mat4_mulEqFloat2 = 2.0f;
    auto mat4_mulEqFloat3 = mat4_mulEqFloat1 *= mat4_mulEqFloat2;
    auto mat4_mulEqFloatExpected = maths::mat4(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
    PRINT_TEST(mat4_mulEqFloat3 == mat4_mulEqFloatExpected);

    auto mat4_divFloat1 = maths::mat4(0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30);
    float mat4_divFloat2 = 2.0f;
    auto mat4_divFloatExpected = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    PRINT_TEST(mat4_divFloat1 / mat4_divFloat2 == mat4_divFloatExpected);

    auto mat4_transpose1 = maths::mat4(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    auto mat4_transposeExpected = maths::mat4(0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15);
    PRINT_TEST(mat4_transpose1.transpose() == mat4_transposeExpected);

    auto mat4_identity = maths::mat4::identity();
    auto mat4_identityExpected = maths::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    PRINT_TEST(mat4_identity == mat4_identityExpected);

    // ###################### Quaternions ##############################
    

    auto quat_toMat4 = maths::quaternion(1, 2, 3, 4).toMat4();
    auto quat_toMat4Expected = maths::mat4(1, -4, 3, 2,
                                           4,  1, -2, 3,
                                          -3,  2,  1, 4,
                                          -2, -3, -4, 1);
    PRINT_TEST(quat_toMat4 == quat_toMat4Expected);

    auto quat_magnitude = maths::quaternion(1, 2, 3, 4).magnitude();
    float quat_magnitudeExpected = maths::vec4(2, 3, 4, 1).magnitude();
    PRINT_TEST(quat_magnitude == quat_magnitudeExpected);

    auto quat_conjugate = maths::quaternion(1, 2, 3, 4).conjugate();
    auto quat_conjugateExpected = maths::quaternion(1, -2, -3, -4);
    PRINT_TEST(quat_conjugate == quat_conjugateExpected);

    auto quat_inverse = maths::quaternion(1, 2, 3, 4).inverse();
    auto quat_inverseExpected = maths::quaternion(1, -2, -3, -4) / quat_magnitudeExpected;
    PRINT_TEST(quat_inverse == quat_inverseExpected);

    auto quat_dot = maths::quaternion(1, 2, 3, 4).dot(maths::quaternion(2, 2, 2, 2));
    float quat_dotExpected = 1 * 2 + 2 * 2 + 3 * 2 + 4 * 2;
    PRINT_TEST(quat_dot == quat_dotExpected);

    // Test de la méthode pow avec un angle significatif
    auto quat_pow = maths::quaternion(0.99f, 0.5f, 0.5f, 0.5f).pow(0.5f);
    float alpha = acos(0.99f); // Angle en radians
    auto quat_powExpected = maths::quaternion(
        cos(0.5f * alpha), 
        maths::vec3(0.5f, 0.5f, 0.5f) * (sin(0.5f * alpha) / sin(alpha))
    );
    PRINT_TEST(quat_pow == quat_powExpected);

    // Test de la méthode pow pour un angle très petit (_w proche de 1)
    auto quat_powBis = maths::quaternion(0.991f, 0.5f, 0.5f, 0.5f).pow(0.5f);
    auto quat_powBisExpected = maths::quaternion(0.991f, 0.5f, 0.5f, 0.5f);
    PRINT_TEST(quat_powBis == quat_powBisExpected);
    
    auto quat_pow_near_identity = maths::quaternion(1, 0.001f, 0.001f, 0.001f).pow(0.5f);
    auto quat_pow_near_identityExpected = maths::quaternion(1, 0.001f, 0.001f, 0.001f); // Pas de changement significatif
    PRINT_TEST(quat_pow_near_identity == quat_pow_near_identityExpected);

    auto quat_rotation = maths::quaternion(1, 2, 3, 4).isRotation();
    bool quat_rotationExpected = maths::quaternion(1, 2, 3, 4).magnitude() == 1;
    PRINT_TEST(quat_rotation == quat_rotationExpected);

    auto quat_neg = -maths::quaternion(1, 2, 3, 4);
    auto quat_negExpected = maths::quaternion(-1, -2, -3, -4);
    PRINT_TEST(quat_neg == quat_negExpected);

    auto quat_addFloat = maths::quaternion(1, 2, 3, 4) + 2.0f;
    auto quat_addFloatExpected = maths::quaternion(3, 4, 5, 6);
    PRINT_TEST(quat_addFloat == quat_addFloatExpected);

    auto quat_subFloat = maths::quaternion(1, 2, 3, 4) - 2.0f;
    auto quat_subFloatExpected = maths::quaternion(-1, 0, 1, 2);
    PRINT_TEST(quat_subFloat == quat_subFloatExpected);

    auto quat_mulFloat = maths::quaternion(1, 2, 3, 4) * 2.0f;
    auto quat_mulFloatExpected = maths::quaternion(2, 4, 6, 8);
    PRINT_TEST(quat_mulFloat == quat_mulFloatExpected);

    auto quat_divFloat = maths::quaternion(2, 4, 6, 8) / 2.0f;
    auto quat_divFloatExpected = maths::quaternion(1, 2, 3, 4);
    PRINT_TEST(quat_divFloat == quat_divFloatExpected);

    auto quat_equal1 = maths::quaternion(1, 2, 3, 4);
    auto quat_equal2 = maths::quaternion(1, 2, 3, 4);
    PRINT_TEST(quat_equal1 == quat_equal2);

    auto quat_notEqual1 = maths::quaternion(1, 2, 3, 4);
    auto quat_notEqual2 = maths::quaternion(4, 3, 2, 1);
    PRINT_TEST(quat_notEqual1 != quat_notEqual2);

    auto quat_subQuat = maths::quaternion(1, 2, 3, 4) - maths::quaternion(4, 3, 2, 1);
    auto quat_subQuatExpected = maths::quaternion(4, 3, 2, 1) * maths::quaternion(1, -2, -3, -4);
    PRINT_TEST(quat_subQuat == quat_subQuatExpected);

    auto quat_mulQuat = maths::quaternion(1, 2, 3, 4) * maths::quaternion(4, 3, 2, 1);
    auto quat_mulQuatExpected = maths::quaternion(
        1 * 4 - maths::vec3(2, 3, 4).dot(maths::vec3(3, 2, 1)),
        maths::vec3(3, 2, 1) * 1 + maths::vec3(2, 3, 4) * 4 + maths::vec3(2, 3, 4).cross(maths::vec3(3, 2, 1))
    );
    PRINT_TEST(quat_mulQuat == quat_mulQuatExpected);
    
    

    // ###################### FIN ######################################
     
    std::printf("%u tests succeeded, %u tests failed.", success, fail);

    return 0;
}