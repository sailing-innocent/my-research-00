#include <gtest/gtest.h>
#include "sail/hello.h"

TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
    std::string s = sail::hello();
    EXPECT_STREQ(s.c_str(), "Hello");
}
