#include <gtest/gtest.h>

#include "include/math/Vec2.hpp"

class Vec2Test : public testing::Test { };

TEST_F(Vec2Test, InitToZero) {
    Vec2i v1 = Vec2i();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
    Vec2f v1 = Vec2f();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
    Vec2d v1 = Vec2d();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 0);
}