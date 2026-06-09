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


double product(double elements[], int n) {
    int size = n;
    double product = 1;
    for (int i = size; --i >= 0; ) {
        product *= elements[i];
    }
    return product;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){1.0}, 1 },
    { (double[]){0.0}, 1 },
    { (double[]){-1.0}, 1 },
    { (double[]){2.0, 3.0}, 2 },
    { (double[]){5.0, 0.0}, 2 },
    { (double[]){-2.0, -3.0}, 2 },
    { (double[]){1.5, -2.0, 4.0}, 3 },
    { (double[]){0.0, 1.2, -3.3}, 3 },
    { (double[]){3.0, 1.0, 4.0, 2.0}, 4 },
    { (double[]){-1.0, 2.0, -3.0, 4.0}, 4 },
    { (double[]){-0.5, 2.5, 0.0, -1.5, 3.0}, 5 },
    { (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5 },
    { (double[]){2.2, -2.2, 3.3, -3.3, 0.1, -0.1}, 6 },
    { (double[]){10.0, 0.5, -0.5, 2.0, -2.0, 1.0}, 6 },
    { (double[]){-2.0, -2.0, -2.0}, 3 },
    { (double[]){0.25, 4.0}, 2 },
    { (double[]){0.5, 0.2, 5.0, 2.0}, 4 },
    { (double[]){0.0, 0.0, 1.0, -1.0, 2.0}, 5 },
    { (double[]){1e-3}, 1 },
    { (double[]){1e-3, 1e3}, 2 },
    { (double[]){9.0, -9.0, 1.0}, 3 },
    { (double[]){-1.0, 1.0, -1.0, 1.0}, 4 },
    { (double[]){3.1415, -2.718, 0.577, -1.618, 2.0}, 5 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, 6 },
    { (double[]){-5.0, 0.0, -2.0}, 3 },
    { (double[]){-0.75, 1.25, -1.25, 0.75}, 4 },
    { (double[]){0.1, -10.0, 5.0, -0.2, 2.0}, 5 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0, 2.0}, 6 },
    { (double[]){1.0, -1.0, 1.0}, 3 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z15Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling: deep copy of the array
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;

    // Defensive check: ensure there is at least one element to sort
    if (follow_case.n == 0) {
        return follow_case;
    }

    // Sort the array in ascending order (bubble sort)
    for (int i = 0; i < follow_case.n - 1; ++i) {
        for (int j = 0; j < follow_case.n - i - 1; ++j) {
            if (follow_case.elements[j] > follow_case.elements[j + 1]) {
                double temp = follow_case.elements[j];
                follow_case.elements[j] = follow_case.elements[j + 1];
                follow_case.elements[j + 1] = temp;
            }
        }
    }

    return follow_case;
}

int z15check(double result1, double result2) {
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

TestResult z15runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z15Change(test_cases[test_case_id]);
    // 原始调用
    double source = product(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = product(follow_case.elements, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z15check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z15runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}