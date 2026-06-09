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


double autoCorrelation(double data[], int lag, double mean, double variance, int n){
    double run = 0;
    for (int i = lag; i < n; i++)
    {
        run += (data[i] - mean) * (data[i - lag] - mean);
    }
    
    return run / (n - lag) / variance;
}


typedef struct {
    double* data; int lag; double mean; double variance; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 1, 0.0, 1.0, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 0, 0.0, 1.0, 5},
    {(double[]){3.5, -2.2, 0.0, 4.1, -1.5, 2.8}, 2, 0.78, 4.5, 6},
    {(double[]){-5.0, 2.3, 4.4, -3.1, 0.0, 1.9, -2.2}, 3, -0.23, 7.0, 7},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 3, 2.0, 0.1, 4},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 1, 2.0, 0.1, 4},
    {(double[]){0.5, -0.7, 0.3, -0.2, 0.9}, 2, 0.16, 0.5, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 1, 0.0, 0.01, 4},
    {(double[]){10.0, -10.0, 10.0, -10.0, 10.0}, 2, 0.0, 100.0, 5},
    {(double[]){3.14}, 0, 3.14, 0.5, 1},
    {(double[]){1.0, -1.0}, 1, 0.0, 1.0, 2},
    {(double[]){2.0, 2.0, 2.0}, 2, 2.0, 0.2, 3},
    {(double[]){5.1, -3.2, 4.8, 0.0, -1.1, 2.2, -4.0, 3.3}, 4, 0.775, 8.0, 8},
    {(double[]){5.1, -3.2, 4.8, 0.0, -1.1, 2.2, -4.0, 3.3}, 0, 0.775, 8.0, 8},
    {(double[]){1.01, 0.99, 1.00, 1.02}, 1, 1.005, 0.0001, 4},
    {(double[]){-2.0, -3.5, -1.0, -4.5}, 2, -2.75, 2.0, 4},
    {(double[]){0.25, 0.75, -0.5, 1.5, -1.25}, 3, 0.15, 1.0, 5},
    {(double[]){1.0, 2.0, 3.0, 2.5, 1.5, 0.5, -0.5, -1.5, -2.0, -1.0}, 5, 0.5, 3.0, 10},
    {(double[]){1.0, 2.0, 3.0, 2.5, 1.5, 0.5, -0.5, -1.5, -2.0, -1.0}, 0, 0.5, 3.0, 10},
    {(double[]){4.4, 4.4, -2.2, 3.3, -2.2, 5.5}, 2, 2.3, 9.0, 6},
    {(double[]){4.4, 4.4, -2.2, 3.3, -2.2, 5.5}, 1, 2.3, 9.0, 6},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0}, 2, 0.0, 0.5, 5},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0}, 4, 0.0, 0.5, 5},
    {(double[]){7.2, -3.1, 4.6, -2.8, 0.9, 1.2}, 3, 0.8333, 10.0, 6},
    {(double[]){7.2, -3.1, 4.6, -2.8, 0.9, 1.2}, 0, 0.8333, 10.0, 6},
    {(double[]){2.5, -1.5, 3.0, -2.0, 0.0, 1.0, -3.5, 4.0, -0.5}, 5, 0.1111, 5.0, 9},
    {(double[]){2.5, -1.5, 3.0, -2.0, 0.0, 1.0, -3.5, 4.0, -0.5}, 2, 0.1111, 5.0, 9},
    {(double[]){5.0,5.0,5.0,5.0,5.0}, 2, 5.0, 0.2, 5},
    {(double[]){5.0,5.0,5.0,5.0,5.0}, 0, 5.0, 0.2, 5},
    {(double[]){-0.3, 0.7, -0.2}, 1, 0.067, 0.2, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z79Change(TestCase t1) {
    TestCase follow_case = t1;
    // Defensive check: avoid operation on zero variance
    if (follow_case.variance != 0.0) {
        follow_case.variance /= 2.0;
    }
    return follow_case;
}

#include <math.h>
#include <stdbool.h>

int z79check(double result1, double result2) {
    double epsilon = 1e-5;
    // Rearranged invariant: 2 * result1 == result2

    double A = 2 * result1;
    double B = result2;

    if (isnan(A) || isnan(B)) return 0;
    if (isinf(A) || isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z79runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z79Change(test_cases[test_case_id]);
    // 原始调用
    double source = autoCorrelation(test_cases[test_case_id].data, test_cases[test_case_id].lag, test_cases[test_case_id].mean, test_cases[test_case_id].variance, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = autoCorrelation(follow_case.data, follow_case.lag, follow_case.mean, follow_case.variance, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z79check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z79runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}