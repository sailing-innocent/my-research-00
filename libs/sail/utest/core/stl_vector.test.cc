/**
 * @file: utest/core/stl_vector.test.cc
 * @author: sailing-innocent
 * @create: 2022-10-25
 * @desp: testing vector
 * @done: TODO
*/

#include <gtest/gtest.h>
#include <vector>

TEST(SAIL_TEST_CORE, STL_VECTOR_BASIC)
{
    std::vector<int> vi(3);
    EXPECT_EQ(vi.size(), 3);
    vi[0] = 1;
    vi[1] = 2;
    vi[2] = 3;
    EXPECT_EQ(vi[0], 1);
    EXPECT_EQ(vi.size(), 3);
    EXPECT_EQ(sizeof(vi), 32);
    vi.push_back(4);
    vi.push_back(5);
    EXPECT_EQ(vi.size(), 5);
    int* pvi = vi.data();
    EXPECT_EQ(*(pvi+2),3);
    EXPECT_EQ(sizeof(vi), 32);
    vi.push_back(4);
    vi.push_back(5);
    vi.push_back(4);
    vi.push_back(5);
    EXPECT_EQ(sizeof(vi.data()), 8);
    EXPECT_EQ(sizeof(int*), 8);
}