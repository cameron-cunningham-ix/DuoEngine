#include <gtest/gtest.h>

#include "include/math/Mat3.hpp"

class Mat3Test : public testing::Test { };

using namespace RendMath;
constexpr const float FLOAT_ABS_ERROR = std::numeric_limits<float>::epsilon() * 2.0f;
constexpr const double DOUBLE_ABS_ERROR = std::numeric_limits<double>::epsilon() * 4.0;

TEST_F(Mat3Test, Constructors) {
    // Int
    Mat3i mi1;
    EXPECT_EQ(mi1, Mat3i(1,0,0,0,1,0,0,0,1));
    EXPECT_EQ(mi1, Mat3i::identity());
    Mat3i mi2(1,2,3,4,5,6,7,8,9);
    EXPECT_EQ(mi2(0,0), 1); EXPECT_EQ(mi2(0,1), 2); EXPECT_EQ(mi2(0,2), 3);
    EXPECT_EQ(mi2(1,0), 4); EXPECT_EQ(mi2(1,1), 5); EXPECT_EQ(mi2(1,2), 6);
    EXPECT_EQ(mi2(2,0), 7); EXPECT_EQ(mi2(2,1), 8); EXPECT_EQ(mi2(2,2), 9);
    // Float
    Mat3f mf1;
    EXPECT_EQ(mf1, Mat3f(1,0,0,0,1,0,0,0,1));
    EXPECT_EQ(mf1, Mat3f::identity());
    // Double
    Mat3d md1;
    EXPECT_EQ(md1, Mat3d(1,0,0,0,1,0,0,0,1));
    EXPECT_EQ(md1, Mat3d::identity());
}

