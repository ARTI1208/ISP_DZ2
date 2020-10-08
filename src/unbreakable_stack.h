/**
 * @file
 *
 * @brief Implementation of unbreakable stack, with c-style templates
 */

#ifndef ISP_DZ3_STACK_H
#define ISP_DZ3_STACK_H

#include <utility>
#include <cstring>
#include <cstdio>
#include <typeinfo>

/**
 * Enum that represents stack state
 */
enum unbr_stack_state {
    /**
     * Everything ok
     */
    OK,

    /**
     * Size is less than zero
     */
    WRONG_SIZE,

    /**
     * Capacity is less than zero
     */
    WRONG_CAPACITY,

    /**
     * Capacity is less than stack actual size
     */
    CAPACITY_LESS_THAN_SIZE,

    /**
     * Returned by top/pop if stack size is zero
     */
    STACK_EMPTY
};

/**
 * Return enum stack state name
 */
static const char* enumStateName(const unbr_stack_state& state) {
    switch (state) {
        case OK:
            return "ok";
        case WRONG_SIZE:
            return "WRONG_SIZE";
        case WRONG_CAPACITY:
            return "WRONG_CAPACITY";
        case CAPACITY_LESS_THAN_SIZE:
            return "CAPACITY_LESS_THAN_SIZE";
        case STACK_EMPTY:
            return "STACK_EMPTY";
    }

    return "UNKNOWN";
}

/**
 * Checks the stack state and dumps if stack is not ok
 */
#define validateStack()  {                    \
    unbr_stack_state valid = getStackState(); \
    if (valid != OK) {                        \
        dump();                               \
        return valid;                         \
    }                                         \
}

#endif

#ifndef STACK_EL_TYPE
#define STACK_EL_TYPE int
#endif

#define CONCAT(param1, param2) param1##_##param2
#define StackName(type) CONCAT(unbr_stack, type)

/**
 * Implementation of unbreakable stack, with c-style templates
 */
struct StackName(STACK_EL_TYPE) {
private:
    STACK_EL_TYPE* data = nullptr;

    long sizeInternal = 0;
    long capacity = 0;

    int resizeFactor = 2;

    [[nodiscard]] unbr_stack_state getStackState() const {
        if (sizeInternal < 0) return WRONG_SIZE;
        if (capacity < 0) return WRONG_CAPACITY;
        if (capacity < sizeInternal) return CAPACITY_LESS_THAN_SIZE;

        return OK;
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

    /**
     * Pushes given element to the stack
     *
     * @param elem Element to push
     * @return Stack state
     */
    unbr_stack_state push(STACK_EL_TYPE elem) {
        validateStack()

        resizeIfNeeded();
        data[sizeInternal++] = elem;

        validateStack()
        return OK;
    }

    /**
     * Pops top element from the stack
     *
     * @param elem Element reference to pop into
     * @return Stack state
     */
    unbr_stack_state pop(STACK_EL_TYPE& elem) {
        validateStack()
        if (empty()) return STACK_EMPTY;

        elem = data[--sizeInternal];

        validateStack()
        return OK;
    }

    /**
     * Returns the top element of the stack without popping it
     *
     * @param elem Element reference to write top element into
     * @return Stack state
     */
    unbr_stack_state top(STACK_EL_TYPE& elem) {
        validateStack()
        if (empty()) return STACK_EMPTY;

        elem = data[sizeInternal - 1];

        validateStack()
        return OK;
    }

    /**
     * Returns whether this stack should be treated as empty
     *
     * @return True if stack is empty, false otherwise
     */
    [[nodiscard]] bool empty() const {
        return sizeInternal == 0;
    }

    /**
     * Returns size of the stack
     *
     * @return Size of the stack
     */
    [[nodiscard]] long size() const {
        return sizeInternal;
    }

    /**
     * Dumps all stack info to the file
     *
     * @param path Path to the dump file
     */
    void dump(const char* path) {
        FILE* logFile = fopen(path, "a");
        if (logFile == nullptr) return;

        unbr_stack_state state = getStackState();
        const char* stateStr = enumStateName(state);
        fprintf(logFile, "%s %s (%s) [%p] {\n\tcapacity: %ld,\n\tsize: %ld,\n\tdata [%p]: {\n",
                typeid(this).name(), "test", stateStr, this, capacity, sizeInternal, data);

#ifdef STACK_EL_TO_STRING
        if (state == OK) {
            for (long i = 0; i < capacity; ++i) {
                if (i < sizeInternal) {
                    fprintf(logFile, "\t\t*data[%ld]: %s\n", i, STACK_EL_TO_STRING(data[i]));
                } else {
                    fprintf(logFile, "\t\t data[%ld]: %s (POISON)\n", i, STACK_EL_TO_STRING(data[i]));
                }
            }
        }
#endif
        fprintf(logFile, "\t}\n}\n\n");

        fclose(logFile);
    }

    /**
     * Dumps all stack info to default file (unbr_stack_<type>.txt)
     */
    void dump() {
        const char* className = typeid(this).name();

        std::size_t pathLen = strlen(className) + 5;
        char* path = new char[pathLen];
        strcpy(path, className);
        path[pathLen - 5] = '.';
        path[pathLen - 4] = 't';
        path[pathLen - 3] = 'x';
        path[pathLen - 2] = 't';
        path[pathLen - 1] = '\0';

        dump(path);

        delete[] path;
    }
};
