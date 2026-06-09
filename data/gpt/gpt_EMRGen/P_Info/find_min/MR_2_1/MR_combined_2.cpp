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


int find_min(int a[], int n) {
    int min = a[0];
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1},
    {(int[]){3, 7}, 2},
    {(int[]){10, -2}, 2},
    {(int[]){8, 3, 9, 1, 6}, 5},
    {(int[]){-5, -1, -9, -3}, 4},
    {(int[]){0, -1, 2, -3, 4}, 5},
    {(int[]){2, 2, 2, 2}, 4},
    {(int[]){5, 5, 1, 5}, 4},
    {(int[]){7, -8, 9, -10, 3, 2}, 6},
    {(int[]){4, 4, 4, -4, 4}, 5},
    {(int[]){-20, 15, -5, 0, 10}, 5},
    {(int[]){1, -1, 1, -1, 1}, 5},
    {(int[]){99, -99, 50, -50, 0}, 5},
    {(int[]){-3, 5, -1, 4, 0, -2, 3}, 7},
    {(int[]){6, -2, 7, -1, 8, -3, 9}, 7},
    {(int[]){42}, 1},
    {(int[]){-42}, 1},
    {(int[]){5, -5, 5, -5, 5, -5}, 6},
    {(int[]){8, 6, 7, 5, 3, 0, -2, -4}, 8},
    {(int[]){-7, -3, -5, -2, -9, -1}, 6},
    {(int[]){12, 0, -12, 6, -6, 3, -3}, 7},
    {(int[]){100, 50, 0, -50, -100}, 5},
    {(int[]){-10, 10, -20, 20, -30, 30}, 6},
    {(int[]){7, 7, 7, 7, 7, 7, 7}, 7},
    {(int[]){-5, 0, 5, -5, 0, 5}, 6},
    {(int[]){2, -3, 5, -8, 13, -21}, 6},
    {(int[]){9, 3, 6, 2, 8, 1, 7, 4, 5}, 9},
    {(int[]){-1, -2, -3, -4, -5, -6, -7, -8, -9}, 9},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){15, -15, 30, -30, 45, -45, 60}, 7}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z2Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive check: ensure there is at least one element
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Operation: subtract 5 from all elements (when element ≥ 5)
    for (int i = 0; i < follow_case.n; ++i) {
        if (follow_case.a[i] >= 5) {
            follow_case.a[i] -= 5;
        }
    }
    
    return follow_case;
}

int z2check(int result1, int result2) {
    if (!(result1 >= result2)) {
        return 0;
    }
    return 1;
}

TestResult z2runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z2Change(test_cases[test_case_id]);
    // 原始调用
    int source = find_min(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = find_min(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z2check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z2runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}