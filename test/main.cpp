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

#define STACK_EL_TYPE long
#define STACK_EL_TO_STRING(v) std::to_string(v).c_str()
#include "../src/unbreakable_stack.h"
#undef STACK_EL_TYPE
#undef STACK_EL_TO_STRING

TEST(StackTest, DoesItCompileAtAll) {
    unbr_stack_double doubleStack {};
    unbr_stack_long stringStack {};
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
//
//    auto* q = new double[3] {1, 2, 3};
//
    doubleStack.push(5);
//
//    for (int i = 0; i < 10; ++i) {
//        q[i] = 40;
//    }
//
    double tmp = 0;

    ASSERT_EQ(doubleStack.top(tmp), OK);

    ASSERT_EQ(tmp, 5);
}

TEST(StackTest, StructCanaryLeftAttack) {
    struct s {
        long t[2]{7, 8};
        unbr_stack_long longStack {};
    } tmpStruct;

    ASSERT_EQ(tmpStruct.longStack.push(6), OK);

    for (int i = 0; i < 3; ++i) {
        tmpStruct.t[i] = 9;
    }

    ASSERT_EQ(tmpStruct.longStack.push(6), ATTACK_LEFT);
}

TEST(StackTest, StructCanaryRightAttack) {
    struct s {
        unbr_stack_long longStack {};
        long t[2]{7, 8};
    } tmpStruct;

    ASSERT_EQ(tmpStruct.longStack.push(6), OK);

    for (int i = 1; i >= -1; --i) {
        tmpStruct.t[i] = 9;
    }

    ASSERT_EQ(tmpStruct.longStack.push(6), ATTACK_RIGHT);
}

TEST(StackTest, DataCanaryLeftAttack) {
    unbr_stack_long longStack {};

    ASSERT_EQ(longStack.push(6), OK);

    //no idea how to test data for attack
}

TEST(StackTest, DataCanaryRightAttack) {
    unbr_stack_long longStack {};

    ASSERT_EQ(longStack.push(6), OK);

    //no idea how to test data for attack
}