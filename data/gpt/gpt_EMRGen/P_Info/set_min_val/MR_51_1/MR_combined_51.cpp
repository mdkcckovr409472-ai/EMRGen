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


int* set_min_val(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        if (cp1[i] < k) {
            cp1[i] = k;
        }
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 5, 0 },
    { (int[]){1}, 5, 1 },
    { (int[]){5}, 5, 1 },
    { (int[]){10}, 5, 1 },
    { (int[]){2, 3}, 5, 2 },
    { (int[]){7, 2}, 5, 2 },
    { (int[]){8, 9}, 5, 2 },
    { (int[]){0, -1, 4}, 3, 3 },
    { (int[]){5, 2, 6}, 4, 3 },
    { (int[]){7, 8, 9}, 5, 3 },
    { (int[]){-5, -3, 0, 2}, -2, 4 },
    { (int[]){-1, -4, 3}, -2, 3 },
    { (int[]){-5, -1, 0, 2}, 0, 4 },
    { (int[]){1, 2, 3}, 0, 3 },
    { (int[]){3, 7, 1, 9, 2}, 5, 5 },
    { (int[]){0, 1, 2, 3, 4}, 6, 5 },
    { (int[]){10, 11, 12, 13, 14}, 5, 5 },
    { (int[]){5, 5, 5, 5}, 3, 4 },
    { (int[]){2, 2, 2, 2}, 5, 4 },
    { (int[]){2, 5, 2, 5, 2}, 4, 5 },
    { (int[]){10, 15, 20, 5}, 15, 4 },
    { (int[]){-10, -6, -4, 0}, -5, 4 },
    { (int[]){8, -2, 5, 1, 9, -3}, 4, 6 },
    { (int[]){-1, 0, 1, 2, 3, 4}, 5, 6 },
    { (int[]){6, 7, 8, 9, 10, 11}, 5, 6 },
    { (int[]){10, 1, 10, 1, 10, 1}, 5, 6 },
    { (int[]){0, 0, 0, 0}, 3, 4 },
    { (int[]){7, 7, 7}, 7, 3 },
    { (int[]){-3, 4, -1, 5}, 2, 4 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, 10 }
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z51Change(TestCase t1) {
    TestCase follow_case = t1;
    // Defensive checks (none required for this operation)

    // Operation: set k to min(k, 10)
    if (follow_case.k > 10) {
        follow_case.k = 10;
    }

    return follow_case;
}

int z51check(int* result1, int* result2, int n) {
    // 4. Defensive Programming and Boundary Checks
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    // 2. Core evaluation logic (elementwise) for return.result1[] >= return.result2[]
    for (int i = 0; i < n; i++) {
        if (!(result1[i] >= result2[i])) {
            return 0;
        }
    }

    // 3. Fully satisfied, return 1
    return 1;
}

TestResult z51runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z51Change(test_cases[test_case_id]);
    // 原始调用
    int* source = set_min_val(test_cases[test_case_id].a, test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = set_min_val(follow_case.a, follow_case.k, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z51check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z51runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}