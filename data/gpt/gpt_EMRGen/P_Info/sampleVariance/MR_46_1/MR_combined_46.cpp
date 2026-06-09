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


double sampleVariance(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        double delta = elements[i] - mean;
        sum += delta * delta;
    }
    return sum / (size - 1);
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, 2.0, 3 },
    { (double[]){5.5, -2.2, 7.1, 0.0}, 2.6, 4 },
    { (double[]){10.0, 10.0, 10.0, 10.0}, 10.0, 4 },
    { (double[]){-1.0, 2.5, -3.5, 4.0, -5.0}, -0.6, 5 },
    { (double[]){0.1, 0.2, 0.3, 0.4}, 0.25, 4 },
    { (double[]){100.0, -100.0, 50.0, -50.0}, 0.0, 4 },
    { (double[]){3.1415, 2.7182, 1.618, 0.5772}, 2.013725, 4 },
    { (double[]){-0.5, -0.1, 0.2, 0.8, -0.3}, 0.02, 5 },
    { (double[]){9.9, 8.8, 7.7, 6.6, 5.5, 4.4}, 7.15, 6 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 3.0, 3.0}, 2.0, 6 },
    { (double[]){-10.0, 10.0}, 0.0, 2 },
    { (double[]){0.0, 0.0}, 0.0, 2 },
    { (double[]){0.5, -0.5}, 0.0, 2 },
    { (double[]){1.5, 2.5, 3.5}, 2.5, 3 },
    { (double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 0.0, 5 },
    { (double[]){0.001, 0.002, 0.003, 0.004}, 0.0025, 4 },
    { (double[]){99.9, 0.1, -99.8, -0.2}, 0.0, 4 },
    { (double[]){5.0, 6.0, 7.0, 8.0, 9.0}, 7.0, 5 },
    { (double[]){-3.3, 4.4, -5.5, 6.6, -7.7, 8.8}, 0.55, 6 },
    { (double[]){2.0, 2.0, 2.0, 3.0}, 2.25, 4 },
    { (double[]){-0.01, 0.01, -0.02, 0.02}, 0.0, 4 },
    { (double[]){1.0, 4.0, 9.0, 16.0}, 7.5, 4 },
    { (double[]){0.0, 1.0, 0.0, 1.0}, 0.5, 4 },
    { (double[]){-1.5, 0.0, 1.5}, 0.0, 3 },
    { (double[]){3.0, -3.0, 3.0, -3.0, 3.0}, 0.6, 5 },
    { (double[]){0.123, 0.456, 0.789}, 0.456, 3 },
    { (double[]){-100.0, -50.0, 0.0, 50.0, 100.0}, 0.0, 5 },
    { (double[]){0.25, 0.75, 0.5}, 0.5, 3 },
    { (double[]){8.0, 6.0, 7.0, 5.0, 9.0}, 7.0, 5 },
    { (double[]){-2.2, -3.3, -4.4, -5.5}, -3.85, 4 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z46Change(TestCase t1) {
    TestCase follow_case = t1;

    // Defensive programming: no array length check needed for mean operation

    // Operation: set mean to 3.14159 if it is not already that value
    if (follow_case.mean != 3.14159) {
        follow_case.mean = 3.14159;
    }

    return follow_case;
}

int z46check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;

    if (std::isnan(A) || std::isnan(B)) return 0;

    if (std::isinf(A) || std::isinf(B)) {
        if (A < B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (A >= B - tol) return 0;

    return 1;
}

TestResult z46runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z46Change(test_cases[test_case_id]);
    // 原始调用
    double source = sampleVariance(test_cases[test_case_id].elements, test_cases[test_case_id].mean, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sampleVariance(follow_case.elements, follow_case.mean, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z46check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z46runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}