TEST_F(Mat3Test, Index) {
    // Int
    Mat3i mi1;
    EXPECT_EQ(mi1(0,0), 1);
    EXPECT_EQ(mi1(0,1), 0);
    EXPECT_EQ(mi1(0,2), 0);
    EXPECT_EQ(mi1(1,1), 1);
    EXPECT_EQ(mi1(2,2), 1);
    mi1(0,0) = 5;
    EXPECT_EQ(mi1(0,0), 5);
    // Const check
    const Mat3i mi2(1,2,3,4,5,6,7,8,9);
    EXPECT_EQ(mi2(0,0), 1); EXPECT_EQ(mi2(0,1), 2); EXPECT_EQ(mi2(0,2), 3);
    EXPECT_EQ(mi2(1,0), 4); EXPECT_EQ(mi2(1,1), 5); EXPECT_EQ(mi2(1,2), 6);
    EXPECT_EQ(mi2(2,0), 7); EXPECT_EQ(mi2(2,1), 8); EXPECT_EQ(mi2(2,2), 9);
    // Float
    Mat3f mf1(1.5f,2.5f,3.5f,4.5f,5.5f,6.5f,7.5f,8.5f,9.5f);
    EXPECT_NEAR(mf1(0,0), 1.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(1,1), 5.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(2,2), 9.5f, FLOAT_ABS_ERROR);
    mf1(1,2) = 99.0f;
    EXPECT_NEAR(mf1(1,2), 99.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1(1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9);
    EXPECT_NEAR(md1(0,0), 1.1, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(1,1), 5.5, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(2,2), 9.9, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, Identity) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    EXPECT_EQ(mi1(0,0), 1);
    EXPECT_EQ(mi1(0,1), 0);
    EXPECT_EQ(mi1(0,2), 0);
    EXPECT_EQ(mi1(1,0), 0);
    EXPECT_EQ(mi1(1,1), 1);
    EXPECT_EQ(mi1(1,2), 0);
    EXPECT_EQ(mi1(2,0), 0);
    EXPECT_EQ(mi1(2,1), 0);
    EXPECT_EQ(mi1(2,2), 1);
    // Float
    Mat3f mf1 = Mat3f::identity();
    EXPECT_NEAR(mf1(0,0), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(1,1), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(2,2), 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(0,1), 0.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1 = Mat3d::identity();
    EXPECT_NEAR(md1(0,0), 1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(1,1), 1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(2,2), 1.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(0,1), 0.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, MatrixMult) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    EXPECT_EQ(mi1 * mi1, Mat3i::identity());
    Mat3i mi2(1,2,3,4,5,6,7,8,9);
    EXPECT_EQ(mi1 * mi2, mi2);
    EXPECT_EQ(mi2 * mi1, mi2);
    Mat3i mi3(9,8,7,6,5,4,3,2,1);
    Mat3i mi4 = mi2 * mi3;
    EXPECT_EQ(mi4(0,0), 30); EXPECT_EQ(mi4(0,1), 24); EXPECT_EQ(mi4(0,2), 18);
    EXPECT_EQ(mi4(1,0), 84); EXPECT_EQ(mi4(1,1), 69); EXPECT_EQ(mi4(1,2), 54);
    EXPECT_EQ(mi4(2,0), 138); EXPECT_EQ(mi4(2,1), 114); EXPECT_EQ(mi4(2,2), 90);
    // Float
    Mat3f mf1(1.0f,2.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,0.0f,1.0f);
    Mat3f mf2(-1.0f,2.0f,0.0f, 0.0f,3.0f,0.0f, 0.0f,0.0f,1.0f);
    Mat3f mf3 = mf1 * mf2;
    EXPECT_NEAR(mf3(0,0), -1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf3(0,1),  8.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf3(1,1),  3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf3(2,2),  1.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1 = Mat3d::identity();
    Mat3d md2(1.0,2.0,3.0, 4.0,5.0,6.0, 7.0,8.0,9.0);
    EXPECT_EQ(md1 * md2, md2);
}

TEST_F(Mat3Test, ScalarMult) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    Mat3i mi2 = mi1 * 3;
    EXPECT_EQ(mi2, Mat3i(3,0,0,0,3,0,0,0,3));
    Mat3i mi3 = 3 * mi1;
    EXPECT_EQ(mi3, Mat3i(3,0,0,0,3,0,0,0,3));
    Mat3i mi4(1,2,3,4,5,6,7,8,9);
    mi4 *= 2;
    EXPECT_EQ(mi4, Mat3i(2,4,6,8,10,12,14,16,18));
    // Float
    Mat3f mf1(1.0f,2.0f,3.0f, 4.0f,5.0f,6.0f, 7.0f,8.0f,9.0f);
    Mat3f mf2 = mf1 * 2.0f;
    EXPECT_NEAR(mf2(0,0), 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(1,1), 10.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(2,2), 18.0f, FLOAT_ABS_ERROR);
    Mat3f mf3 = 0.5f * mf1;
    EXPECT_NEAR(mf3(0,0), 0.5f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf3(1,1), 2.5f, FLOAT_ABS_ERROR);
    mf1 *= 3.0f;
    EXPECT_NEAR(mf1(0,0), 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(2,2), 27.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1(1.0,0.0,0.0, 0.0,2.0,0.0, 0.0,0.0,3.0);
    Mat3d md2 = md1 * 4.0;
    EXPECT_NEAR(md2(0,0), 4.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(1,1), 8.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(2,2), 12.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, VectorMult) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    Vec3i vi1(1,2,3);
    EXPECT_EQ(mi1 * vi1, vi1);
    Mat3i mi2(1,2,3,4,5,6,7,8,9);
    Vec3i vi2 = mi2 * Vec3i(1,1,1);
    EXPECT_EQ(vi2, Vec3i(6,15,24));
    Vec3i vi3 = mi2 * Vec3i(1,0,0);
    EXPECT_EQ(vi3, Vec3i(1,4,7));
    // Float
    Mat3f mf1 = Mat3f::identity();
    Vec3f vf1(1.0f, 2.0f, 3.0f);
    Vec3f vf2 = mf1 * vf1;
    EXPECT_NEAR(vf2.x, 1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2.y, 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf2.z, 3.0f, FLOAT_ABS_ERROR);
    Mat3f mf2(2.0f,0.0f,0.0f, 0.0f,3.0f,0.0f, 0.0f,0.0f,4.0f);
    Vec3f vf3 = mf2 * Vec3f(1.0f, 1.0f, 1.0f);
    EXPECT_NEAR(vf3.x, 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf3.y, 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(vf3.z, 4.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1 = Mat3d::identity();
    Vec3d vd1(5.0, 6.0, 7.0);
    Vec3d vd2 = md1 * vd1;
    EXPECT_NEAR(vd2.x, 5.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2.y, 6.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(vd2.z, 7.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, Equality) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    Mat3i mi2 = Mat3i::identity();
    EXPECT_TRUE(mi1 == mi2);
    EXPECT_FALSE(mi1 == Mat3i(1,2,3,4,5,6,7,8,9));
    // Float
    Mat3f mf1(1.0f,2.0f,3.0f, 4.0f,5.0f,6.0f, 7.0f,8.0f,9.0f);
    Mat3f mf2(1.0f,2.0f,3.0f, 4.0f,5.0f,6.0f, 7.0f,8.0f,9.0f);
    EXPECT_TRUE(mf1 == mf2);
    EXPECT_FALSE(mf1 == Mat3f::identity());
    // Double
    Mat3d md1 = Mat3d::identity();
    Mat3d md2 = Mat3d::identity();
    EXPECT_TRUE(md1 == md2);
    EXPECT_FALSE(md1 == Mat3d(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0));
}

TEST_F(Mat3Test, Transpose) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    EXPECT_EQ(mi1.transpose(), Mat3i::identity());
    Mat3i mi2(1,2,3,4,5,6,7,8,9);
    Mat3i mi3 = mi2.transpose();
    EXPECT_EQ(mi3(0,0), 1); EXPECT_EQ(mi3(0,1), 4); EXPECT_EQ(mi3(0,2), 7);
    EXPECT_EQ(mi3(1,0), 2); EXPECT_EQ(mi3(1,1), 5); EXPECT_EQ(mi3(1,2), 8);
    EXPECT_EQ(mi3(2,0), 3); EXPECT_EQ(mi3(2,1), 6); EXPECT_EQ(mi3(2,2), 9);
    // Float
    Mat3f mf1(1.0f,4.0f,7.0f, 2.0f,5.0f,8.0f, 3.0f,6.0f,9.0f);
    Mat3f mf2 = mf1.transpose();
    EXPECT_NEAR(mf2(0,0), 1.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(0,1), 2.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(0,2), 3.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(1,0), 4.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(1,1), 5.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(1,2), 6.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2(2,0), 7.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(2,1), 8.0f, FLOAT_ABS_ERROR); EXPECT_NEAR(mf2(2,2), 9.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1(1.0,2.0,3.0, 4.0,5.0,6.0, 7.0,8.0,9.0);
    Mat3d md2 = md1.transpose();
    EXPECT_NEAR(md2(0,1), 4.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(1,0), 2.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(0,2), 7.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md2(2,0), 3.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, TransposeInPlace) {
    // Int
    Mat3i mi1 = Mat3i::identity();
    mi1.transposeInPlace();
    EXPECT_EQ(mi1, Mat3i::identity());
    Mat3i mi2(1,2,3,4,5,6,7,8,9);
    mi2.transposeInPlace();
    EXPECT_EQ(mi2(0,1), 4); EXPECT_EQ(mi2(1,0), 2);
    EXPECT_EQ(mi2(0,2), 7); EXPECT_EQ(mi2(2,0), 3);
    EXPECT_EQ(mi2(1,2), 8); EXPECT_EQ(mi2(2,1), 6);
    EXPECT_EQ(mi2(0,0), 1); EXPECT_EQ(mi2(1,1), 5); EXPECT_EQ(mi2(2,2), 9);
    // Float
    Mat3f mf1(1.0f,2.0f,3.0f, 4.0f,5.0f,6.0f, 7.0f,8.0f,9.0f);
    mf1.transposeInPlace();
    EXPECT_NEAR(mf1(0,1), 4.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(1,0), 2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf1(2,0), 3.0f, FLOAT_ABS_ERROR);
    // Double
    Mat3d md1(1.0,2.0,3.0, 4.0,5.0,6.0, 7.0,8.0,9.0);
    md1.transposeInPlace();
    EXPECT_NEAR(md1(0,1), 4.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(1,0), 2.0, DOUBLE_ABS_ERROR);
    EXPECT_NEAR(md1(2,0), 3.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, Determinant) {
    // Int
    EXPECT_EQ(Mat3i::identity().determinant(), 1);
    Mat3i mi1(1,2,3,4,5,6,7,8,9);
    EXPECT_EQ(mi1.determinant(), 0);
    Mat3i mi2(1,2,0, 0,3,4, 5,6,7);
    EXPECT_EQ(mi2.determinant(), 37);
    Mat3i mi3(2,1,3, 0,4,1, 5,2,6);
    EXPECT_EQ(mi3.determinant(), -11);
    // Float
    EXPECT_NEAR(Mat3f::identity().determinant(), 1.0f, FLOAT_ABS_ERROR);
    Mat3f mf1(1.0f,2.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,0.0f,1.0f);
    EXPECT_NEAR(mf1.determinant(), 1.0f, FLOAT_ABS_ERROR);
    // Double
    EXPECT_NEAR(Mat3d::identity().determinant(), 1.0, DOUBLE_ABS_ERROR);
    Mat3d md1(2.0,1.0,3.0, 0.0,4.0,1.0, 5.0,2.0,6.0);
    EXPECT_NEAR(md1.determinant(), -11.0, DOUBLE_ABS_ERROR);
}

TEST_F(Mat3Test, Inverse) {
    // Int
    EXPECT_EQ(Mat3i::identity().inverse(), Mat3i::identity());
    Mat3i mi_singular(1,2,3,4,5,6,7,8,9);
    EXPECT_THROW(mi_singular.inverse(), std::runtime_error);
    // Float
    Mat3f mf1 = Mat3f::identity();
    EXPECT_EQ(mf1.inverse(), Mat3f::identity());
    Mat3f mf2(1.0f,2.0f,0.0f, 0.0f,1.0f,0.0f, 0.0f,0.0f,1.0f);
    Mat3f mf2_inv = mf2.inverse();
    EXPECT_NEAR(mf2_inv(0,0),  1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2_inv(0,1), -2.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2_inv(0,2),  0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2_inv(1,0),  0.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2_inv(1,1),  1.0f, FLOAT_ABS_ERROR);
    EXPECT_NEAR(mf2_inv(2,2),  1.0f, FLOAT_ABS_ERROR);
    // M * inverse = identity
    Mat3f mf3(2.0f,1.0f,3.0f, 0.0f,4.0f,1.0f, 5.0f,2.0f,6.0f);
    Mat3f mf3_inv = mf3.inverse();
    Mat3f mf3_result = mf3 * mf3_inv;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            EXPECT_NEAR(mf3_result(r,c), r == c ? 1.0f : 0.0f, 1e-5f);
    // Double
    Mat3d md1(2.0,1.0,3.0, 0.0,4.0,1.0, 5.0,2.0,6.0);
    Mat3d md1_inv = md1.inverse();
    Mat3d md1_result = md1 * md1_inv;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            EXPECT_NEAR(md1_result(r,c), r == c ? 1.0 : 0.0, 1e-10);
}
