#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by arti1208 on 02.10.2020.
//

#include "gtest/gtest.h"

using namespace std;

#define STACK_EL_TYPE double
#define STACK_EL_TO_STRING(v) std::to_string(v).c_str()
#include "../src/unbreakable_stack.h"
#undef STACK_EL_TYPE
#undef STACK_EL_TO_STRING

#define STACK_EL_TYPE string
#define STACK_EL_TO_STRING(v) v.c_str()
#include "../src/unbreakable_stack.h"
#undef STACK_EL_TYPE
#undef STACK_EL_TO_STRING

TEST(StackTest, DoesItCompileAtAll) {
    unbr_stack_double doubleStack {};
    unbr_stack_string stringStack {};
}

TEST(StackTest, StackPush) {
    unbr_stack_double doubleStack {};

    ASSERT_TRUE(doubleStack.empty());

    ASSERT_EQ(doubleStack.push(5), OK);
    ASSERT_EQ(doubleStack.size(), 1);
    ASSERT_FALSE(doubleStack.empty());

    double tmp = 0;

    ASSERT_EQ(doubleStack.top(tmp), OK);
    ASSERT_EQ(tmp, 5);
    ASSERT_EQ(doubleStack.size(), 1);
    ASSERT_FALSE(doubleStack.empty());

    ASSERT_EQ(doubleStack.top(tmp), OK);
    ASSERT_EQ(tmp, 5);
    ASSERT_EQ(doubleStack.size(), 1);
    ASSERT_FALSE(doubleStack.empty());
}

TEST(StackTest, StackTop) {
    unbr_stack_double doubleStack{};

    doubleStack.push(5);

    double tmp = 0;

    ASSERT_EQ(doubleStack.top(tmp), OK);
    ASSERT_EQ(tmp, 5);
    ASSERT_EQ(doubleStack.size(), 1);
    ASSERT_FALSE(doubleStack.empty());
}

TEST(StackTest, StackPop) {
    unbr_stack_double doubleStack{};

    doubleStack.push(5);

    double tmp = 0;

    ASSERT_EQ(doubleStack.pop(tmp), OK);
    ASSERT_EQ(tmp, 5);
    ASSERT_EQ(doubleStack.size(), 0);
    ASSERT_TRUE(doubleStack.empty());
}

TEST(StackTest, TryBreakStack) {
    unbr_stack_double doubleStack{};

    auto* q = new double[3] {1, 2, 3};

    doubleStack.push(5);

    for (int i = 0; i < 10; ++i) {
        q[i] = 40;
    }

    double tmp = 0;

    ASSERT_EQ(doubleStack.top(tmp), OK);

    ASSERT_EQ(tmp, 5);
}

#pragma clang diagnostic pop // yeah, CLion bug