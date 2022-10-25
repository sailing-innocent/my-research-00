#include <gtest/gtest.h>

#include <fmt/core.h>

#include <string>

TEST(LIB_SAIL_TEST, DEPS_FMT_BASIC) {
    // fmt::print("This is the format function {}.", 42);
    std::string s = fmt::format("The answer is {}.", 42);
    EXPECT_EQ(s, "The answer is 42.");
}