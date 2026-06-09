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


int* clip(int a[], int lowerLim, int upperLim, int n) {
    int* r = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            if (a[i] < lowerLim) {
                r[i] = lowerLim;
            } else {
                if (a[i] > upperLim) {
                    r[i] = upperLim;
                } else {
                    r[i] = a[i];
                }
            }
        }
        return r;
    }
    


typedef struct {
    int* a; int lowerLim; int upperLim; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){5, 10, 15}, 7, 12, 3 },
    { (int[]){8, 9, 10}, 5, 15, 3 },
    { (int[]){1, 2, 3}, 5, 10, 3 },
    { (int[]){20, 25, 30}, 5, 15, 3 },
    { (int[]){-10, 0, 10, 20}, -5, 5, 4 },
    { (int[]){1, 2, 3}, 5, 5, 3 },
    { (int[]){}, 0, 10, 0 },
    { (int[]){7}, 5, 10, 1 },
    { (int[]){2}, 5, 10, 1 },
    { (int[]){12}, 5, 10, 1 },
    { (int[]){5, 10, 15}, 20, 10, 3 },
    { (int[]){12, 15, 18}, 20, 10, 3 },
    { (int[]){-20, -10, 0, 10, 20}, -15, 5, 5 },
    { (int[]){-5, 0, 5}, 0, 0, 3 },
    { (int[]){3, -1, 7, 12, 5, -8, 0, 9, 14, 2}, 4, 10, 10 },
    { (int[]){5, 5, 5, 5, 5}, 3, 7, 5 },
    { (int[]){1, 1, 9, 9, 10}, 3, 8, 5 },
    { (int[]){3, 7, 5}, 3, 7, 3 },
    { (int[]){2, 3, 4, 7, 8}, 3, 7, 5 },
    { (int[]){-3, 4, -1, 6, 2}, 0, 5, 5 },
    { (int[]){-10, -5}, -3, -7, 2 },
    { (int[]){-100, 0, 100}, -50, 50, 3 },
    { (int[]){0, 0, 0, 0}, -1, 1, 4 },
    { (int[]){9, -2, 5, -7, 3, 8}, 0, 6, 6 },
    { (int[]){2, 5, 8}, 8, 10, 3 },
    { (int[]){2, 5, 8}, 0, 2, 3 },
    { (int[]){-5, -2, 0, 2, 5}, -3, 3, 5 },
    { (int[]){1}, 5, 3, 1 },
    { (int[]){11, 12, 13, 14}, 10, 15, 4 },
    { (int[]){15, 10, 12, 8}, 10, 12, 4 }
};
int num_test_cases = 30;


    typedef struct {
        int* result1;
        int* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z22Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling for array 'a'
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;

    // Defensive check: ensure there is at least one element
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            if (follow_case.a[i] >= 0) {
                follow_case.a[i] = (int)floor(sqrt((double)follow_case.a[i]));
            }
            // If element is negative, leave it unchanged
        }
    }
    return follow_case;
}

int z22check(int* result1, int* result2, int n) {
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    for (int i = 0; i < n; i++) {
        if (!(result1[i] >= result2[i])) {
            return 0;
        }
    }

    return 1;
}

TestResult z22runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z22Change(test_cases[test_case_id]);
    // 原始调用
    int* source = clip(test_cases[test_case_id].a, test_cases[test_case_id].lowerLim, test_cases[test_case_id].upperLim, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int* follow = clip(follow_case.a, follow_case.lowerLim, follow_case.upperLim, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z22check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z22runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}