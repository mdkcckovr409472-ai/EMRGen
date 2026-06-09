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


double variance(double x[], int n) {
    double sum = 0;
    double sum1 = 0;
    double var = 0;
    double avrg = 0;
    for(int i = 0; i < n; i++) {
        sum = sum + x[i];
    }
    
    avrg = sum / (double)n;
    for (int i = 0; i < n; i++) {
        sum1 = sum1 + (x[i] - avrg) * (x[i] - avrg);
    }
    var = sum1 / (double) n;
    return var;
}


typedef struct {
    double* x; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){5.5}, 1 },
    { (double[]){2.2, 2.2}, 2 },
    { (double[]){-1.0, 2.0, -3.0, 4.0}, 4 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5 },
    { (double[]){-50.0, -20.0, -30.0}, 3 },
    { (double[]){3.5, -2.1, 7.8, 0.0, -5.5}, 5 },
    { (double[]){1.0, -1.0, 1.0, -1.0}, 4 },
    { (double[]){10.0, 10.0, 10.0, 10.0}, 4 },
    { (double[]){0.0, 5.0, 0.0, 5.0}, 4 },
    { (double[]){1.0, 2.0, 2.0, 3.0}, 4 },
    { (double[]){5.0, 4.0, 4.0, 3.0}, 4 },
    { (double[]){-3.3, 4.4, -1.1, 2.2, 0.0, 5.5, -2.2, 3.3}, 8 },
    { (double[]){9.9, -9.9, 8.8, -8.8, 7.7, -7.7, 6.6, -6.6, 0.0}, 9 },
    { (double[]){0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10}, 10 },
    { (double[]){99.9, 80.0, 70.5, 60.2, 50.1, 40.0}, 6 },
    { (double[]){1.0, 2.5, -3.75}, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0}, 5 },
    { (double[]){1e-6, -1e-6, 2e-6, -2e-6}, 4 },
    { (double[]){5.5, -4.4, 3.3, -2.2, 1.1, 0.0, -0.5}, 7 },
    { (double[]){0.0, 3.14}, 2 },
    { (double[]){-7.0, -7.0, -7.0}, 3 },
    { (double[]){1.0, 2.0, 3.0, 2.0, 1.0}, 5 },
    { (double[]){-99.9, 0.0, 99.9, -50.5, 50.5, -0.1}, 6 },
    { (double[]){2.5, 2.0, 2.5, 2.0}, 4 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0}, 9 },
    { (double[]){100.0, 101.0, 99.5, 100.5, 100.2}, 5 },
    { (double[]){0.333, 0.666, 0.999}, 3 },
    { (double[]){-0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.7, -0.8}, 8 },
    { (double[]){0.0, 50.0, -50.0, 25.0, -25.0, 0.0}, 6 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z9Change(TestCase t1) {
    TestCase follow_case = t1;
    // Deep copy of the array
    double* follow_case_x = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_x, t1.x, t1.n * sizeof(double));
    follow_case.x = follow_case_x;

    // Defensive check: need at least two elements to swap
    if (follow_case.n < 2) {
        return follow_case;
    }

    // Swap two random elements
    int idx1 = rand() % follow_case.n;
    int idx2 = rand() % follow_case.n;
    while (idx2 == idx1) {
        idx2 = rand() % follow_case.n;
    }
    double temp = follow_case.x[idx1];
    follow_case.x[idx1] = follow_case.x[idx2];
    follow_case.x[idx2] = temp;

    return follow_case;
}

int z9check(double result1, double result2) {
    const double epsilon = 1e-5;
    // Rearranged: compare result1 and result2 directly (==)
    double A = result1;
    double B = result2;
    // NaN check
    if (std::isnan(A) || std::isnan(B)) return 0;
    // Inf check
    if (std::isinf(A) || std::isinf(B)) {
        return (A == B) ? 1 : 0;
    }
    // Calculate tolerance
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    // Compare with tolerance for equality
    if (fabs(A - B) > tol) return 0;
    return 1;
}

TestResult z9runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z9Change(test_cases[test_case_id]);
    // 原始调用
    double source = variance(test_cases[test_case_id].x, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = variance(follow_case.x, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z9check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z9runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}