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


double quantile(double sortedElements[], double phi, int n) {      
    double index = phi * (n - 1);
    int lhs = (int) index;
    double delta = index - lhs;
    double result;
    if (n == 0) {
        return 0.0;
    }
    if (lhs == n - 1) {
        result = sortedElements[lhs];
    } else {
        result = (1 - delta) * sortedElements[lhs] + delta * sortedElements[lhs + 1];
    }
    return result;
}


typedef struct {
    double* sortedElements; double phi; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0.5, 0 },
    { (double[]){5.0}, 0.0, 1 },
    { (double[]){5.0}, 0.5, 1 },
    { (double[]){5.0}, 1.0, 1 },
    { (double[]){1.0, 3.0}, 0.0, 2 },
    { (double[]){1.0, 3.0}, 1.0, 2 },
    { (double[]){1.0, 3.0}, 0.5, 2 },
    { (double[]){-2.5, 0.0, 4.5}, 0.0, 3 },
    { (double[]){-2.5, 0.0, 4.5}, 1.0, 3 },
    { (double[]){-2.5, 0.0, 4.5}, 0.5, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, 0.25, 4 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, 0.75, 4 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 3.0}, 0.4, 5 },
    { (double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, 0.6, 5 },
    { (double[]){0.1, 0.4, 0.9, 2.5, 5.0, 9.0}, 0.33, 6 },
    { (double[]){0.1, 0.4, 0.9, 2.5, 5.0, 9.0}, 0.9, 6 },
    { (double[]){-3.2, -1.1, 0.0, 0.5, 2.2, 3.8, 7.7}, 0.123, 7 },
    { (double[]){-3.2, -1.1, 0.0, 0.5, 2.2, 3.8, 7.7}, 0.987, 7 },
    { (double[]){1.5, 1.5, 2.5, 3.5, 3.5, 4.5, 5.5, 5.5}, 0.5, 8 },
    { (double[]){1.5, 1.5, 2.5, 3.5, 3.5, 4.5, 5.5, 5.5}, 0.0, 8 },
    { (double[]){1.5, 1.5, 2.5, 3.5, 3.5, 4.5, 5.5, 5.5}, 1.0, 8 },
    { (double[]){-8.0, -3.0, -1.0, 0.0, 1.0, 4.0, 6.0, 9.0, 12.0}, 0.45, 9 },
    { (double[]){-8.0, -3.0, -1.0, 0.0, 1.0, 4.0, 6.0, 9.0, 12.0}, 0.55, 9 },
    { (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 0.2, 10 },
    { (double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 0.8, 10 },
    { (double[]){0.01, 0.02, 0.05, 0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4}, 0.75, 10 },
    { (double[]){0.01, 0.02, 0.05, 0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4}, 0.33, 10 },
    { (double[]){-5.0, -3.0, -1.0, 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 0.5, 11 },
    { (double[]){-5.0, -3.0, -1.0, 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 0.999, 11 },
    { (double[]){0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5}, 0.001, 12 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z38Change(TestCase t1) {
    TestCase follow_case = t1;
    // Defensive programming: none required for phi operation
    if (follow_case.phi > DBL_MIN) {
        follow_case.phi = DBL_MIN;
    }
    return follow_case;
}

int z38check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;
    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A >= B) return 1;
        else return 0;
    }
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    if (A < B - tol) {
        return 0;
    }
    return 1;
}

TestResult z38runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z38Change(test_cases[test_case_id]);
    // 原始调用
    double source = quantile(test_cases[test_case_id].sortedElements, test_cases[test_case_id].phi, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = quantile(follow_case.sortedElements, follow_case.phi, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z38check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z38runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}