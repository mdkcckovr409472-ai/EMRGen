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


double min(double elements[], int n) {
    int size = n;
    double min = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] < min) {
            min = elements[i];
        }
    }
    return min;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){5.0}, 1},
    {(double[]){-1.0, 2.0}, 2},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){3.2, 1.5, 4.8, 2.2}, 4},
    {(double[]){-5.5, -3.3, -9.9, -1.1}, 4},
    {(double[]){10.0, -10.0, 5.0, -5.0}, 4},
    {(double[]){2.2, 2.2, 2.2}, 3},
    {(double[]){7.7, 3.3, 5.5, 1.1, 9.9}, 5},
    {(double[]){-0.5, 0.5, -0.5, 0.5}, 4},
    {(double[]){100.0, 50.0, 75.0, 25.0, 0.0}, 5},
    {(double[]){-100.0, -50.0, -75.0, -25.0, -1.0}, 5},
    {(double[]){3.1415, 2.7182, 1.618, 0.5772}, 4},
    {(double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5, 4.4}, 6},
    {(double[]){-1.1, -2.2, -3.3, -4.4, -5.5}, 5},
    {(double[]){0.001, 0.0001, 0.01, 0.1}, 4},
    {(double[]){-0.001, -0.0001, -0.01, -0.1}, 4},
    {(double[]){5.5, 3.3, 5.5, 3.3, 1.1}, 5},
    {(double[]){1.0, -1.0, 1.0, -1.0, 1.0, -1.0}, 6},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 4.0, 2.0}, 7},
    {(double[]){2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0}, 7},
    {(double[]){-3.0, 0.0, 3.0, -6.0, 9.0}, 5},
    {(double[]){1.5, 2.5, 3.5, 4.5, 0.5}, 5},
    {(double[]){-2.5, -1.5, -0.5, 0.5, 1.5}, 5},
    {(double[]){0.0, -0.0, 0.0, -0.0}, 4},
    {(double[]){-9.9, 9.9, -8.8, 8.8, -7.7, 7.7}, 6},
    {(double[]){3.0, 1.0, 4.0, 1.5, 5.0, 9.0, 2.6}, 7},
    {(double[]){-1.2, 3.4, -5.6, 7.8, -9.0, 11.2}, 6},
    {(double[]){0.123, 0.456, 0.789, 0.012}, 4},
    {(double[]){-0.123, -0.456, -0.789, -0.012}, 4}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z13Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling: deep copy of the array
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;

    // Defensive check: ensure there is at least one element to sort
    if (follow_case.n > 0) {
        // Sort the array in descending order
        for (int i = 0; i < follow_case.n - 1; ++i) {
            for (int j = 0; j < follow_case.n - i - 1; ++j) {
                if (follow_case.elements[j] < follow_case.elements[j + 1]) {
                    double temp = follow_case.elements[j];
                    follow_case.elements[j] = follow_case.elements[j + 1];
                    follow_case.elements[j + 1] = temp;
                }
            }
        }
    }

    return follow_case;
}

int z13check(double result1, double result2) {
    const double epsilon = 1e-5;
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

TestResult z13runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z13Change(test_cases[test_case_id]);
    // 原始调用
    double source = min(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = min(follow_case.elements, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z13check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z13runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}