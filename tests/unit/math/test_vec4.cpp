#include <gtest/gtest.h>

#include "include/math/Vec4.hpp"

class Vec4Test : public testing::Test { };

using namespace RendMath;
constexpr const float FLOAT_ABS_ERROR = std::numeric_limits<float>::epsilon() * 2.0f;
constexpr const double DOUBLE_ABS_ERROR = std::numeric_limits<double>::epsilon() * 4.0;

TEST_F(Vec4Test, Constructors) {
    // Default
    Vec4i vi1;
    Vec4f vf1;
    Vec4d vd1;
    EXPECT_EQ(vi1, Vec4i(0,0,0,0));
    EXPECT_EQ(vf1, Vec4f(0,0,0,0));
    EXPECT_EQ(vd1, Vec4d(0,0,0,0));
    // Vec3
    Vec3i vec3(1, 2, 5);
    Vec4i vi2(vec3, 0);
    EXPECT_EQ(vi2, Vec4i(1,2,5,0));

}

TEST_F(Vec4Test, Index) {
    // Int
    Vec4i vi1 = Vec4i(5, 7, 9, 1);
    EXPECT_EQ(vi1[0], 5);
    EXPECT_EQ(vi1[1], 7);
    EXPECT_EQ(vi1[2], 9);
    EXPECT_EQ(vi1[3], 1);
    EXPECT_THROW(vi1[-1], std::out_of_range);
    EXPECT_THROW(vi1[4], std::out_of_range);
    // Const check
    const Vec4i vi2 = Vec4i(3, 4, 5, 0);
    EXPECT_EQ(vi2[0], 3);
    EXPECT_EQ(vi2[1], 4);
    EXPECT_EQ(vi2[2], 5);
    EXPECT_EQ(vi2[3], 0);
    // Float
    Vec4f vf1 = Vec4f(5.5333333f, 7.1200002f, 3.1415926f, 0.0f);
    EXPECT_NEAR(vf1[0], 5.5333333f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1[1], 7.1200002f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1[2], 3.1415926f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1[3], 0.0f, FLOAT_ABS_ERROR);
    EXPECT_THROW(vf1[-1], std::out_of_range);
    EXPECT_THROW(vf1[4], std::out_of_range);
    // Const check
    const Vec4f vf2 = Vec4f(3.0f, 4.1111f, 2.5f, 1.0f);
    EXPECT_NEAR(vf2[0], 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2[1], 4.1111f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2[2], 2.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2[3], 1.0f, FLOAT_ABS_ERROR);
    // Double
    Vec4d vd1 = Vec4d(5.533333333333333, 7.120000000000002, 3.141592653589793, 0.0);
    EXPECT_NEAR(vd1[0], 5.533333333333333, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1[1], 7.120000000000002, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1[2], 3.141592653589793, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1[3], 0.0, DOUBLE_ABS_ERROR);
    EXPECT_THROW(vd1[-1], std::out_of_range);
    EXPECT_THROW(vd1[4], std::out_of_range);
    // Const check
    const Vec4d vd2 = Vec4d(3.0, 4.1111, 2.5, 1.0);
    EXPECT_NEAR(vd2[0], 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2[1], 4.1111, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2[2], 2.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2[3], 1.0, DOUBLE_ABS_ERROR);
}

TEST_F(Vec4Test, toVec3) {
    Vec4i vi1 = Vec4i(5, 7, 9, 1);
    Vec4i vi2 = Vec4i(5, 7, 9, 0);
    Vec3i vec3_1 = toVec3(vi1);
    Vec3i vec3_2 = toVec3(vi2);
    EXPECT_EQ(vec3_1, Vec3i(5,7,9));
    EXPECT_EQ(vec3_2, Vec3i(5,7,9));

    Vec4f vf1 = Vec4f(5.0f, 10.0f, 20.0f, 0.5f);
    Vec3f vec3f_1 = toVec3(vf1);
    EXPECT_EQ(vec3f_1, Vec3f(10.0f, 20.0f, 40.0f));
}