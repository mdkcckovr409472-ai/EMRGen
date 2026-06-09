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


double kurtosis(double data[], int n) {
    double sum = 0;
    double sumPD = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
        sumSq += data[i] * data[i];
    }
    double mean = sum / n;
    double standardDeviation = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        sumPD += pow(data[i] - mean, 4);
    }
    double moment4 = sumPD / n;
    return -3 + moment4 / (standardDeviation * standardDeviation * standardDeviation * standardDeviation);
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0}, 2},
    {(double[]){-1.5, 0.5, 2.5}, 3},
    {(double[]){0.0, 0.0, 1.0, -1.0}, 4},
    {(double[]){3.3, -2.2, 5.5, -4.4, 0.0}, 5},
    {(double[]){10.0, -10.0, 5.0, -5.0, 2.5, -2.5}, 6},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7}, 7},
    {(double[]){-3.0, -1.0, 0.0, 1.0, 3.0, 5.0, -5.0, 2.0}, 8},
    {(double[]){0.5, -0.5, 0.25, -0.25, 0.75, -0.75, 1.0, -1.0, 0.0}, 9},
    {(double[]){20.0, 2.0, 18.0, 4.0, 16.0, 6.0, 14.0, 8.0, 12.0, 10.0}, 10},
    {(double[]){-20.0, -2.0, -18.0, -4.0, -16.0, -6.0, -14.0, -8.0, -12.0, -10.0}, 10},
    {(double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, 6},
    {(double[]){5.5, 5.5, -5.5, -5.5, 0.0, 0.0}, 6},
    {(double[]){3.1415, 2.718, 1.618, -1.0, -2.0, -3.0}, 6},
    {(double[]){-0.1, 0.2, -0.3, 0.4, -0.5, 0.6, -0.7, 0.8}, 8},
    {(double[]){100.0, -50.0, 25.0, -12.5, 6.25, -3.125, 1.5625}, 7},
    {(double[]){0.03, 0.01, 0.05, 0.02, 0.04}, 5},
    {(double[]){-0.04, -0.01, -0.05, -0.02, -0.03}, 5},
    {(double[]){9.9, -9.9, 8.8, -8.8, 7.7, -7.7, 6.6, -6.6}, 8},
    {(double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, 6},
    {(double[]){-1.0, -1.0, -1.0, 0.0, 0.0, 1.0, 1.0, 1.0}, 8},
    {(double[]){2.5, -2.5, 2.5, -2.5, 2.5, -2.5}, 6},
    {(double[]){3.0, 3.0, 3.0, 3.0, 4.0}, 5},
    {(double[]){-3.0, -3.0, -3.0, -3.0, -4.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 1.0, -1.0, 2.0, -2.0}, 7},
    {(double[]){5.0, -5.0, 5.0, -5.0, 5.0, -5.0, 5.0, -5.0}, 8},
    {(double[]){4.8, 1.2, 6.0, 2.4, 7.2, 3.6}, 6},
    {(double[]){-4.8, -1.2, -6.0, -2.4, -7.2, -3.6}, 6},
    {(double[]){0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0}, 7},
    {(double[]){100.0, 0.0, -100.0, 50.0, -50.0}, 5},
    {(double[]){0.123, -0.456, 0.789, -0.321, 0.654}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z14Change(TestCase t1) {
    TestCase follow_case = t1;
    // Deep copy of the array
    double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
    follow_case.data = follow_case_data;

    // Defensive check: need at least 2 elements to swap
    if (follow_case.n < 2) {
        return follow_case;
    }

    // Swap two random elements
    int idx1 = rand() % follow_case.n;
    int idx2 = rand() % follow_case.n;
    if (idx1 == idx2) {
        idx2 = (idx2 + 1) % follow_case.n;
    }
    double temp = follow_case.data[idx1];
    follow_case.data[idx1] = follow_case.data[idx2];
    follow_case.data[idx2] = temp;

    return follow_case;
}

int z14check(double result1, double result2) {
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

TestResult z14runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z14Change(test_cases[test_case_id]);
    // 原始调用
    double source = kurtosis(test_cases[test_case_id].data, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = kurtosis(follow_case.data, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z14check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z14runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}