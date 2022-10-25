#include <gtest/gtest.h>

#define ONE_BEGIN namespace one {
#define ONE_END }
#define TWO_BEGIN ONE_BEGIN namespace two {
#define TWO_END ONE_END }

TWO_BEGIN

int get() { return 1; }

TWO_END

TEST(SAIL_TEST_CORE, CPP_MACRO_BASIC)
{
    int s = one::two::get();
    EXPECT_EQ(s, 1);
}