/**
 * @file: utest/core/cpp_basic.test.cc
 * @author: sailing-innocent
 * @create: 2022-10-24
 * @desp: testing the basic c++ features
 * @done: TODO
*/

#include <gtest/gtest.h>

class Base {
public:
    int func1() { func3(); return func4(); }
    int func2() { return 3; }
protected:
    void func3() { mS = 5;}
    int func4() { return mS + 2; } // 7
protected:
    int mS;
};

class Derived: public Base {
public:   
    int func1() { func3(); return func4(); }
    int func2() { return Base::func2() + 1;}
protected:
    void func3() { mS = 6; }
};

TEST(SAIL_TEST_CORE, CPP_BASIC_DERIVE)
{
    Derived d;
    EXPECT_EQ(d.func2(), 4);
    EXPECT_EQ(d.func1(), 8);
}

TEST(SAIL_TEST_CORE, CPP_BASIC_ENUM)
{
    enum TENUM {
        ONE = 1,
        TWO = 2
    };
    TENUM te = ONE;
    EXPECT_EQ(te, 1);
    // te = TWO;
    // EXPECT_EQ(te, 1);
}