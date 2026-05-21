#ifndef COMMON_H
#define COMMON_H

#include "../mstd.h"

#define TEST(test_result, exp)  do {                                                                \
                                    u32 passed = (exp);                                             \
                                    test_result->passed += passed;                                  \
                                    test_result->count += 1;                                        \
                                                                                                    \
                                    printf("TEST: %s |%s|\n", #exp, (passed) ? "PASS" : "FAIL");    \
                                }while(0)

typedef struct TestResult {
    u32 count;
    u32 passed;
} TestResult;

#endif /* COMMON_H */