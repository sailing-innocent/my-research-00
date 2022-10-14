#include <gtest/gtest.h>
#include "sail/hello.h"

TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, UseLibrary) {
    std::string s = sail::hello();
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(HelloTest, UseTemplate) {
    int t = sail::getT<int>();
    EXPECT_EQ(t, 0);
}