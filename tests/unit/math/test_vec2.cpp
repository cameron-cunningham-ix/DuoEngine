#include <gtest/gtest.h>

#include "include/math/Vec2.hpp"

class Vec2Test : public testing::Test { };

using namespace RendMath;
constexpr const float FLOAT_ABS_ERROR = std::numeric_limits<float>::epsilon() * 2.0f;
constexpr const double DOUBLE_ABS_ERROR = std::numeric_limits<double>::epsilon() * 4.0;

TEST_F(Vec2Test, DefaultConstructor) {
    Vec2i v1 = Vec2i();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
    Vec2f v2 = Vec2f();
    EXPECT_EQ(v2.x, 0);
    EXPECT_EQ(v2.y, 0);
    Vec2d v3 = Vec2d();
    EXPECT_EQ(v3.x, 0);
    EXPECT_EQ(v3.y, 0);
}

TEST_F(Vec2Test, IntDot) {
    Vec2i vi1 = Vec2i(10);
    Vec2i vi2 = Vec2i(10);
    EXPECT_EQ(vi1.dot(vi2), 200);
    Vec2i vi3 = Vec2i(5.5f, 4.3f);
    EXPECT_EQ(vi1.dot(vi3), 90);
    Vec2i vi4 = Vec2i();
    EXPECT_EQ(vi1.dot(vi4), 0);
}

TEST_F(Vec2Test, Index) {
    // Int
    Vec2i vi1 = Vec2i(5, 7);
    EXPECT_EQ(vi1[0], 5);
    EXPECT_EQ(vi1[1], 7);
    EXPECT_THROW(vi1[-1], std::out_of_range);
    EXPECT_THROW(vi1[2], std::out_of_range);
    // Const check
    const Vec2i vi2 = Vec2(3, 4);
    EXPECT_EQ(vi2[0], 3);
    EXPECT_EQ(vi2[1], 4);
    // Float
    Vec2f vf1 = Vec2f(5.5333333f, 7.1200002f);
    EXPECT_NEAR(vf1[0], 5.5333333f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1[1], 7.1200002f, FLOAT_ABS_ERROR);
    EXPECT_THROW(vf1[-1], std::out_of_range);
    EXPECT_THROW(vf1[2], std::out_of_range);
    // Const check
    const Vec2f vf2 = Vec2f(3.0f, 4.1111f);
    EXPECT_NEAR(vf2[0], 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2[1], 4.1111f, FLOAT_ABS_ERROR);
    // Double
    Vec2d vd1 = Vec2d(5.533333333333333, 7.120000000000002);
    EXPECT_NEAR(vd1[0], 5.533333333333333, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1[1], 7.120000000000002, DOUBLE_ABS_ERROR);
    EXPECT_THROW(vd1[-1], std::out_of_range);
    EXPECT_THROW(vd1[2], std::out_of_range);
    // Const check
    const Vec2d vd2 = Vec2d(3.0, 4.1111);
    EXPECT_NEAR(vd2[0], 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2[1], 4.1111, DOUBLE_ABS_ERROR);
}

