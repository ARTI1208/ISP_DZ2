#include <utility>

//
// Created by arti1208 on 08.10.2020.
//

#ifndef STACK_EL_TYPE
#define STACK_EL_TYPE int
#endif

#define CONCAT(param1, param2) param1##_##param2

#define StackName(type) CONCAT(unbr_stack, type)

struct StackName(STACK_EL_TYPE) {
private:
    STACK_EL_TYPE* data = nullptr;

    long sizeInternal = 0;
    long capacity = 0;

    int resizeFactor = 2;

    [[nodiscard]] int checkStackValid() const {
        if (sizeInternal < 0) return -1;
        if (capacity < 0) return -2;
        if (capacity < sizeInternal) return -3;

        return 0;
    }

    bool resizeIfNeeded() {
        if (sizeInternal == capacity) {
            capacity = capacity > 0 ? resizeFactor * capacity : 10;
            auto* newData = new STACK_EL_TYPE[capacity];
            for (long i = 0; i < sizeInternal; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;

            return true;
        }

        return false;
    }

public:

    ~StackName(STACK_EL_TYPE)() {
        delete[] data;
        capacity = -1;
        sizeInternal = 0;
    }

    int push(STACK_EL_TYPE elem) {
        int valid = checkStackValid();
        if (valid != 0) return valid;

        resizeIfNeeded();

        data[sizeInternal++] = std::move(elem);

        valid = checkStackValid();
        if (valid != 0) return valid;

        return 0;
    }

    int pop(STACK_EL_TYPE& elem) {

        int valid = checkStackValid();
        if (valid != 0) return valid;

        if (empty()) return -1;

        elem = data[--sizeInternal];

        valid = checkStackValid();
        if (valid != 0) return valid;

        return 0;
    }

    int top(STACK_EL_TYPE& elem) {

        int valid = checkStackValid();
        if (valid != 0) return valid;

        if (empty()) return -1;

        elem = data[sizeInternal - 1];

        valid = checkStackValid();
        if (valid != 0) return valid;

        return 0;
    }

    [[nodiscard]] bool empty() const {
        return sizeInternal == 0;
    }

    [[nodiscard]] long size() const {
        return sizeInternal;
    }
};
