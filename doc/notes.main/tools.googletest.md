# Tools.GoogleTest

googletest is a testing framework developed by the Testing Technology team with Google's specific requirements and constraints in mind.

REF: [Googletest Primer | GoogleTest](https://google.github.io/googletest/primer.html)

When using googletest, you start by writing assertions, which are statements that check whether a condition is true.

An assertion's result can be success, nonfatal failure or fatal failure.


## Assertions

ASSERT_* versions generate fatal failures when they fail and abort the current functinos.

EXPECT_* versions generate nonfatal failures, which don't abort the functions.

To provide a custom failure message, simply stream it into the macro

## Simple Tests

To create a test:

- use TEST() macro to define and name a test function
  TEST(TestSuitName, TestName)

## QuickStart CMake

- A compatible operating system
- A compatible C++ compiler that supports at least C++14
- CMake and a compatible build tool for building the project
