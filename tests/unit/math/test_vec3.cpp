#include <gtest/gtest.h>

#include "include/math/Vec3.hpp"

class Vec3Test : public testing::Test { };

using namespace RendMath;
constexpr const float FLOAT_ABS_ERROR = std::numeric_limits<float>::epsilon() * 2.0f;
constexpr const double DOUBLE_ABS_ERROR = std::numeric_limits<double>::epsilon() * 4.0;

TEST_F(Vec3Test, DefaultConstructor) {
    Vec3i v1 = Vec3i();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
    EXPECT_EQ(v1.z, 0);
    Vec3f v2 = Vec3f();
    EXPECT_EQ(v2.x, 0);
    EXPECT_EQ(v2.y, 0);
    EXPECT_EQ(v2.z, 0);
    Vec3d v3 = Vec3d();
    EXPECT_EQ(v3.x, 0);
    EXPECT_EQ(v3.y, 0);
    EXPECT_EQ(v3.z, 0);
}

TEST_F(Vec3Test, IntDot) {
    Vec3i vi1 = Vec3i(10);
    Vec3i vi2 = Vec3i(10);
    EXPECT_EQ(vi1.dot(vi2), 300);
    Vec3i vi3 = Vec3i(5, 4, 3);
    EXPECT_EQ(vi1.dot(vi3), 120);
    Vec3i vi4 = Vec3i();
    EXPECT_EQ(vi1.dot(vi4), 0);
}

TEST_F(Vec3Test, Index) {
    // Int
    Vec3i vi1 = Vec3i(5, 7, 9);
    EXPECT_EQ(vi1[0], 5);
    EXPECT_EQ(vi1[1], 7);
    EXPECT_EQ(vi1[2], 9);
    EXPECT_THROW(vi1[-1], std::out_of_range);
    EXPECT_THROW(vi1[3], std::out_of_range);
    // Const check
    const Vec3i vi2 = Vec3i(3, 4, 5);
    EXPECT_EQ(vi2[0], 3);
    EXPECT_EQ(vi2[1], 4);
    EXPECT_EQ(vi2[2], 5);
    // Float
    Vec3f vf1 = Vec3f(5.5333333f, 7.1200002f, 3.1415926f);
    EXPECT_NEAR(vf1[0], 5.5333333f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1[1], 7.1200002f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1[2], 3.1415926f, FLOAT_ABS_ERROR);
    EXPECT_THROW(vf1[-1], std::out_of_range);
    EXPECT_THROW(vf1[3], std::out_of_range);
    // Const check
    const Vec3f vf2 = Vec3f(3.0f, 4.1111f, 2.5f);
    EXPECT_NEAR(vf2[0], 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2[1], 4.1111f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2[2], 2.5f, FLOAT_ABS_ERROR);
    // Double
    Vec3d vd1 = Vec3d(5.533333333333333, 7.120000000000002, 3.141592653589793);
    EXPECT_NEAR(vd1[0], 5.533333333333333, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1[1], 7.120000000000002, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1[2], 3.141592653589793, DOUBLE_ABS_ERROR);
    EXPECT_THROW(vd1[-1], std::out_of_range);
    EXPECT_THROW(vd1[3], std::out_of_range);
    // Const check
    const Vec3d vd2 = Vec3d(3.0, 4.1111, 2.5);
    EXPECT_NEAR(vd2[0], 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2[1], 4.1111, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2[2], 2.5, DOUBLE_ABS_ERROR);
}

