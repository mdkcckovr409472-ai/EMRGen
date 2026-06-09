#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <climits>
#include <cfloat>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int get_array_value(int a[], int k, int n) {
        return a[k - 1];
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1, 1},
    {(int[]){0, -1, 2}, 2, 3},
    {(int[]){3, 3, 3, 3}, 4, 4},
    {(int[]){-5, 10, -2, 7}, 3, 4},
    {(int[]){1, 2, 3, 4, 5}, 5, 5},
    {(int[]){9, 1, 8, 2, 7, 3}, 2, 6},
    {(int[]){0, 0, 0, 0, 0}, 4, 5},
    {(int[]){-3, 4, -1, 6, -2}, 1, 5},
    {(int[]){2, -2, 2, -2, 2}, 5, 5},
    {(int[]){8, -7, 6, -5, 4, -3, 2, -1}, 8, 8},
    {(int[]){100, -100, 50, -50}, 3, 4},
    {(int[]){7, 7, 5, 5, 3, 3, 1, 1}, 6, 8},
    {(int[]){1, -1, 1, -1, 1}, 2, 5},
    {(int[]){4, 2, 0, -2, -4}, 4, 5},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9, 9},
    {(int[]){5, -3, 9, -8, 2}, 3, 5},
    {(int[]){0}, 1, 1},
    {(int[]){-10, 10, -9, 9, -8, 8}, 5, 6},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6, 5}, 7, 9},
    {(int[]){2, 4, 8, 16, 32}, 4, 5},
    {(int[]){1, 0, -1, 0, 1}, 5, 5},
    {(int[]){6, -6, 6, -6, 6, -6}, 2, 6},
    {(int[]){5, -4, 3, -2, 1, 0, -1, 2, -3, 4}, 10, 10},
    {(int[]){7, 2, -5, 3, -1}, 3, 5},
    {(int[]){0, 1, 0, 1, 0, 1}, 6, 6},
    {(int[]){9, -9, 8, -8, 7, -7}, 1, 6},
    {(int[]){3, -3, 3, -3, 3}, 4, 5},
    {(int[]){2, 5, 2, 5, 2, 5, 2}, 7, 7},
    {(int[]){1, 2, 3, 2, 1}, 2, 5},
    {(int[]){4, -2, 0, 2, -4}, 5, 5}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z8Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling for deep copy of array 'a'
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // Defensive check: ensure there is at least one element
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            follow_case.a[i] = -follow_case.a[i];
        }
    }
    return follow_case;
}

int z8check(int result1, int result2) {
    if (!(result1 + result2 == 0)) {
        return 0;
    }
    return 1;
}

TestResult z8runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z8Change(test_cases[test_case_id]);
    // 原始调用
    int source = get_array_value(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = get_array_value(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z8check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z8runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}