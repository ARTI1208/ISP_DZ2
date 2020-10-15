#include <iostream>

using namespace std;

//#define STACK_EL_TYPE string
//#include "unbreakable_stack.h"
//#undef STACK_EL_TYPE

#define STACK_EL_TYPE double
#define STACK_EL_TO_STRING(v) std::to_string(v).c_str()
#include "unbreakable_stack.h"
#undef STACK_EL_TYPE
#undef STACK_EL_TO_STRING

#define STACK_EL_TYPE string
#define STACK_EL_TO_STRING(v) v.c_str()
#include "unbreakable_stack.h"
#undef STACK_EL_TYPE
#undef STACK_EL_TO_STRING

int main(int argc, char* argv[]) {

    unbr_stack_double doubleStack {};
    std::cout << "0=================\n";

    std::cout << "0.5=================\n";

    std::cout << doubleStack.empty() << "\n";
    std::cout << doubleStack.size() << "\n";

    std::cout << "1=================\n";

//    double* str1 = new double[3]{1, 2, 3};

    std::cout << doubleStack.push(6) << "\n";

//    const char* str2 = "man";
//    doubleStack.dump();


//    for (int i = 0; i < 3; ++i) {
//        str1[i] = 9;
//    }

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



    return 0;
}
