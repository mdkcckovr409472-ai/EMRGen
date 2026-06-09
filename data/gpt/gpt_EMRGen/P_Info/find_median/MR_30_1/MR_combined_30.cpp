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


double find_median(int a[], int n) {
    int k = n / 2 + 1;
    int minIndex = 0;
    int minValue = a[0];
    for (int i = 0; i < k; i++) {
        minIndex = i;
        minValue = a[i];
        for (int j = i + 1; j < n; j++) {
            if (a[j] < minValue) {
                minIndex = j;
                minValue = a[j];
            }
        }
        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
    if (n % 2 == 0) {
        return (double) (a[n / 2 - 1] + a[n / 2]) / 2;
    } else {
        return a[n / 2];
    }
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){3, 1, 2}, 3},
    {(int[]){4, 3, 2, 1}, 4},
    {(int[]){0, -1, 5, 3, 2}, 5},
    {(int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){7, -3, 2, 2, 5, -1, 0}, 7},
    {(int[]){10, -10, 5, -5, 0, 3, -2, 1}, 8},
    {(int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3}, 9},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, 10},
    {(int[]){9, -9, 0}, 3},
    {(int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){0, 0, 1, 1}, 4},
    {(int[]){-3, 5, -1, 4, -2, 3}, 6},
    {(int[]){8, 7, 6, 5, 4, 3, 2}, 7},
    {(int[]){0, 0}, 2},
    {(int[]){-2, 4, -1, 3, 0}, 5},
    {(int[]){1, -1, 2, -2, 3, -3, 4, -4}, 8},
    {(int[]){5, 5, 4, 4, 3, 3, 2, 2, 1}, 9},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){9, 8, 7, 6, 5, 4}, 6},
    {(int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){2, -2, 2, -2}, 4},
    {(int[]){-5, 0, 5, -5, 0, 5, -5}, 7},
    {(int[]){0, 1, 0, 1, 0, 1, 0, 1}, 8},
    {(int[]){-9, -8, -7, -6, -5, -4, -3, -2, -1}, 9},
    {(int[]){3, -3, 3, -3, 0}, 5},
    {(int[]){1, 2, 1, 2, 1, 2}, 6},
    {(int[]){-3, 3}, 2},
    {(int[]){0, 0, 1}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z30Change(TestCase t1) {
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
    
    // Linear scaling: new = 3 * old + 5
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.a[i] = 3 * follow_case.a[i] + 5;
    }
    
    return follow_case;
}

#include <cmath>

int z30check(double result1, double result2) {
    // 1. Core evaluation logic (direct scalar comparison)
    // Invariant: 3 * result1 - result2 + 5 == 0
    // Rearranged: 3 * result1 + 5 == result2
    double epsilon = 1e-5;
    double A = 3 * result1 + 5;
    double B = result2;

    if (std::isnan(A) || std::isnan(B)) return 0;

    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z30runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z30Change(test_cases[test_case_id]);
    // 原始调用
    double source = find_median(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = find_median(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z30check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z30runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}