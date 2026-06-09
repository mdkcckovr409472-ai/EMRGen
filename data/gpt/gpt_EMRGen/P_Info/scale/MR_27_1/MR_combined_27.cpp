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


double* scale(double val, double arr[], int n) {
    double* newArr = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        newArr[i] = arr[i] * val;
    }
    return newArr;
}


typedef struct {
    double val; double* arr; int n;
} TestCase;

TestCase test_cases[] = {
    {0.0, (double[]){}, 0},
    {1.0, (double[]){2.5, -3.1, 4.0}, 3},
    {-2.0, (double[]){10.0, -5.5, 0.0, 3.3}, 4},
    {0.5, (double[]){-1.2, 2.8, -4.4, 5.5, -6.6}, 5},
    {3.14, (double[]){1.0, 1.0, 1.0}, 3},
    {-0.75, (double[]){8.8, -9.9, 0.1, -0.2, 0.3, -0.4}, 6},
    {2.0, (double[]){-7.0, 7.0}, 2},
    {1.5, (double[]){3.3, -2.2, 1.1, 0.0, -1.1, 2.2, -3.3}, 7},
    {-1.0, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5},
    {0.25, (double[]){-0.5, 0.5, -0.75, 0.75}, 4},
    {4.0, (double[]){9.9, -9.8, 9.7, -9.6, 9.5}, 5},
    {-3.5, (double[]){2.2, -2.2, 2.2, -2.2}, 4},
    {1.0, (double[]){0.0}, 1},
    {-0.1, (double[]){-0.1, 0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8}, 8},
    {2.5, (double[]){-1.0, -2.0, -3.0}, 3},
    {-2.5, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {0.33, (double[]){7.7, -8.8, 9.9}, 3},
    {5.0, (double[]){-5.0, 0.0, 5.0}, 3},
    {-1.25, (double[]){-10.0, 10.0, -20.0, 20.0}, 4},
    {0.66, (double[]){3.14, 2.71, 1.41, 0.577, 0.0}, 5},
    {3.0, (double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, 7},
    {-0.5, (double[]){0.25, -0.25, 0.5, -0.5}, 4},
    {1.2, (double[]){-4.4, 4.4, -2.2, 2.2, -1.1, 1.1}, 6},
    {-0.8, (double[]){9.0, -9.0, 8.0, -8.0, 7.0, -7.0, 6.0, -6.0}, 8},
    {0.0, (double[]){100.0, -100.0, 50.0, -50.0}, 4},
    {0.9, (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5},
    {-0.3, (double[]){-0.3, 0.6, -0.9, 1.2, -1.5}, 5},
    {2.2, (double[]){-1.5, 2.5, -3.5, 4.5, -5.5, 6.5}, 6}
};
int num_test_cases = 28;


    typedef struct {
        double* result1;
        double* result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z27Change(TestCase t1) {
    TestCase follow_case = t1;
    // Increase val by 10%
    follow_case.val = follow_case.val * 1.10;
    return follow_case;
}

#include <math.h>
#include <float.h>

int z27check(double* result1, double* result2, int n) {
    // 1. Defensive programming (length and null pointer checks)
    if (n <= 0) return 1;
    if (result1 == NULL || result2 == NULL) return 0;

    double epsilon = 1e-5;
    for (int i = 0; i < n; i++) {
        // rearranged condition:
        // 1.1 * result1[i] == result2[i]
        // => A = 1.1 * result1[i], B = result2[i]
        double A = 1.1 * result1[i];
        double B = result2[i];

        if (isnan(A) || isnan(B)) return 0;
        if (isinf(A) || isinf(B)) {
            if (A == B) continue;
            else return 0;
        }
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
        if (fabs(A - B) > tol) return 0;
    }
    return 1;
}

TestResult z27runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z27Change(test_cases[test_case_id]);
    // 原始调用
    double* source = scale(test_cases[test_case_id].val, test_cases[test_case_id].arr, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = scale(follow_case.val, follow_case.arr, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z27check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z27runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}