TEST_F(Vec2Test, IntOperators) {
    Vec2i vi1 = Vec2i();
    Vec2i vi2 = Vec2i(1);
    Vec2i vi3 = Vec2i(2, 3);
    Vec2i vi4 = Vec2i(-4, -5);
    // Addition
    Vec2i vi5 = vi1 + vi2;
    EXPECT_EQ(vi5, vi2);
    vi5 += vi3;
    EXPECT_EQ(vi5, Vec2i(3, 4));
    vi5 += vi4;
    EXPECT_EQ(vi5, Vec2i(-1, -1));
    // Subtraction
    vi5 = vi1 - vi2;
    EXPECT_EQ(vi5, -vi2);
    vi5 -= vi3;
    EXPECT_EQ(vi5, Vec2i(-3, -4));
    vi5 -= vi4;
    EXPECT_EQ(vi5, Vec2i(1, 1));
    // Multiplication
    vi5 = vi2 * 4;
    EXPECT_EQ(vi5, Vec2i(4, 4));
    vi5 = 5 * vi2;
    EXPECT_EQ(vi5, Vec2i(5, 5));
    vi5 *= 4;
    EXPECT_EQ(vi5, Vec2i(20, 20));
    vi5 = vi1 * vi2;
    EXPECT_EQ(vi5, vi1);
    vi5 = vi3 * vi4;
    EXPECT_EQ(vi5, Vec2i(-8, -15));
    vi5 *= vi3;
    EXPECT_EQ(vi5, Vec2i(-16, -45));
    // Division
    vi5 = Vec2i(12, 20);
    EXPECT_EQ(vi5 / 4, Vec2i(3, 5));
    vi5 /= 2;
    EXPECT_EQ(vi5, Vec2i(6, 10));
    vi5 = Vec2i(12, 20) / Vec2i(4, 5);
    EXPECT_EQ(vi5, Vec2i(3, 4));
    vi5 = Vec2i(12, 20);
    vi5 /= Vec2i(3, 4);
    EXPECT_EQ(vi5, Vec2i(4, 5));
    // Negation
    EXPECT_EQ(-vi2, Vec2i(-1, -1));
    EXPECT_EQ(-vi4, Vec2i(4, 5));
    EXPECT_EQ(-vi1, vi1);
    // Equality
    EXPECT_EQ((vi1 == Vec2i(0,0)), true);
    EXPECT_EQ((vi2 == Vec2i(1, 1)), true);
    EXPECT_EQ((vi1 == Vec2i(2, 3)), false);
    EXPECT_EQ((vi1 == vi2), false);
    // Inequality
    Vec2i vi6 = Vec2i(1, 1);
    EXPECT_EQ((vi1 != vi2), true);
    EXPECT_EQ((vi2 != vi6), false);
    EXPECT_EQ((vi2 != Vec2i(1)), false);
}

TEST_F(Vec2Test, FloatLength) {
    Vec2f vf1 = Vec2f(10);
    EXPECT_FLOAT_EQ(vf1.length(), 14.142135f);
    vf1 = Vec2f(-10);
    EXPECT_FLOAT_EQ(vf1.length(), 14.142135f);
    vf1 = Vec2f();
    EXPECT_FLOAT_EQ(vf1.length(), 0);
    // Const check
    const Vec2f vf2 = Vec2f(5);
    EXPECT_FLOAT_EQ(vf2.length(), 7.0710678f);
}

TEST_F(Vec2Test, FloatNormalize) {
    Vec2f vf1 = Vec2f(3, 2);
    vf1.normalize();
    EXPECT_NEAR(vf1.x, 0.8320502f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1.y, 0.5547001f, FLOAT_ABS_ERROR);
    Vec2f vf2 = Vec2f(100, -214);
    vf2.normalize();
    EXPECT_NEAR(vf2.x, 0.423349f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2.y, -0.9059668f, FLOAT_ABS_ERROR);
    Vec2f vf3 = Vec2f();
    vf3.normalize();
    EXPECT_EQ(vf3.x, 0);
    EXPECT_EQ(vf3.y, 0);
    // Function
    Vec2f vf4 = normalize(vf2);
    EXPECT_NEAR(vf4.x, 0.423349f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf4.y, -0.9059668f, FLOAT_ABS_ERROR);
    // Const check
    const Vec2f vf5 = Vec2f(100, -214);
    Vec2f vf6 = normalize(vf5);
    EXPECT_NEAR(vf6.x, 0.423349f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf6.y, -0.9059668f, FLOAT_ABS_ERROR);
}

TEST_F(Vec2Test, FloatDot) {
    Vec2f vf1 = Vec2f(1);
    Vec2f vf2 = Vec2f(2);
    EXPECT_EQ(vf1.dot(vf2), 4);
    // Function
    EXPECT_EQ(dot(vf1, vf2), 4);
    // Const check
    const Vec2f vf3 = Vec2f(3, 4);
    EXPECT_EQ(vf3.dot(vf1), 7);
}

TEST_F(Vec2Test, FloatLerp) {
    Vec2f vf1 = Vec2f();
    Vec2f vf2 = Vec2f(1);
    Vec2f vf3 = Vec2f(10.0f, 5.0f);

    vf1.lerp(vf2, 0.1);
    EXPECT_NEAR(vf1.x, 0.1f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1.y, 0.1f, FLOAT_ABS_ERROR);
    vf1.lerp(vf2, 1);
    EXPECT_NEAR(vf1.x, 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf1.y, 1.0f, FLOAT_ABS_ERROR);
}

