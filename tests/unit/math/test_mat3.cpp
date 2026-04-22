#include <gtest/gtest.h>

#include "include/math/Mat3.hpp"

class Mat3Test : public testing::Test { };

using namespace RendMath;

TEST_F(Mat3Test, Constructors) {
    Mat3i mi1;
    EXPECT_EQ(mi1, Mat3i(1,0,0,0,1,0,0,0,1));
}