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

TestCase z23Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* new_a = (int*)malloc((t1.n + 1) * sizeof(int));
    if (!new_a) {
        return follow_case;
    }
    memcpy(new_a, t1.a, t1.n * sizeof(int));
    new_a[t1.n] = 0;
    follow_case.a = new_a;
    follow_case.n = t1.n + 1;
    // ------------------------------------
    return follow_case;
}

int z23check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        if (result1[i] >= result2[i]) {
            return 0;
        }
        else if (result1[i] < result2[i]) {
            return 1;
        }
    }
    return 0;
}

TestResult z23runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z23Change(test_cases[test_case_id]);
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
    int status = z23check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z23runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}