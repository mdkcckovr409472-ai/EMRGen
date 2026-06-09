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


int find_max2(int a[], int n) {
    int max = a[0] + a[1];
    for (int i = 0; i < n - 1; i++) {
        if (a[i] + a[i + 1] > max) {
            max = a[i] + a[i + 1];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){1, 2, 3, 4}, 4 },
    { (int[]){5, 5, 5, 5}, 4 },
    { (int[]){-1, -2, -3, -4}, 4 },
    { (int[]){10, -5, 3, -2, 8}, 5 },
    { (int[]){1, 2, 100, 3, 4}, 5 },
    { (int[]){50, 50, 1, 2, 3}, 5 },
    { (int[]){1, 2, 3, 40, 40}, 5 },
    { (int[]){0, 0, 0, 0}, 4 },
    { (int[]){7, -7, 7, -7, 7}, 5 },
    { (int[]){3, -1, 4, -2, 5, -3}, 6 },
    { (int[]){9, -1}, 2 },
    { (int[]){0, 0}, 2 },
    { (int[]){1, 2, 3}, 3 },
    { (int[]){-10, 20, -30, 40}, 4 },
    { (int[]){-50, -40, -30, -20}, 4 },
    { (int[]){0, 5, 0, 5, 0}, 5 },
    { (int[]){12, -3, 7, 19, -8, 4}, 6 },
    { (int[]){5, 5, 5, 5, 5}, 5 },
    { (int[]){-99, -1, -2, -3}, 4 },
    { (int[]){1, 9, 1, 9, 1}, 5 },
    { (int[]){20, 15, 10, 5, 10, 15, 20}, 7 },
    { (int[]){8, -6, 2, 9, -1, 3, 7}, 7 },
    { (int[]){-5, -4, -3, 2, -1}, 5 },
    { (int[]){1, 2, 3, 4, 100, 5, 6}, 7 },
    { (int[]){3, 1, 4, 1, 3}, 5 },
    { (int[]){-2, 7, -3, 8, -1, 6, -4, 5}, 8 },
    { (int[]){0, 0, 0, 10, 0, 0}, 6 },
    { (int[]){-99, 99, -50, 50}, 4 },
    { (int[]){2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 10 },
    { (int[]){1, 2, 1, 2, 1, 2, 1, 2}, 8 }
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z5Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive check for array length (requires at least 1 element)
    if (follow_case.n == 0) {
        return follow_case;
    }
    
    // Operation: set first element to 0 when it is greater than 0
    if (follow_case.a[0] > 0) {
        follow_case.a[0] = 0;
    }
    
    return follow_case;
}

int z5check(int result1, int result2) {
    if (!(result1 >= result2)) {
        return 0;
    }
    return 1;
}

TestResult z5runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z5Change(test_cases[test_case_id]);
    // 原始调用
    int source = find_max2(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = find_max2(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z5check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z5runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}