TEST_F(Vec3Test, IntOperators) {
    Vec3i vi1 = Vec3i();
    Vec3i vi2 = Vec3i(1);
    Vec3i vi3 = Vec3i(2, 3, 4);
    Vec3i vi4 = Vec3i(-4, -5, -6);
    // Addition
    Vec3i vi5 = vi1 + vi2;
    EXPECT_EQ(vi5, vi2);
    vi5 += vi3;
    EXPECT_EQ(vi5, Vec3i(3, 4, 5));
    vi5 += vi4;
    EXPECT_EQ(vi5, Vec3i(-1, -1, -1));
    // Subtraction
    vi5 = vi1 - vi2;
    EXPECT_EQ(vi5, -vi2);
    vi5 -= vi3;
    EXPECT_EQ(vi5, Vec3i(-3, -4, -5));
    vi5 -= vi4;
    EXPECT_EQ(vi5, Vec3i(1, 1, 1));
    // Multiplication
    vi5 = vi2 * 4;
    EXPECT_EQ(vi5, Vec3i(4, 4, 4));
    vi5 = 5 * vi2;
    EXPECT_EQ(vi5, Vec3i(5, 5, 5));
    vi5 *= 4;
    EXPECT_EQ(vi5, Vec3i(20, 20, 20));
    vi5 = vi1 * vi2;
    EXPECT_EQ(vi5, vi1);
    vi5 = vi3 * vi4;
    EXPECT_EQ(vi5, Vec3i(-8, -15, -24));
    vi5 *= vi3;
    EXPECT_EQ(vi5, Vec3i(-16, -45, -96));
    // Division
    vi5 = Vec3i(12, 20, 36);
    EXPECT_EQ(vi5 / 4, Vec3i(3, 5, 9));
    vi5 /= 2;
    EXPECT_EQ(vi5, Vec3i(6, 10, 18));
    vi5 = Vec3i(12, 20, 36) / Vec3i(4, 5, 6);
    EXPECT_EQ(vi5, Vec3i(3, 4, 6));
    vi5 = Vec3i(12, 20, 36);
    vi5 /= Vec3i(3, 4, 6);
    EXPECT_EQ(vi5, Vec3i(4, 5, 6));
    // Negation
    EXPECT_EQ(-vi2, Vec3i(-1, -1, -1));
    EXPECT_EQ(-vi4, Vec3i(4, 5, 6));
    EXPECT_EQ(-vi1, vi1);
    // Equality
    EXPECT_EQ((vi1 == Vec3i(0, 0, 0)), true);
    EXPECT_EQ((vi2 == Vec3i(1, 1, 1)), true);
    EXPECT_EQ((vi1 == Vec3i(2, 3, 4)), false);
    EXPECT_EQ((vi1 == vi2), false);
    // Inequality
    Vec3i vi6 = Vec3i(1, 1, 1);
    EXPECT_EQ((vi1 != vi2), true);
    EXPECT_EQ((vi2 != vi6), false);
    EXPECT_EQ((vi2 != Vec3i(1)), false);
}

TEST_F(Vec3Test, FloatLength) {
    Vec3f vf1 = Vec3f(10);
    EXPECT_FLOAT_EQ(vf1.length(), 17.320507f);
    vf1 = Vec3f(-10);
    EXPECT_FLOAT_EQ(vf1.length(), 17.320507f);
    vf1 = Vec3f();
    EXPECT_FLOAT_EQ(vf1.length(), 0);
    // Const check
    const Vec3f vf2 = Vec3f(5);
    EXPECT_FLOAT_EQ(vf2.length(), 8.6602540f);
}

TEST_F(Vec3Test, FloatNormalize) {
    Vec3f vf1 = Vec3f(3, 2, 1);
    vf1.normalize();
    EXPECT_NEAR(vf1.x, 0.8017837f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1.y, 0.5345225f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1.z, 0.2672612f, FLOAT_ABS_ERROR);
    Vec3f vf2 = Vec3f(100, -214, 50);
    vf2.normalize();
    EXPECT_NEAR(vf2.x, 0.4141718f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2.y, -0.8863278f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2.z, 0.2070859f, FLOAT_ABS_ERROR);
    Vec3f vf3 = Vec3f();
    vf3.normalize();
    EXPECT_EQ(vf3.x, 0);
    EXPECT_EQ(vf3.y, 0);
    EXPECT_EQ(vf3.z, 0);
    // Function
    Vec3f vf4 = normalize(vf2);
    EXPECT_NEAR(vf4.x, 0.4141718f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf4.y, -0.8863278f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf4.z, 0.2070859f, FLOAT_ABS_ERROR);
    // Const check
    const Vec3f vf5 = Vec3f(100, -214, 50);
    Vec3f vf6 = normalize(vf5);
    EXPECT_NEAR(vf6.x, 0.4141718f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf6.y, -0.8863278f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf6.z, 0.2070859f, FLOAT_ABS_ERROR);
}

