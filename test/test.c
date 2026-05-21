#include "../mstd.h"
#include "common.h"
#include "test_mem.c"

// #define test_result_add(result_dest, test_fn) do { TestResult result_src = test_fn(); result_dest.passed += result_src.passed; result_dest.count += result_src.count; } while(0)

int main() {
    TestResult result = {0};

    test_mem(&result);

    printf("Test result: %d/%d\n", result.passed, result.count);
    return 0;
}

#include "../mstd.c"
