/**
 * @file: utest/core/timer.test.cc
 * @author: sailing-innocent
 * @create: 2022-10-15
 * @desp: testing suites for sail core timer
 * @done: TODO
*/


#include <gtest/gtest.h>
#include <sail/core.h>
#include <windows.h>

using namespace sail;

TEST(SAIL_TEST_TIMER, CREATE_TIMER)
{
    Timer timer;
    long long dt = timer.DeltaTime();
    EXPECT_EQ(dt, -1);
}

TEST(SAIL_TEST_TIMER, TIMER_BASIC_FUNCTION)
{
    Timer timer;
    timer.Reset();
    timer.Start();
    Sleep(1000);
    timer.Tick();
    long long dt = timer.DeltaTime();
    // dt should be a little more than 1000
    EXPECT_GT(dt, 1000);
    EXPECT_LT(dt, 2000);
}