TEST_F(Vec3Test, FloatDot) {
    Vec3f vf1 = Vec3f(1);
    Vec3f vf2 = Vec3f(2);
    EXPECT_EQ(vf1.dot(vf2), 6);
    // Function
    EXPECT_EQ(dot(vf1, vf2), 6);
    // Const check
    const Vec3f vf3 = Vec3f(3, 4, 5);
    EXPECT_EQ(vf3.dot(vf1), 12);
}

TEST_F(Vec3Test, FloatCross) {
    Vec3f vf1 = Vec3f(1, 0, 0);
    Vec3f vf2 = Vec3f(0, 1, 0);
    Vec3f vf3 = vf1.cross(vf2);
    EXPECT_NEAR(vf3.x, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf3.y, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf3.z, 1.0f, FLOAT_ABS_ERROR);
    // Anticommutative: a x b = -(b x a)
    Vec3f vf4 = vf2.cross(vf1);
    EXPECT_NEAR(vf4.z, -1.0f, FLOAT_ABS_ERROR);
    // Function
    Vec3f vf5 = cross(vf1, Vec3f(0, 0, 1));
    EXPECT_NEAR(vf5.x, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf5.y, -1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf5.z, 0.0f, FLOAT_ABS_ERROR);
    // Const check
    const Vec3f vf6 = Vec3f(1, 2, 3);
    const Vec3f vf7 = Vec3f(4, 5, 6);
    Vec3f vf8 = vf6.cross(vf7);
    EXPECT_NEAR(vf8.x, -3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf8.y, 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf8.z, -3.0f, FLOAT_ABS_ERROR);
}

