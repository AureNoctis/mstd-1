#include "common.h"
#include <stdio.h>

typedef struct TestStruct {
    int id;
    float value;
    char key[8];
} TestStruct;

mem_align_to(16) typedef struct TestStructAlign16 {
    int id;
    float value;
    char key[8];
} TestStructAlign16;

function void test_mem(TestResult* result) {
    char* name = "mstd";
    TEST(result, mem_match(name, "mstd", sizeof("mstd")));
    TEST(result, !mem_match(name, "diff", sizeof("diff")));

    arena_scratch_scope(arena) {
        char* temp = arena_push_array(arena, char, 10);
        mem_copy(temp, "hi", sizeof("hi"));
        TEST(result, mem_match(temp, "hi", sizeof("hi")));

        char* buffer = arena_push_array(arena, char, 8);
        mem_set(buffer, 'A', 4);
        mem_set(buffer + 4, 'B', 4);
        TEST(result, mem_match(buffer, "AAAABBBB", 8));

        mem_zero(buffer, 4);
        TEST(result, buffer[0] == 0 && buffer[3] == 0);
        TEST(result, buffer[4] == 'B');

        TestStruct* src = arena_push_struct(arena, TestStruct);
        src->id = 42;
        src->value = 3.14f;
        mem_copy(src->key, "valid", sizeof("valid"));

        TestStruct* dest = arena_push_struct(arena, TestStruct);
        mem_copy_struct(dest, src);
        TEST(result, dest->id == 42);
        TEST(result, dest->value == 3.14f);
        TEST(result, mem_match(dest->key, "valid", sizeof("valid")));

        mem_zero_struct(dest);
        TEST(result, dest->id == 0);
        TEST(result, dest->value == 0.0f);
        TEST(result, dest->key[0] == 0);

        int count = 5;
        TestStruct* src_array = arena_push_array(arena, TestStruct, count);
        for (int i = 0; i < count; ++i) {
            src_array[i].id = i + 100;
        }

        TestStruct* dest_array = arena_push_array(arena, TestStruct, count);
        mem_copy_array(dest_array, src_array, count);
        TEST(result, dest_array[0].id == 100);
        TEST(result, dest_array[4].id == 104);

        mem_zero_array(dest_array, count);
        TEST(result, dest_array[0].id == 0);
        TEST(result, dest_array[4].id == 0);

        char* overlap_buf = arena_push_array(arena, char, 11);
        mem_copy(overlap_buf, "0123456789", 11);

        mem_move(overlap_buf + 2, overlap_buf, 4);
        printf("%s", overlap_buf);
        TEST(result, mem_match(overlap_buf, "0101236789", 10));

        mem_copy(overlap_buf, "0123456789", 11);

        mem_move(overlap_buf, overlap_buf + 2, 4);
        TEST(result, mem_match(overlap_buf, "2345456789", 10));

        int* move_arr = arena_push_array(arena, int, 4);
        move_arr[0] = 10; move_arr[1] = 20; move_arr[2] = 30; move_arr[3] = 40;

        mem_move_array(move_arr + 1, move_arr, 2);
        TEST(result, move_arr[1] == 10);
        TEST(result, move_arr[2] == 20);

        TEST(result, mem_align_of(int) == sizeof(int));
        TEST(result, mem_align_of(TestStruct) == 4);
        TEST(result, mem_align_of(TestStructAlign16) == 16);
    }
}