TEST_F(Vec2Test, FloatOperations) {
    Vec2f vi1 = Vec2f();
    Vec2f vi2 = Vec2f(1.5f);
    Vec2f vi3 = Vec2f(2.0005f, 3.135f);
    Vec2f vi4 = Vec2f(-4.5025f, -5.125f);
    // Addition
    Vec2f vi5 = vi1 + vi2;
    EXPECT_NEAR(vi5.x, 1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 1.5f, FLOAT_ABS_ERROR);
    vi5 += vi3;
    EXPECT_NEAR(vi5.x, 3.5005f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 4.635f, FLOAT_ABS_ERROR);
    vi5 += vi4;
    EXPECT_NEAR(vi5.x, -1.002f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -0.490f, FLOAT_ABS_ERROR);
    // Subtraction
    vi5 = vi1 - vi2;
    EXPECT_NEAR(vi5.x, -1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -1.5f, FLOAT_ABS_ERROR);
    vi5 -= vi3;
    EXPECT_NEAR(vi5.x, -3.5005f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -4.635f, FLOAT_ABS_ERROR);
    vi5 -= vi4;
    EXPECT_NEAR(vi5.x, 1.002f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 0.49f, FLOAT_ABS_ERROR);
    // Multiplication
    vi5 = vi2 * 4.0f;
    EXPECT_NEAR(vi5.x, 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 6.0f, FLOAT_ABS_ERROR);
    vi5 = 5.0f * vi2;
    EXPECT_NEAR(vi5.x, 7.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 7.5f, FLOAT_ABS_ERROR);
    vi5 *= 4.0f;
    EXPECT_NEAR(vi5.x, 30.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 30.0f, FLOAT_ABS_ERROR);
    vi5 = vi1 * vi2;
    EXPECT_NEAR(vi5.x, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 0.0f, FLOAT_ABS_ERROR);
    vi5 = Vec2f(2.0f, 3.0f) * Vec2f(4.0f, 5.0f);
    EXPECT_NEAR(vi5.x, 8.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 15.0f, FLOAT_ABS_ERROR);
    vi5 *= Vec2f(2.0f, 3.0f);
    EXPECT_NEAR(vi5.x, 16.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 45.0f, FLOAT_ABS_ERROR);
    // Division
    vi5 = Vec2f(12.0f, 20.0f);
    EXPECT_NEAR((vi5 / 4.0f).x, 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR((vi5 / 4.0f).y, 5.0f, FLOAT_ABS_ERROR);
    vi5 /= 2.0f;
    EXPECT_NEAR(vi5.x, 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 10.0f, FLOAT_ABS_ERROR);
    vi5 = Vec2f(12.0f, 20.0f) / Vec2f(4.0f, 5.0f);
    EXPECT_NEAR(vi5.x, 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 4.0f, FLOAT_ABS_ERROR);
    vi5 = Vec2f(12.0f, 20.0f);
    vi5 /= Vec2f(3.0f, 4.0f);
    EXPECT_NEAR(vi5.x, 4.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 5.0f, FLOAT_ABS_ERROR);
    // Negation
    vi5 = -vi2;
    EXPECT_NEAR(vi5.x, -1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, -1.5f, FLOAT_ABS_ERROR);
    vi5 = -vi4;
    EXPECT_NEAR(vi5.x, 4.5025f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 5.125f, FLOAT_ABS_ERROR);
    vi5 = -vi1;
    EXPECT_NEAR(vi5.x, 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vi5.y, 0.0f, FLOAT_ABS_ERROR);
    // Equality (using exactly representable values to avoid float precision issues)
    EXPECT_TRUE(vi1 == Vec2f(0.0f, 0.0f));
    EXPECT_TRUE(vi2 == Vec2f(1.5f, 1.5f));
    EXPECT_FALSE(vi1 == vi2);
    EXPECT_FALSE(vi2 == vi3);
    // Inequality
    EXPECT_TRUE(vi1 != vi2);
    EXPECT_TRUE(vi2 != vi3);
    EXPECT_FALSE(vi1 != Vec2f(0.0f, 0.0f));
    EXPECT_FALSE(vi2 != Vec2f(1.5f, 1.5f));
}

TEST_F(Vec2Test, DoubleLength) {
    Vec2d vd1 = Vec2d(10);
    EXPECT_NEAR(vd1.length(), 14.142135623730951, DOUBLE_ABS_ERROR);
    vd1 = Vec2d(-10);
    EXPECT_NEAR(vd1.length(), 14.142135623730951, DOUBLE_ABS_ERROR);
    vd1 = Vec2d();
    EXPECT_DOUBLE_EQ(vd1.length(), 0);
    // Const check
    const Vec2d vd2 = Vec2d(5);
    EXPECT_NEAR(vd2.length(), 7.0710678118654755, DOUBLE_ABS_ERROR);
}

TEST_F(Vec2Test, DoubleNormalize) {
    Vec2d vd1 = Vec2d(3.0, 2.0);
    vd1.normalize();
    EXPECT_NEAR(vd1.x, 0.8320502943378437, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1.y, 0.5547001962252291, DOUBLE_ABS_ERROR);
    Vec2d vd2 = Vec2d(100.0, -214.0);
    vd2.normalize();
    EXPECT_NEAR(vd2.x, 0.423348930736043, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2.y, -0.905966711775133, DOUBLE_ABS_ERROR);
    Vec2d vd3 = Vec2d();
    vd3.normalize();
    EXPECT_EQ(vd3.x, 0);
    EXPECT_EQ(vd3.y, 0);
    // Function
    Vec2d vd4 = normalize(vd2);
    EXPECT_NEAR(vd4.x, 0.423348930736043, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd4.y, -0.905966711775133, DOUBLE_ABS_ERROR);
    // Const check
    const Vec2d vd5 = Vec2d(100, -214);
    Vec2d vd6 = normalize(vd5);
    EXPECT_NEAR(vd6.x, 0.423348930736043, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd6.y, -0.905966711775133, DOUBLE_ABS_ERROR);
}

TEST_F(Vec2Test, DoubleDot) {
    Vec2d vd1 = Vec2d(1);
    Vec2d vd2 = Vec2d(2);
    EXPECT_EQ(vd1.dot(vd2), 4);
    // Function
    EXPECT_EQ(dot(vd1, vd2), 4);
    // Const check
    const Vec2d vd3 = Vec2d(3, 4);
    EXPECT_EQ(vd3.dot(vd1), 7);
}

TEST_F(Vec2Test, DoubleLerp) {
    Vec2d vd1 = Vec2d();
    Vec2d vd2 = Vec2d(1.0);
    Vec2d vd3 = Vec2d(10.0, 5.0);

    vd1.lerp(vd2, 0.1);
    EXPECT_NEAR(vd1.x, 0.1, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1.y, 0.1, DOUBLE_ABS_ERROR);
    vd1.lerp(vd2, 0);
    EXPECT_NEAR(vd1.x, 0.1, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1.y, 0.1, DOUBLE_ABS_ERROR);
    vd1.lerp(vd2, 1);
    EXPECT_NEAR(vd1.x, 1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd1.y, 1.0, DOUBLE_ABS_ERROR);
}

TEST_F(Vec2Test, DoubleOperations) {
    Vec2d vd1 = Vec2d();
    Vec2d vd2 = Vec2d(1.5);
    Vec2d vd3 = Vec2d(2.0005, 3.135);
    Vec2d vd4 = Vec2d(-4.5025, -5.125);
    // Addition
    Vec2d vd5 = vd1 + vd2;
    EXPECT_NEAR(vd5.x, 1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 1.5, DOUBLE_ABS_ERROR);
    vd5 += vd3;
    EXPECT_NEAR(vd5.x, 3.5005, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 4.635, DOUBLE_ABS_ERROR);
    vd5 += vd4;
    EXPECT_NEAR(vd5.x, -1.002, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -0.49, DOUBLE_ABS_ERROR);
    // Subtraction
    vd5 = vd1 - vd2;
    EXPECT_NEAR(vd5.x, -1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -1.5, DOUBLE_ABS_ERROR);
    vd5 -= vd3;
    EXPECT_NEAR(vd5.x, -3.5005, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -4.635, DOUBLE_ABS_ERROR);
    vd5 -= vd4;
    EXPECT_NEAR(vd5.x, 1.002, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 0.49, DOUBLE_ABS_ERROR);
    // Multiplication
    vd5 = vd2 * 4.0;
    EXPECT_NEAR(vd5.x, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 6.0, DOUBLE_ABS_ERROR);
    vd5 = 5.0 * vd2;
    EXPECT_NEAR(vd5.x, 7.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 7.5, DOUBLE_ABS_ERROR);
    vd5 *= 4.0;
    EXPECT_NEAR(vd5.x, 30.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 30.0, DOUBLE_ABS_ERROR);
    vd5 = vd1 * vd2;
    EXPECT_NEAR(vd5.x, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 0.0, DOUBLE_ABS_ERROR);
    vd5 = Vec2d(2.0, 3.0) * Vec2d(4.0, 5.0);
    EXPECT_NEAR(vd5.x, 8.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 15.0, DOUBLE_ABS_ERROR);
    vd5 *= Vec2d(2.0, 3.0);
    EXPECT_NEAR(vd5.x, 16.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 45.0, DOUBLE_ABS_ERROR);
    // Division
    vd5 = Vec2d(12.0, 20.0);
    EXPECT_NEAR((vd5 / 4.0).x, 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR((vd5 / 4.0).y, 5.0, DOUBLE_ABS_ERROR);
    vd5 /= 2.0;
    EXPECT_NEAR(vd5.x, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 10.0, DOUBLE_ABS_ERROR);
    vd5 = Vec2d(12.0, 20.0) / Vec2d(4.0, 5.0);
    EXPECT_NEAR(vd5.x, 3.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 4.0, DOUBLE_ABS_ERROR);
    vd5 = Vec2d(12.0, 20.0);
    vd5 /= Vec2d(3.0, 4.0);
    EXPECT_NEAR(vd5.x, 4.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 5.0, DOUBLE_ABS_ERROR);
    // Negation
    vd5 = -vd2;
    EXPECT_NEAR(vd5.x, -1.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, -1.5, DOUBLE_ABS_ERROR);
    vd5 = -vd4;
    EXPECT_NEAR(vd5.x, 4.5025, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 5.125, DOUBLE_ABS_ERROR);
    vd5 = -vd1;
    EXPECT_NEAR(vd5.x, 0.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd5.y, 0.0, DOUBLE_ABS_ERROR);
    // Equality (using exactly representable values to avoid precision issues)
    EXPECT_TRUE(vd1 == Vec2d(0.0, 0.0));
    EXPECT_TRUE(vd2 == Vec2d(1.5, 1.5));
    EXPECT_FALSE(vd1 == vd2);
    EXPECT_FALSE(vd2 == vd3);
    // Inequality
    EXPECT_TRUE(vd1 != vd2);
    EXPECT_TRUE(vd2 != vd3);
    EXPECT_FALSE(vd1 != Vec2d(0.0, 0.0));
    EXPECT_FALSE(vd2 != Vec2d(1.5, 1.5));
}

TEST_F(Vec2Test, ApproxEq) {
    // Int
    Vec2i vi1 = Vec2i(1);
    Vec2i vi2 = Vec2i(1);
    Vec2i vi3 = Vec2i(2);
    EXPECT_TRUE(approxEq(vi1, vi2, 0));
    EXPECT_TRUE(approxEq(vi1, vi3, 2));
    EXPECT_FALSE(approxEq(vi1, vi3, 0));
    // Float
    Vec2f vf1 = Vec2f(4.5f, 5.5f);
    Vec2f vf2 = Vec2f(4.500001f, 5.500001f);
    EXPECT_TRUE(approxEq(vf1, vf2, 0.000001f));
    EXPECT_FALSE(approxEq(vf1, vf2, 0.0000001f));
    // Double
    Vec2d vd1 = Vec2d(4.5, 5.5);
    Vec2d vd2 = Vec2d(4.500000000000001, 5.500000000000001);
    EXPECT_TRUE(approxEq(vd1, vd2, 0.000000000000001));
    EXPECT_FALSE(approxEq(vd1, vd2, 0.0000000000000001));
}

TEST_F(Vec2Test, Conversions) {
    // Int to float
    Vec2i vi1 = Vec2i(10, 20);
    Vec2f vf1 = (Vec2f)(vi1);
    EXPECT_EQ(vf1, Vec2f(10.0f, 20.0f));
    // Int to double
    Vec2d vd1 = (Vec2d)(vi1);
    EXPECT_EQ(vd1, Vec2d(10.0, 20.0));
    // Float to int
    Vec2f vf2 = Vec2f(25.5f, 15.5f);
    Vec2i vi2 = (Vec2i)(vf2);
    EXPECT_EQ(vi2, Vec2i(25, 15));
    // Float to double
    Vec2d vd2 = (Vec2d)(vf2);
    EXPECT_EQ(vd2, Vec2d(25.5, 15.5));
    // Double to int
    Vec2d vd3 = Vec2d(15.6, 18.9);
    Vec2i vi3 = (Vec2i)(vd3);
    EXPECT_EQ(vi3, Vec2i(15, 18));
    // Double to float
    Vec2f vf3 = (Vec2f)(vd3);
    EXPECT_EQ(vf3, Vec2f(15.6f, 18.9f));
}