TEST_F(Vec3Test, FloatOperations) {
    Vec3f vi1 = Vec3f();
    Vec3f vi2 = Vec3f(1.5f);
    Vec3f vi3 = Vec3f(2.0005f, 3.135f, 1.5f);
    Vec3f vi4 = Vec3f(-4.5025f, -5.125f, -2.0f);
    // Addition
    Vec3f vi5 = vi1 + vi2;
    EXPECT_NEAR(vi5.x, 1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 1.5f, FLOAT_ABS_ERROR);
    vi5 += vi3;
    EXPECT_NEAR(vi5.x, 3.5005f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 4.635f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 3.0f, FLOAT_ABS_ERROR);
    vi5 += vi4;
    EXPECT_NEAR(vi5.x, -1.002f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -0.490f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 1.0f, FLOAT_ABS_ERROR);
    // Subtraction
    vi5 = vi1 - vi2;
    EXPECT_NEAR(vi5.x, -1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, -1.5f, FLOAT_ABS_ERROR);
    vi5 -= vi3;
    EXPECT_NEAR(vi5.x, -3.5005f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -4.635f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, -3.0f, FLOAT_ABS_ERROR);
    vi5 -= vi4;
    EXPECT_NEAR(vi5.x, 1.002f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 0.49f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, -1.0f, FLOAT_ABS_ERROR);
    // Multiplication
    vi5 = vi2 * 4.0f;
    EXPECT_NEAR(vi5.x, 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 6.0f, FLOAT_ABS_ERROR);
    vi5 = 5.0f * vi2;
    EXPECT_NEAR(vi5.x, 7.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 7.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 7.5f, FLOAT_ABS_ERROR);
    vi5 *= 4.0f;
    EXPECT_NEAR(vi5.x, 30.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 30.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 30.0f, FLOAT_ABS_ERROR);
    vi5 = vi1 * vi2;
    EXPECT_NEAR(vi5.x, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 0.0f, FLOAT_ABS_ERROR);
    vi5 = Vec3f(2.0f, 3.0f, 4.0f) * Vec3f(4.0f, 5.0f, 6.0f);
    EXPECT_NEAR(vi5.x, 8.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 15.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 24.0f, FLOAT_ABS_ERROR);
    vi5 *= Vec3f(2.0f, 3.0f, 4.0f);
    EXPECT_NEAR(vi5.x, 16.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 45.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 96.0f, FLOAT_ABS_ERROR);
    // Division
    vi5 = Vec3f(12.0f, 20.0f, 36.0f);
    EXPECT_NEAR((vi5 / 4.0f).x, 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR((vi5 / 4.0f).y, 5.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR((vi5 / 4.0f).z, 9.0f, FLOAT_ABS_ERROR);
    vi5 /= 2.0f;
    EXPECT_NEAR(vi5.x, 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 10.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 18.0f, FLOAT_ABS_ERROR);
    vi5 = Vec3f(12.0f, 20.0f, 36.0f) / Vec3f(4.0f, 5.0f, 6.0f);
    EXPECT_NEAR(vi5.x, 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 4.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 6.0f, FLOAT_ABS_ERROR);
    vi5 = Vec3f(12.0f, 20.0f, 36.0f);
    vi5 /= Vec3f(3.0f, 4.0f, 6.0f);
    EXPECT_NEAR(vi5.x, 4.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 5.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 6.0f, FLOAT_ABS_ERROR);
    // Negation
    vi5 = -vi2;
    EXPECT_NEAR(vi5.x, -1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, -1.5f, FLOAT_ABS_ERROR);
    vi5 = -vi4;
    EXPECT_NEAR(vi5.x, 4.5025f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 5.125f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 2.0f, FLOAT_ABS_ERROR);
    vi5 = -vi1;
    EXPECT_NEAR(vi5.x, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.z, 0.0f, FLOAT_ABS_ERROR);
    // Equality (using exactly representable values to avoid float precision issues)
    EXPECT_TRUE(vi1 == Vec3f(0.0f, 0.0f, 0.0f));
    EXPECT_TRUE(vi2 == Vec3f(1.5f, 1.5f, 1.5f));
    EXPECT_FALSE(vi1 == vi2);
    EXPECT_FALSE(vi2 == vi3);
    // Inequality
    EXPECT_TRUE(vi1 != vi2);
    EXPECT_TRUE(vi2 != vi3);
    EXPECT_FALSE(vi1 != Vec3f(0.0f, 0.0f, 0.0f));
    EXPECT_FALSE(vi2 != Vec3f(1.5f, 1.5f, 1.5f));
}

TEST_F(Vec3Test, DoubleLength) {
    Vec3d vd1 = Vec3d(10);
    EXPECT_NEAR(vd1.length(), 17.320508075688773, DOUBLE_ABS_ERROR);
    vd1 = Vec3d(-10);
    EXPECT_NEAR(vd1.length(), 17.320508075688773, DOUBLE_ABS_ERROR);
    vd1 = Vec3d();
    EXPECT_DOUBLE_EQ(vd1.length(), 0);
    // Const check
    const Vec3d vd2 = Vec3d(5);
    EXPECT_NEAR(vd2.length(), 8.660254037844387, DOUBLE_ABS_ERROR);
}

TEST_F(Vec3Test, DoubleNormalize) {
    Vec3d vd1 = Vec3d(3.0, 2.0, 1.0);
    vd1.normalize();
    EXPECT_NEAR(vd1.x, 0.8017837257372732, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1.y, 0.5345224838248488, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1.z, 0.2672612419124244, DOUBLE_ABS_ERROR);
    Vec3d vd2 = Vec3d(100.0, -214.0, 50.0);
    vd2.normalize();
    EXPECT_NEAR(vd2.x, 0.4141718918231853, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2.y, -0.8863278485016166, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2.z, 0.20708594591159266, DOUBLE_ABS_ERROR);
    Vec3d vd3 = Vec3d();
    vd3.normalize();
    EXPECT_EQ(vd3.x, 0);
    EXPECT_EQ(vd3.y, 0);
    EXPECT_EQ(vd3.z, 0);
    // Function
    Vec3d vd4 = normalize(vd2);
    EXPECT_NEAR(vd4.x, 0.4141718918231853, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd4.y, -0.8863278485016166, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd4.z, 0.20708594591159266, DOUBLE_ABS_ERROR);
    // Const check
    const Vec3d vd5 = Vec3d(100, -214, 50);
    Vec3d vd6 = normalize(vd5);
    EXPECT_NEAR(vd6.x, 0.4141718918231853, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd6.y, -0.8863278485016166, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd6.z, 0.20708594591159266, DOUBLE_ABS_ERROR);
}

TEST_F(Vec3Test, DoubleDot) {
    Vec3d vd1 = Vec3d(1);
    Vec3d vd2 = Vec3d(2);
    EXPECT_EQ(vd1.dot(vd2), 6);
    // Function
    EXPECT_EQ(dot(vd1, vd2), 6);
    // Const check
    const Vec3d vd3 = Vec3d(3, 4, 5);
    EXPECT_EQ(vd3.dot(vd1), 12);
}

TEST_F(Vec3Test, DoubleCross) {
    Vec3d vd1 = Vec3d(1, 0, 0);
    Vec3d vd2 = Vec3d(0, 1, 0);
    Vec3d vd3 = vd1.cross(vd2);
    EXPECT_NEAR(vd3.x, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd3.y, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd3.z, 1.0, DOUBLE_ABS_ERROR);
    // Anticommutative: a x b = -(b x a)
    Vec3d vd4 = vd2.cross(vd1);
    EXPECT_NEAR(vd4.z, -1.0, DOUBLE_ABS_ERROR);
    // Function
    Vec3d vd5 = cross(vd1, Vec3d(0, 0, 1));
    EXPECT_NEAR(vd5.x, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 0.0, DOUBLE_ABS_ERROR);
    // Const check
    const Vec3d vd6 = Vec3d(1, 2, 3);
    const Vec3d vd7 = Vec3d(4, 5, 6);
    Vec3d vd8 = vd6.cross(vd7);
    EXPECT_NEAR(vd8.x, -3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd8.y, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd8.z, -3.0, DOUBLE_ABS_ERROR);
}

TEST_F(Vec3Test, DoubleOperations) {
    Vec3d vd1 = Vec3d();
    Vec3d vd2 = Vec3d(1.5);
    Vec3d vd3 = Vec3d(2.0005, 3.135, 1.5);
    Vec3d vd4 = Vec3d(-4.5025, -5.125, -2.0);
    // Addition
    Vec3d vd5 = vd1 + vd2;
    EXPECT_NEAR(vd5.x, 1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 1.5, DOUBLE_ABS_ERROR);
    vd5 += vd3;
    EXPECT_NEAR(vd5.x, 3.5005, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 4.635, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 3.0, DOUBLE_ABS_ERROR);
    vd5 += vd4;
    EXPECT_NEAR(vd5.x, -1.002, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -0.49, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 1.0, DOUBLE_ABS_ERROR);
    // Subtraction
    vd5 = vd1 - vd2;
    EXPECT_NEAR(vd5.x, -1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, -1.5, DOUBLE_ABS_ERROR);
    vd5 -= vd3;
    EXPECT_NEAR(vd5.x, -3.5005, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -4.635, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, -3.0, DOUBLE_ABS_ERROR);
    vd5 -= vd4;
    EXPECT_NEAR(vd5.x, 1.002, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 0.49, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, -1.0, DOUBLE_ABS_ERROR);
    // Multiplication
    vd5 = vd2 * 4.0;
    EXPECT_NEAR(vd5.x, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 6.0, DOUBLE_ABS_ERROR);
    vd5 = 5.0 * vd2;
    EXPECT_NEAR(vd5.x, 7.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 7.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 7.5, DOUBLE_ABS_ERROR);
    vd5 *= 4.0;
    EXPECT_NEAR(vd5.x, 30.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 30.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 30.0, DOUBLE_ABS_ERROR);
    vd5 = vd1 * vd2;
    EXPECT_NEAR(vd5.x, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 0.0, DOUBLE_ABS_ERROR);
    vd5 = Vec3d(2.0, 3.0, 4.0) * Vec3d(4.0, 5.0, 6.0);
    EXPECT_NEAR(vd5.x, 8.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 15.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 24.0, DOUBLE_ABS_ERROR);
    vd5 *= Vec3d(2.0, 3.0, 4.0);
    EXPECT_NEAR(vd5.x, 16.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 45.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 96.0, DOUBLE_ABS_ERROR);
    // Division
    vd5 = Vec3d(12.0, 20.0, 36.0);
    EXPECT_NEAR((vd5 / 4.0).x, 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR((vd5 / 4.0).y, 5.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR((vd5 / 4.0).z, 9.0, DOUBLE_ABS_ERROR);
    vd5 /= 2.0;
    EXPECT_NEAR(vd5.x, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 10.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 18.0, DOUBLE_ABS_ERROR);
    vd5 = Vec3d(12.0, 20.0, 36.0) / Vec3d(4.0, 5.0, 6.0);
    EXPECT_NEAR(vd5.x, 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 4.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 6.0, DOUBLE_ABS_ERROR);
    vd5 = Vec3d(12.0, 20.0, 36.0);
    vd5 /= Vec3d(3.0, 4.0, 6.0);
    EXPECT_NEAR(vd5.x, 4.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 5.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 6.0, DOUBLE_ABS_ERROR);
    // Negation
    vd5 = -vd2;
    EXPECT_NEAR(vd5.x, -1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, -1.5, DOUBLE_ABS_ERROR);
    vd5 = -vd4;
    EXPECT_NEAR(vd5.x, 4.5025, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 5.125, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 2.0, DOUBLE_ABS_ERROR);
    vd5 = -vd1;
    EXPECT_NEAR(vd5.x, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.z, 0.0, DOUBLE_ABS_ERROR);
    // Equality (using exactly representable values to avoid precision issues)
    EXPECT_TRUE(vd1 == Vec3d(0.0, 0.0, 0.0));
    EXPECT_TRUE(vd2 == Vec3d(1.5, 1.5, 1.5));
    EXPECT_FALSE(vd1 == vd2);
    EXPECT_FALSE(vd2 == vd3);
    // Inequality
    EXPECT_TRUE(vd1 != vd2);
    EXPECT_TRUE(vd2 != vd3);
    EXPECT_FALSE(vd1 != Vec3d(0.0, 0.0, 0.0));
    EXPECT_FALSE(vd2 != Vec3d(1.5, 1.5, 1.5));
}

TEST_F(Vec3Test, ApproxEq) {
    // Int
    Vec3i vi1 = Vec3i(1);
    Vec3i vi2 = Vec3i(1);
    Vec3i vi3 = Vec3i(2);
    EXPECT_TRUE(approxEq(vi1, vi2, 0));
    EXPECT_TRUE(approxEq(vi1, vi3, 2));
    EXPECT_FALSE(approxEq(vi1, vi3, 0));
    // Float
    Vec3f vf1 = Vec3f(4.5f, 5.5f, 3.0f);
    Vec3f vf2 = Vec3f(4.500001f, 5.500001f, 3.000001f);
    EXPECT_TRUE(approxEq(vf1, vf2, 0.000001f));
    EXPECT_FALSE(approxEq(vf1, vf2, 0.0000001f));
    // Double
    Vec3d vd1 = Vec3d(4.5, 5.5, 3.0);
    Vec3d vd2 = Vec3d(4.500000000000001, 5.500000000000001, 3.000000000000001);
    EXPECT_TRUE(approxEq(vd1, vd2, 0.000000000000001));
    EXPECT_FALSE(approxEq(vd1, vd2, 0.0000000000000001));
}
