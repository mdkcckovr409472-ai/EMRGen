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


double max(double elements[], int n) {
    int size = n;
    double max = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] > max) {
            max = elements[i];
        }
    }
    return max;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){5.0}, 1},
    {(double[]){-3.2, 7.1}, 2},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){9.9, 0.0, -1.0}, 3},
    {(double[]){-5.5, -2.2, -3.3}, 3},
    {(double[]){4.0, 4.0, 4.0}, 3},
    {(double[]){2.1, 8.3, 5.5, 7.7}, 4},
    {(double[]){-1.0, 0.0, 1.0, -2.0, 2.0}, 5},
    {(double[]){3.14, 2.71, 1.41, 1.73}, 4},
    {(double[]){0.001, 0.002, 0.003, 0.004, 0.005}, 5},
    {(double[]){100.0, -100.0, 50.0, -50.0}, 4},
    {(double[]){-0.5, -0.2, -0.8, -0.1}, 4},
    {(double[]){7.5, 3.2, 7.5, 2.2}, 4},
    {(double[]){1e-3, 1e-2, 1e-1, 1.0}, 4},
    {(double[]){-10.0, 0.0, 10.0, 5.0}, 4},
    {(double[]){5.5, 6.6, 7.7, 8.8, 9.9}, 5},
    {(double[]){9.9, 8.8, 7.7, 6.6, 5.5}, 5},
    {(double[]){2.2, 3.3, 2.2, 3.3, 2.2}, 5},
    {(double[]){0.0, -0.0, 0.0}, 3},
    {(double[]){-3.3, 3.3, -3.3, 3.3}, 4},
    {(double[]){0.5, 0.5, 0.4, 0.6, 0.5}, 5},
    {(double[]){-1.1, -2.2, -3.3, -4.4, -0.5}, 5},
    {(double[]){100.5, 99.9, 101.0, 100.0}, 4},
    {(double[]){-50.0, 25.0, -25.0, 50.0}, 4},
    {(double[]){3.0, 1.0, 4.0, 1.5, 2.5}, 5},
    {(double[]){0.123, 0.456, 0.789, 0.101, 0.112}, 5},
    {(double[]){-0.001, -0.002, -0.003}, 3},
    {(double[]){5.0, 10.0, 5.0, 10.0, 5.0}, 5},
    {(double[]){2.718, 3.1415, 1.618, 2.0, 3.0}, 5},
    {(double[]){-9.9, 9.9, -8.8, 8.8, 0.0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z7Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------
    
    // Defensive check: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }
    
    // Set a random element to -DBL_MAX when it is greater than -DBL_MAX
    int random_index = rand() % follow_case.n;
    if (follow_case.elements[random_index] > -DBL_MAX) {
        follow_case.elements[random_index] = -DBL_MAX;
    }
    
    return follow_case;
}

int z7check(double result1, double result2) {
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

TestResult z7runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z7Change(test_cases[test_case_id]);
    // 原始调用
    double source = max(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = max(follow_case.elements, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z7check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z7runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}