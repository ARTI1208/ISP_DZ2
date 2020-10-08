#include <cstdio>
#include <iostream>

using namespace std;

#define STACK_EL_TYPE string
#include "unbreakable_stack.h"
#undef STACK_EL_TYPE

#define STACK_EL_TYPE double
#include "unbreakable_stack.h"
#undef STACK_EL_TYPE

int main(int argc, char* argv[]) {

    unbr_stack_double doubleStack {};


    std::cout << doubleStack.empty() << "\n";
    std::cout << doubleStack.size() << "\n";

    std::cout << "1=================\n";

    double* str1 = new double[3]{1, 2, 3};

    std::cout << doubleStack.push(6) << "\n";

    const char* str2 = "man";

    for (int i = 0; i < 3; ++i) {
        str1[i] = 9;
    }

    std::cout << "2=================\n";

    std::cout << doubleStack.empty() << "\n";
    std::cout << doubleStack.size() << "\n";

    std::cout << "3=================\n";

    double el = 0;
    std::cout << doubleStack.top(el) << "\n";
    std::cout << el << "\n";

    std::cout << "4=================\n";

    std::cout << doubleStack.empty() << "\n";
    std::cout << doubleStack.size() << "\n";

    std::cout << "5=================\n";

    double el2 = 0;
    std::cout << doubleStack.pop(el2) << "\n";
    std::cout << el << "\n";

    std::cout << "6=================\n";

    std::cout << doubleStack.empty() << "\n";
    std::cout << doubleStack.size() << "\n";

    std::cout << "7=================\n";


    unbr_stack_string s {};


    s.push("test");

    string str;
    std::cout << s.pop(str) << "\n";
    std::cout << str << "\n";



    return 0;
}
