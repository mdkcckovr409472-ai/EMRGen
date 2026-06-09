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


double varianceDifference(double sample1[], double sample2[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    double diff = 0;
    double sumDifference = 0;

    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    
    double meanDifference = sumDifference / n;
    for (int i = 0; i < n; i++) {
        diff = sample1[i] - sample2[i];
        sum1 += (diff - meanDifference) * (diff - meanDifference);
        sum2 += diff - meanDifference;
    }
    return (sum1 - sum2 * sum2 / n) / (n - 1);
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0}, 3},
    {(double[]){0.0, -1.0, 4.5}, (double[]){2.0, 3.0, -1.5}, 3},
    {(double[]){-2.5, 0.0, 2.5, 5.0}, (double[]){5.0, 2.5, 0.0, -2.5}, 4},
    {(double[]){3.3, -3.3, 1.1, -1.1, 0.0}, (double[]){0.0, 1.1, -1.1, 3.3, -3.3}, 5},
    {(double[]){10.0, -10.0}, (double[]){-10.0, 10.0}, 2},
    {(double[]){2.2, 4.4, 6.6, 8.8}, (double[]){1.1, 3.3, 5.5, 7.7}, 4},
    {(double[]){-0.5, 0.5, -0.5, 0.5}, (double[]){0.5, -0.5, 0.5, -0.5}, 4},
    {(double[]){7.0, 3.0, -2.0, 4.0, 1.0}, (double[]){1.0, 4.0, -2.0, 3.0, 7.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){5.5, 5.5, 5.5}, (double[]){5.5, 5.5, 5.5}, 3},
    {(double[]){-3.0, 2.0, -1.0, 4.0}, (double[]){4.0, -1.0, 2.0, -3.0}, 4},
    {(double[]){1.2, 3.4, 5.6, 7.8, 9.0}, (double[]){9.0, 7.8, 5.6, 3.4, 1.2}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, (double[]){-4.0, -3.0, -2.0, -1.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){0.5, 0.4, 0.3, 0.2, 0.1}, 5},
    {(double[]){2.0, -2.0, 2.0, -2.0, 2.0}, (double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){3.14, 2.71, 1.41, 0.0}, (double[]){0.0, 1.41, 2.71, 3.14}, 4},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){5.0, 0.0, -5.0}, 3},
    {(double[]){1.0, 1.0, 2.0, 2.0, 3.0, 3.0}, (double[]){3.0, 3.0, 2.0, 2.0, 1.0, 1.0}, 6},
    {(double[]){-0.1, 0.2, -0.3, 0.4}, (double[]){0.4, -0.3, 0.2, -0.1}, 4},
    {(double[]){4.5, -4.5, 4.5, -4.5}, (double[]){-4.5, 4.5, -4.5, 4.5}, 4},
    {(double[]){2.5, 3.5, 4.5}, (double[]){3.0, 3.0, 3.0}, 3},
    {(double[]){0.0, 1.0, 0.0, 1.0, 0.0}, (double[]){1.0, 0.0, 1.0, 0.0, 1.0}, 5},
    {(double[]){-2.2, 2.2, -2.2, 2.2}, (double[]){2.2, -2.2, 2.2, -2.2}, 4},
    {(double[]){5.0, 0.0, -5.0, 0.0}, (double[]){0.0, 5.0, 0.0, -5.0}, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, (double[]){4.5, 3.5, 2.5, 1.5}, 4},
    {(double[]){-1.5, -0.5, 0.5, 1.5}, (double[]){1.5, 0.5, -0.5, -1.5}, 4},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 5},
    {(double[]){9.9, -9.9, 9.9, -9.9, 9.9}, (double[]){-9.9, 9.9, -9.9, 9.9, -9.9}, 5},
    {(double[]){3.0, 1.0, 4.0, 1.5}, (double[]){1.5, 4.0, 1.0, 3.0}, 4},
    {(double[]){2.0, 0.0, -2.0, 0.0, 2.0}, (double[]){0.0, 2.0, 0.0, -2.0, 0.0}, 5}
};
int num_test_cases = 31;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z32Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling for sample2
    double* follow_case_sample2 = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_sample2, t1.sample2, t1.n * sizeof(double));
    follow_case.sample2 = follow_case_sample2;
    // Defensive check for array length
    if (follow_case.n <= 0) {
        return follow_case;
    }
    // Subtract 2.5 from each element of sample2
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.sample2[i] -= 2.5;
    }
    return follow_case;
}

int z32check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
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

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double source = varianceDifference(test_cases[test_case_id].sample1, test_cases[test_case_id].sample2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = varianceDifference(follow_case.sample1, follow_case.sample2, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z32check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z32runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}