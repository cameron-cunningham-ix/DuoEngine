#include <gtest/gtest.h>
#include <cmath>
#include <numbers>

#include "include/math/Mat4.hpp"

class Mat4Test : public testing::Test { };

using namespace RendMath;
constexpr const float FLOAT_ABS_ERROR = std::numeric_limits<float>::epsilon() * 2.0f;
constexpr const double DOUBLE_ABS_ERROR = std::numeric_limits<double>::epsilon() * 4.0;
static const float PI = std::numbers::pi_v<float>;

TEST_F(Mat4Test, Constructors) {
    // Int
    Mat4i mi1;
    EXPECT_EQ(mi1, Mat4i(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1));
    EXPECT_EQ(mi1, Mat4i::identity());
    Mat4i mi2(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    EXPECT_EQ(mi2(0,0), 1);  EXPECT_EQ(mi2(0,1), 2);  EXPECT_EQ(mi2(0,2), 3);  EXPECT_EQ(mi2(0,3), 4);
    EXPECT_EQ(mi2(1,0), 5);  EXPECT_EQ(mi2(1,1), 6);  EXPECT_EQ(mi2(1,2), 7);  EXPECT_EQ(mi2(1,3), 8);
    EXPECT_EQ(mi2(2,0), 9);  EXPECT_EQ(mi2(2,1), 10); EXPECT_EQ(mi2(2,2), 11); EXPECT_EQ(mi2(2,3), 12);
    EXPECT_EQ(mi2(3,0), 13); EXPECT_EQ(mi2(3,1), 14); EXPECT_EQ(mi2(3,2), 15); EXPECT_EQ(mi2(3,3), 16);
    // Float
    Mat4f mf1;
    EXPECT_EQ(mf1, Mat4f(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1));
    EXPECT_EQ(mf1, Mat4f::identity());
    // Double
    Mat4d md1;
    EXPECT_EQ(md1, Mat4d(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1));
    EXPECT_EQ(md1, Mat4d::identity());
}

TEST_F(Mat4Test, Index) {
    // Int identity
    Mat4i mi1;
    EXPECT_EQ(mi1(0,0), 1); EXPECT_EQ(mi1(0,1), 0); EXPECT_EQ(mi1(0,2), 0); EXPECT_EQ(mi1(0,3), 0);
    EXPECT_EQ(mi1(1,0), 0); EXPECT_EQ(mi1(1,1), 1); EXPECT_EQ(mi1(1,2), 0); EXPECT_EQ(mi1(1,3), 0);
    EXPECT_EQ(mi1(2,0), 0); EXPECT_EQ(mi1(2,1), 0); EXPECT_EQ(mi1(2,2), 1); EXPECT_EQ(mi1(2,3), 0);
    EXPECT_EQ(mi1(3,0), 0); EXPECT_EQ(mi1(3,1), 0); EXPECT_EQ(mi1(3,2), 0); EXPECT_EQ(mi1(3,3), 1);
    mi1(0,0) = 5;
    EXPECT_EQ(mi1(0,0), 5);
    // Const check
    const Mat4i mi2(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    EXPECT_EQ(mi2(0,0), 1);  EXPECT_EQ(mi2(0,1), 2);  EXPECT_EQ(mi2(0,2), 3);  EXPECT_EQ(mi2(0,3), 4);
    EXPECT_EQ(mi2(1,0), 5);  EXPECT_EQ(mi2(1,1), 6);  EXPECT_EQ(mi2(1,2), 7);  EXPECT_EQ(mi2(1,3), 8);
    EXPECT_EQ(mi2(2,0), 9);  EXPECT_EQ(mi2(2,1), 10); EXPECT_EQ(mi2(2,2), 11); EXPECT_EQ(mi2(2,3), 12);
    EXPECT_EQ(mi2(3,0), 13); EXPECT_EQ(mi2(3,1), 14); EXPECT_EQ(mi2(3,2), 15); EXPECT_EQ(mi2(3,3), 16);
    // Float
    Mat4f mf1(1.5f,2.5f,3.5f,4.5f, 5.5f,6.5f,7.5f,8.5f, 9.5f,10.5f,11.5f,12.5f, 13.5f,14.5f,15.5f,16.5f);
    EXPECT_NEAR(mf1(0,0), 1.5f,  FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(1,1), 6.5f,  FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(2,2), 11.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(3,3), 16.5f, FLOAT_ABS_ERROR);
    mf1(1,2) = 99.0f;
    EXPECT_NEAR(mf1(1,2), 99.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1(1.1,2.2,3.3,4.4, 5.5,6.6,7.7,8.8, 9.9,10.0,11.11,12.12, 13.13,14.14,15.15,16.16);
    EXPECT_NEAR(md1(0,0), 1.1,   DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(1,1), 6.6,   DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(2,2), 11.11, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(3,3), 16.16, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, Identity) {
    // Int: all 16 elements
    Mat4i mi1 = Mat4i::identity();
    EXPECT_EQ(mi1(0,0), 1); EXPECT_EQ(mi1(0,1), 0); EXPECT_EQ(mi1(0,2), 0); EXPECT_EQ(mi1(0,3), 0);
    EXPECT_EQ(mi1(1,0), 0); EXPECT_EQ(mi1(1,1), 1); EXPECT_EQ(mi1(1,2), 0); EXPECT_EQ(mi1(1,3), 0);
    EXPECT_EQ(mi1(2,0), 0); EXPECT_EQ(mi1(2,1), 0); EXPECT_EQ(mi1(2,2), 1); EXPECT_EQ(mi1(2,3), 0);
    EXPECT_EQ(mi1(3,0), 0); EXPECT_EQ(mi1(3,1), 0); EXPECT_EQ(mi1(3,2), 0); EXPECT_EQ(mi1(3,3), 1);
    // Float
    Mat4f mf1 = Mat4f::identity();
    EXPECT_NEAR(mf1(0,0), 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(1,1), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(2,2), 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(3,3), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(0,1), 0.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(0,3), 0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(3,0), 0.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(2,3), 0.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1 = Mat4d::identity();
    EXPECT_NEAR(md1(0,0), 1.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md1(1,1), 1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(2,2), 1.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md1(3,3), 1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(0,1), 0.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md1(3,0), 0.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, MatrixMult) {
    // Int
    Mat4i mi1 = Mat4i::identity();
    EXPECT_EQ(mi1 * mi1, Mat4i::identity());
    Mat4i mi2(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    EXPECT_EQ(mi1 * mi2, mi2);
    EXPECT_EQ(mi2 * mi1, mi2);
    // Non-trivial: shear A * shear B
    // A = [[1,2,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]
    // B = [[-1,2,0,0],[0,3,0,0],[0,0,1,0],[0,0,0,1]]
    // A*B = [[-1,8,0,0],[0,3,0,0],[0,0,1,0],[0,0,0,1]]
    Mat4i mi3(1,2,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    Mat4i mi4(-1,2,0,0, 0,3,0,0, 0,0,1,0, 0,0,0,1);
    Mat4i mi5 = mi3 * mi4;
    EXPECT_EQ(mi5(0,0), -1); EXPECT_EQ(mi5(0,1), 8); EXPECT_EQ(mi5(0,2), 0); EXPECT_EQ(mi5(0,3), 0);
    EXPECT_EQ(mi5(1,0),  0); EXPECT_EQ(mi5(1,1), 3); EXPECT_EQ(mi5(1,2), 0); EXPECT_EQ(mi5(1,3), 0);
    EXPECT_EQ(mi5(2,0),  0); EXPECT_EQ(mi5(2,1), 0); EXPECT_EQ(mi5(2,2), 1); EXPECT_EQ(mi5(2,3), 0);
    EXPECT_EQ(mi5(3,0),  0); EXPECT_EQ(mi5(3,1), 0); EXPECT_EQ(mi5(3,2), 0); EXPECT_EQ(mi5(3,3), 1);
    // Float
    Mat4f mf1(1.0f,2.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,0.0f, 0.0f,0.0f,1.0f,0.0f, 0.0f,0.0f,0.0f,1.0f);
    Mat4f mf2(-1.0f,2.0f,0.0f,0.0f, 0.0f,3.0f,0.0f,0.0f, 0.0f,0.0f,1.0f,0.0f, 0.0f,0.0f,0.0f,1.0f);
    Mat4f mf3 = mf1 * mf2;
    EXPECT_NEAR(mf3(0,0), -1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf3(0,1), 8.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf3(1,1),  3.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf3(2,2), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf3(3,3),  1.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1 = Mat4d::identity();
    Mat4d md2(1.0,2.0,3.0,4.0, 5.0,6.0,7.0,8.0, 9.0,10.0,11.0,12.0, 13.0,14.0,15.0,16.0);
    EXPECT_EQ(md1 * md2, md2);
}

TEST_F(Mat4Test, ScalarMult) {
    // Int
    Mat4i mi1 = Mat4i::identity();
    Mat4i mi2 = mi1 * 3;
    EXPECT_EQ(mi2, Mat4i(3,0,0,0, 0,3,0,0, 0,0,3,0, 0,0,0,3));
    Mat4i mi3 = 3 * mi1;
    EXPECT_EQ(mi3, Mat4i(3,0,0,0, 0,3,0,0, 0,0,3,0, 0,0,0,3));
    Mat4i mi4(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    mi4 *= 2;
    EXPECT_EQ(mi4, Mat4i(2,4,6,8, 10,12,14,16, 18,20,22,24, 26,28,30,32));
    // Float
    Mat4f mf1(1.0f,2.0f,3.0f,4.0f, 5.0f,6.0f,7.0f,8.0f, 9.0f,10.0f,11.0f,12.0f, 13.0f,14.0f,15.0f,16.0f);
    Mat4f mf2 = mf1 * 2.0f;
    EXPECT_NEAR(mf2(0,0),  2.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(1,1), 12.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(2,2), 22.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(3,3), 32.0f, FLOAT_ABS_ERROR);
    Mat4f mf3 = 0.5f * mf1;
    EXPECT_NEAR(mf3(0,0), 0.5f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf3(1,1), 3.0f, FLOAT_ABS_ERROR);
    mf1 *= 3.0f;
    EXPECT_NEAR(mf1(0,0),  3.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(3,3), 48.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1(1.0,0.0,0.0,0.0, 0.0,2.0,0.0,0.0, 0.0,0.0,3.0,0.0, 0.0,0.0,0.0,4.0);
    Mat4d md2 = md1 * 4.0;
    EXPECT_NEAR(md2(0,0),  4.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md2(1,1),  8.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(2,2), 12.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md2(3,3), 16.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, VectorMult) {
    // Int: identity leaves vector unchanged
    Mat4i mi1 = Mat4i::identity();
    Vec4i vi1(1, 2, 3, 4);
    EXPECT_EQ(mi1 * vi1, vi1);
    // General: [1..16] * [1,1,1,1] = [10, 26, 42, 58]
    Mat4i mi2(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    Vec4i vi2 = mi2 * Vec4i(1,1,1,1);
    EXPECT_EQ(vi2, Vec4i(10, 26, 42, 58));
    // Diagonal scale
    Mat4i mi3(2,0,0,0, 0,3,0,0, 0,0,4,0, 0,0,0,5);
    Vec4i vi3 = mi3 * Vec4i(2,3,4,5);
    EXPECT_EQ(vi3, Vec4i(4, 9, 16, 25));
    // Float
    Mat4f mf1 = Mat4f::identity();
    Vec4f vf1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f vf2 = mf1 * vf1;
    EXPECT_NEAR(vf2.x, 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(vf2.y, 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2.z, 3.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(vf2.w, 4.0f, FLOAT_ABS_ERROR);
    Mat4f mf2(2.0f,0.0f,0.0f,0.0f, 0.0f,3.0f,0.0f,0.0f, 0.0f,0.0f,4.0f,0.0f, 0.0f,0.0f,0.0f,5.0f);
    Vec4f vf3 = mf2 * Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
    EXPECT_NEAR(vf3.x, 2.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(vf3.y, 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf3.z, 4.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(vf3.w, 5.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1 = Mat4d::identity();
    Vec4d vd1(5.0, 6.0, 7.0, 8.0);
    Vec4d vd2 = md1 * vd1;
    EXPECT_NEAR(vd2.x, 5.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(vd2.y, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2.z, 7.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(vd2.w, 8.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, Equality) {
    // Int
    Mat4i mi1 = Mat4i::identity();
    Mat4i mi2 = Mat4i::identity();
    EXPECT_TRUE(mi1 == mi2);
    EXPECT_FALSE(mi1 == Mat4i(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16));
    // Float
    Mat4f mf1(1.0f,2.0f,3.0f,4.0f, 5.0f,6.0f,7.0f,8.0f, 9.0f,10.0f,11.0f,12.0f, 13.0f,14.0f,15.0f,16.0f);
    Mat4f mf2(1.0f,2.0f,3.0f,4.0f, 5.0f,6.0f,7.0f,8.0f, 9.0f,10.0f,11.0f,12.0f, 13.0f,14.0f,15.0f,16.0f);
    EXPECT_TRUE(mf1 == mf2);
    EXPECT_FALSE(mf1 == Mat4f::identity());
    // Double
    Mat4d md1 = Mat4d::identity();
    Mat4d md2 = Mat4d::identity();
    EXPECT_TRUE(md1 == md2);
    EXPECT_FALSE(md1 == Mat4d(1.0,2.0,3.0,4.0, 5.0,6.0,7.0,8.0, 9.0,10.0,11.0,12.0, 13.0,14.0,15.0,16.0));
}

TEST_F(Mat4Test, Transpose) {
    // Int: identity is its own transpose
    Mat4i mi1 = Mat4i::identity();
    EXPECT_EQ(mi1.transpose(), Mat4i::identity());
    // Numbered matrix: verify rows become columns
    Mat4i mi2(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    Mat4i mi3 = mi2.transpose();
    EXPECT_EQ(mi3(0,0), 1);  EXPECT_EQ(mi3(0,1), 5);  EXPECT_EQ(mi3(0,2), 9);  EXPECT_EQ(mi3(0,3), 13);
    EXPECT_EQ(mi3(1,0), 2);  EXPECT_EQ(mi3(1,1), 6);  EXPECT_EQ(mi3(1,2), 10); EXPECT_EQ(mi3(1,3), 14);
    EXPECT_EQ(mi3(2,0), 3);  EXPECT_EQ(mi3(2,1), 7);  EXPECT_EQ(mi3(2,2), 11); EXPECT_EQ(mi3(2,3), 15);
    EXPECT_EQ(mi3(3,0), 4);  EXPECT_EQ(mi3(3,1), 8);  EXPECT_EQ(mi3(3,2), 12); EXPECT_EQ(mi3(3,3), 16);
    // Float: pre-transposed input becomes sequential rows
    Mat4f mf1(1.0f,5.0f,9.0f,13.0f, 2.0f,6.0f,10.0f,14.0f, 3.0f,7.0f,11.0f,15.0f, 4.0f,8.0f,12.0f,16.0f);
    Mat4f mf2 = mf1.transpose();
    EXPECT_NEAR(mf2(0,0), 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(0,1), 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(0,2), 3.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(0,3), 4.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(1,0), 5.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(2,0), 9.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(3,0), 13.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1(1.0,2.0,3.0,4.0, 5.0,6.0,7.0,8.0, 9.0,10.0,11.0,12.0, 13.0,14.0,15.0,16.0);
    Mat4d md2 = md1.transpose();
    EXPECT_NEAR(md2(0,1), 5.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md2(1,0), 2.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(0,3), 13.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md2(3,0), 4.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, TransposeInPlace) {
    // Int
    Mat4i mi1 = Mat4i::identity();
    mi1.transposeInPlace();
    EXPECT_EQ(mi1, Mat4i::identity());
    Mat4i mi2(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    mi2.transposeInPlace();
    EXPECT_EQ(mi2(0,1), 5);  EXPECT_EQ(mi2(1,0), 2);
    EXPECT_EQ(mi2(0,2), 9);  EXPECT_EQ(mi2(2,0), 3);
    EXPECT_EQ(mi2(0,3), 13); EXPECT_EQ(mi2(3,0), 4);
    EXPECT_EQ(mi2(1,2), 10); EXPECT_EQ(mi2(2,1), 7);
    EXPECT_EQ(mi2(1,3), 14); EXPECT_EQ(mi2(3,1), 8);
    EXPECT_EQ(mi2(2,3), 15); EXPECT_EQ(mi2(3,2), 12);
    EXPECT_EQ(mi2(0,0), 1);  EXPECT_EQ(mi2(1,1), 6); EXPECT_EQ(mi2(2,2), 11); EXPECT_EQ(mi2(3,3), 16);
    // Float
    Mat4f mf1(1.0f,2.0f,3.0f,4.0f, 5.0f,6.0f,7.0f,8.0f, 9.0f,10.0f,11.0f,12.0f, 13.0f,14.0f,15.0f,16.0f);
    mf1.transposeInPlace();
    EXPECT_NEAR(mf1(0,1), 5.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(1,0), 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(3,0), 4.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf1(0,3), 13.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d md1(1.0,2.0,3.0,4.0, 5.0,6.0,7.0,8.0, 9.0,10.0,11.0,12.0, 13.0,14.0,15.0,16.0);
    md1.transposeInPlace();
    EXPECT_NEAR(md1(0,1), 5.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md1(1,0), 2.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(3,0), 4.0, DOUBLE_ABS_ERROR); EXPECT_NEAR(md1(0,3), 13.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, Calculate3x3Det) {
    // Identity: each cofactor minor on the diagonal == 1
    Mat4i id = Mat4i::identity();
    EXPECT_EQ(id.calculate3x3Det(0,0), 1);
    EXPECT_EQ(id.calculate3x3Det(1,1), 1);
    EXPECT_EQ(id.calculate3x3Det(2,2), 1);
    EXPECT_EQ(id.calculate3x3Det(3,3), 1);
    // Off-diagonal minors of identity: rows/cols involved have exactly one 1 each -> det = 0
    EXPECT_EQ(id.calculate3x3Det(1,0), 0);
    EXPECT_EQ(id.calculate3x3Det(0,1), 0);

    // Block-diagonal M = [[1,2,0,0],[3,4,0,0],[0,0,5,6],[0,0,7,8]]
    // det(M) = (1*4-2*3)*(5*8-6*7) = (-2)*(-2) = 4
    Mat4i m(1,2,0,0, 3,4,0,0, 0,0,5,6, 0,0,7,8);
    // Minor at (0,0): rows{1,2,3} cols{1,2,3} = [[4,0,0],[0,5,6],[0,7,8]] -> 4*(40-42) = -8
    EXPECT_EQ(m.calculate3x3Det(0,0), -8);
    // Minor at (1,0): rows{0,2,3} cols{1,2,3} = [[2,0,0],[0,5,6],[0,7,8]] -> 2*(40-42) = -4
    EXPECT_EQ(m.calculate3x3Det(1,0), -4);
    // Minor at (3,3): rows{0,1,2} cols{0,1,2} = [[1,2,0],[3,4,0],[0,0,5]] -> 1*(20)-2*(15) = -10
    EXPECT_EQ(m.calculate3x3Det(3,3), -10);
    // Float
    Mat4f mf(1.0f,2.0f,0.0f,0.0f, 3.0f,4.0f,0.0f,0.0f, 0.0f,0.0f,5.0f,6.0f, 0.0f,0.0f,7.0f,8.0f);
    EXPECT_NEAR(mf.calculate3x3Det(0,0), -8.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf.calculate3x3Det(3,3), -10.0f, FLOAT_ABS_ERROR);
}

TEST_F(Mat4Test, Determinant) {
    // Int
    EXPECT_EQ(Mat4i::identity().determinant(), 1);
    // Rank-deficient: rows are linearly dependent -> det = 0
    Mat4i mi1(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    EXPECT_EQ(mi1.determinant(), 0);
    // Diagonal: det = product of diagonal entries
    Mat4i mi2(2,0,0,0, 0,3,0,0, 0,0,4,0, 0,0,0,5);
    EXPECT_EQ(mi2.determinant(), 120);
    // Block-diagonal: det = (1*4-2*3)*(5*8-6*7) = (-2)*(-2) = 4
    Mat4i mi3(1,2,0,0, 3,4,0,0, 0,0,5,6, 0,0,7,8);
    EXPECT_EQ(mi3.determinant(), 4);
    // Float
    EXPECT_NEAR(Mat4f::identity().determinant(), 1.0f, FLOAT_ABS_ERROR);
    Mat4f mf1(2.0f,0.0f,0.0f,0.0f, 0.0f,4.0f,0.0f,0.0f, 0.0f,0.0f,8.0f,0.0f, 0.0f,0.0f,0.0f,1.0f);
    EXPECT_NEAR(mf1.determinant(), 64.0f, 1e-4f);
    // Double
    EXPECT_NEAR(Mat4d::identity().determinant(), 1.0, DOUBLE_ABS_ERROR);
    Mat4d md1(1.0,2.0,0.0,0.0, 3.0,4.0,0.0,0.0, 0.0,0.0,5.0,6.0, 0.0,0.0,7.0,8.0);
    EXPECT_NEAR(md1.determinant(), 4.0, 1e-10);
}

TEST_F(Mat4Test, Inverse) {
    // Int: identity inverse is identity
    EXPECT_EQ(Mat4i::identity().inverse(), Mat4i::identity());
    // Singular matrix throws
    Mat4i mi_singular(1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16);
    EXPECT_THROW(mi_singular.inverse(), std::runtime_error);
    // Float: identity
    Mat4f mf1 = Mat4f::identity();
    EXPECT_EQ(mf1.inverse(), Mat4f::identity());
    // Diagonal: inverse = diagonal with reciprocals
    // M = diag(2,4,8,1), inverse = diag(0.5, 0.25, 0.125, 1)
    Mat4f mf2(2.0f,0.0f,0.0f,0.0f, 0.0f,4.0f,0.0f,0.0f, 0.0f,0.0f,8.0f,0.0f, 0.0f,0.0f,0.0f,1.0f);
    Mat4f mf2_inv = mf2.inverse();
    EXPECT_NEAR(mf2_inv(0,0), 0.5f,    1e-5f); EXPECT_NEAR(mf2_inv(1,1), 0.25f,  1e-5f);
    EXPECT_NEAR(mf2_inv(2,2), 0.125f,  1e-5f); EXPECT_NEAR(mf2_inv(3,3), 1.0f,   1e-5f);
    EXPECT_NEAR(mf2_inv(0,1), 0.0f,    1e-5f); EXPECT_NEAR(mf2_inv(1,0), 0.0f,   1e-5f);
    // M * inverse = identity for a general matrix
    Mat4f mf3(1.0f,2.0f,0.0f,0.0f, 3.0f,4.0f,0.0f,0.0f, 0.0f,0.0f,5.0f,6.0f, 0.0f,0.0f,7.0f,8.0f);
    Mat4f mf3_inv = mf3.inverse();
    Mat4f mf3_result = mf3 * mf3_inv;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            EXPECT_NEAR(mf3_result(r,c), r == c ? 1.0f : 0.0f, 1e-5f);
    // Double: M * inverse = identity
    Mat4d md1(1.0,2.0,0.0,0.0, 3.0,4.0,0.0,0.0, 0.0,0.0,5.0,6.0, 0.0,0.0,7.0,8.0);
    Mat4d md1_inv = md1.inverse();
    Mat4d md1_result = md1 * md1_inv;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            EXPECT_NEAR(md1_result(r,c), r == c ? 1.0 : 0.0, 1e-10);
}

TEST_F(Mat4Test, Translate) {
    // Translating identity by (1,2,3): produces matrix with translation in last row
    Mat4f T = Mat4f::translate(Mat4f::identity(), Vec3f(1.0f, 2.0f, 3.0f));
    EXPECT_NEAR(T(0,0), 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(T(1,1), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T(2,2), 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(T(3,3), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T(3,0), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T(3,1), 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T(3,2), 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T(0,3), 0.0f, FLOAT_ABS_ERROR);
    // Zero translation: result is identity
    Mat4f T2 = Mat4f::translate(Mat4f::identity(), Vec3f(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(T2, Mat4f::identity());
    // Chaining: translate(T, (1,1,1)) -> translation accumulates to (2,3,4)
    Mat4f T3 = Mat4f::translate(T, Vec3f(1.0f, 1.0f, 1.0f));
    EXPECT_NEAR(T3(3,0), 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T3(3,1), 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(T3(3,2), 4.0f, FLOAT_ABS_ERROR);
    // Double
    Mat4d Td = Mat4d::translate(Mat4d::identity(), Vec3d(5.0, 6.0, 7.0));
    EXPECT_NEAR(Td(3,0), 5.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(Td(3,1), 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(Td(3,2), 7.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(Td(0,0), 1.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat4Test, Rotate) {
    const float tol = 1e-6f;
    // Zero angle: result is identity regardless of axis
    Mat4f R0 = Mat4f::rotate(Mat4f::identity(), 0.0f, Vec3f(0.0f, 0.0f, 1.0f));
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            EXPECT_NEAR(R0(r,c), r == c ? 1.0f : 0.0f, tol);
    // 90 deg. around Z: [[cos,sin,0,0],[-sin,cos,0,0],[0,0,1,0],[0,0,0,1]]
    // cos(pi/2)=0, sin(pi/2)=1 -> [[0,1,0,0],[-1,0,0,0],[0,0,1,0],[0,0,0,1]]
    Mat4f Rz = Mat4f::rotate(Mat4f::identity(), PI / 2.0f, Vec3f(0.0f, 0.0f, 1.0f));
    EXPECT_NEAR(Rz(0,0),  0.0f, tol); EXPECT_NEAR(Rz(0,1),  1.0f, tol);
    EXPECT_NEAR(Rz(1,0), -1.0f, tol); EXPECT_NEAR(Rz(1,1),  0.0f, tol);
    EXPECT_NEAR(Rz(2,2),  1.0f, tol); EXPECT_NEAR(Rz(3,3),  1.0f, tol);
    EXPECT_NEAR(Rz(0,2),  0.0f, tol); EXPECT_NEAR(Rz(2,0),  0.0f, tol);
    // 90 deg. around X: [[1,0,0,0],[0,cos,sin,0],[0,-sin,cos,0],[0,0,0,1]]
    // -> [[1,0,0,0],[0,0,1,0],[0,-1,0,0],[0,0,0,1]]
    Mat4f Rx = Mat4f::rotate(Mat4f::identity(), PI / 2.0f, Vec3f(1.0f, 0.0f, 0.0f));
    EXPECT_NEAR(Rx(0,0),  1.0f, tol);
    EXPECT_NEAR(Rx(1,1),  0.0f, tol); EXPECT_NEAR(Rx(1,2),  1.0f, tol);
    EXPECT_NEAR(Rx(2,1), -1.0f, tol); EXPECT_NEAR(Rx(2,2),  0.0f, tol);
    EXPECT_NEAR(Rx(3,3),  1.0f, tol);
    // 90 deg. around Y: [[cos,0,-sin,0],[0,1,0,0],[sin,0,cos,0],[0,0,0,1]]
    // -> [[0,0,-1,0],[0,1,0,0],[1,0,0,0],[0,0,0,1]]
    Mat4f Ry = Mat4f::rotate(Mat4f::identity(), PI / 2.0f, Vec3f(0.0f, 1.0f, 0.0f));
    EXPECT_NEAR(Ry(0,0),  0.0f, tol); EXPECT_NEAR(Ry(0,2), -1.0f, tol);
    EXPECT_NEAR(Ry(2,0),  1.0f, tol); EXPECT_NEAR(Ry(2,2),  0.0f, tol);
    EXPECT_NEAR(Ry(1,1),  1.0f, tol); EXPECT_NEAR(Ry(3,3),  1.0f, tol);
    // 360 deg. rotation returns to identity (within float precision)
    Mat4f R360 = Mat4f::rotate(Mat4f::identity(), 2.0f * PI, Vec3f(0.0f, 0.0f, 1.0f));
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            EXPECT_NEAR(R360(r,c), r == c ? 1.0f : 0.0f, tol);
}
