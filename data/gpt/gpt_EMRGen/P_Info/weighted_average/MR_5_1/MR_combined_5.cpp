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


double weighted_average(double a[], double b[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    for(int i = 0; i < n; i++) {
        sum1 += a[i] * b[i];
        sum2 += b[i];
    }
    return sum1 / sum2;
}


typedef struct {
    double* a; double* b; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3 },
    { (double[]){-1.5, 0.0, 2.5}, (double[]){3.0, -2.0, 1.0}, 3 },
    { (double[]){0.0}, (double[]){5.0}, 1 },
    { (double[]){10.0, -10.0}, (double[]){-5.0, 5.0}, 2 },
    { (double[]){2.2, 2.2, 2.2}, (double[]){1.0, 1.0, 1.0}, 3 },
    { (double[]){-3.3, 4.4, -5.5, 6.6}, (double[]){7.7, -8.8, 9.9, -10.0}, 4 },
    { (double[]){9.9, -9.9}, (double[]){0.1, 0.2}, 2 },
    { (double[]){5.5, 5.5, 5.5, 5.5, 5.5}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5 },
    { (double[]){-0.1, -0.2, -0.3}, (double[]){0.3, 0.2, 0.1}, 3 },
    { (double[]){3.14, 2.71}, (double[]){1.41, 1.73}, 2 },
    { (double[]){-7.0, 8.0, 9.0}, (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){0.5, -0.5, 0.5}, (double[]){2.0, 2.0, 2.0}, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4 },
    { (double[]){-2.0, -4.0, -6.0}, (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){7.0, 8.0, 9.0}, (double[]){1.0, 0.0, 1.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3 },
    { (double[]){-5.0, 5.0, -5.0, 5.0}, (double[]){1.0, -1.0, 1.0, 2.0}, 4 },
    { (double[]){3.0}, (double[]){-3.0}, 1 },
    { (double[]){2.5, -2.5}, (double[]){-2.5, 2.5}, 2 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5 },
    { (double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, 1.0}, 3 },
    { (double[]){9.0, 8.0, 7.0}, (double[]){0.1, 0.2, 0.3}, 3 },
    { (double[]){-9.0, -8.0, -7.0}, (double[]){0.3, 0.2, 0.1}, 3 },
    { (double[]){0.123, 0.456}, (double[]){0.789, 0.012}, 2 },
    { (double[]){-0.5, 0.5, -0.5, 0.5}, (double[]){2.0, 2.0, 2.0, 2.0}, 4 },
    { (double[]){6.0, -6.0, 6.0}, (double[]){-2.0, 2.0, -2.0}, 3 },
    { (double[]){3.33, 6.66}, (double[]){1.11, 2.22}, 2 },
    { (double[]){-3.33, -6.66}, (double[]){-1.11, -2.22}, 2 },
    { (double[]){0.0, 1.0, -1.0, 2.0, -2.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5 },
    { (double[]){5.0, 5.0, 5.0}, (double[]){0.5, 0.5, 0.5}, 3 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z5Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_a = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(double));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive programming: ensure there is at least one element
    if (follow_case.n > 0) {
        if (follow_case.a[0] > 0.0) {
            follow_case.a[0] = 0.0;
        }
    }
    
    return follow_case;
}

int z5check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A >= B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (A < B - tol) return 0;

    return 1;
}

TestResult z5runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z5Change(test_cases[test_case_id]);
    // 原始调用
    double source = weighted_average(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = weighted_average(follow_case.a, follow_case.b, follow_case.n);
    
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