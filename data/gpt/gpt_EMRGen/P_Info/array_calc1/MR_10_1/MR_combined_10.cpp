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


int* array_calc1(int a[], int k, int n) {
    int* b = (int*)malloc(n * sizeof(int));
    if (b == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        double val = (double)a[i] / k;
        b[i] = (int)round(val); 
    }
    return b;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){2, 4, 6}, 2, 3},
    {(int[]){-3, -5, 7}, 2, 3},
    {(int[]){0, 5, -5}, -1, 3},
    {(int[]){10, -10, 5, -5}, 5, 4},
    {(int[]){1, 2, 3, 4, 5}, 1, 5},
    {(int[]){9, 5, 8, 4, 7, 3}, 3, 6},
    {(int[]){-9, -5, -8, -4, -7, -2}, -3, 6},
    {(int[]){15, 20, 25}, 5, 3},
    {(int[]){-15, -25, -20}, -5, 3},
    {(int[]){3, -3, 0}, 2, 3},
    {(int[]){100, -100}, 10, 2},
    {(int[]){7}, 3, 1},
    {(int[]){-7}, -3, 1},
    {(int[]){0}, 5, 1},
    {(int[]){}, 1, 0},
    {(int[]){1, -1, 2, -2, 3, -3}, 2, 6},
    {(int[]){15, 5, 20, 10}, 4, 4},
    {(int[]){-20, -5, -15, -10}, 4, 4},
    {(int[]){2, 3, 5, 7, 11}, 2, 5},
    {(int[]){-5, -11, -2, -7, -3}, -2, 5},
    {(int[]){24, 8, 16}, 6, 3},
    {(int[]){-24, -8, -16}, -6, 3},
    {(int[]){13, 26, 39}, 13, 3},
    {(int[]){-13, -26, -39}, -13, 3},
    {(int[]){1, 4, 9, 16, 25}, 5, 5},
    {(int[]){-1, -4, -9, -16, -25}, -5, 5},
    {(int[]){12, 3, 9, 6}, 4, 4},
    {(int[]){-12, -3, -9, -6}, -4, 4},
    {(int[]){2, -4, 6, -8, 10}, 3, 5},
    {(int[]){-2, 4, -6, 8, -10}, -3, 5}
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z10Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ---------------------------

    // Defensive check: ensure there is at least one element to process
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n / 2; ++i) {
            int temp = follow_case.a[i];
            follow_case.a[i] = follow_case.a[follow_case.n - 1 - i];
            follow_case.a[follow_case.n - 1 - i] = temp;
        }
    }

    return follow_case;
}

int z10check(int* result1, int* result2, int n) {
    // 1. Defensive programming (length and null pointer checks)
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    // 2. Core evaluation logic (elementwise reverse check)
    for (int i = 0; i < n; i++) {
        if (result1[i] != result2[n - 1 - i]) {
            return 0;
        }
    }

    // 3. Fully satisfied, return 1
    return 1;
}

TestResult z10runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z10Change(test_cases[test_case_id]);
    // 原始调用
    int* source = array_calc1(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = array_calc1(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z10check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z10runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}