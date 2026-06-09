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


double evaluateHoners(double coefficients[], double argument, int n) {
    
    double result = coefficients[n - 1];
    for (int j = n - 2; j >= 0; j--) {
        result = argument * result + coefficients[j];
    }
    return result;
}


typedef struct {
    double* coefficients; double argument; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, 1.0, 3 },
    { (double[]){0.0}, 5.0, 1 },
    { (double[]){-1.0, 4.5, -3.2}, -2.0, 3 },
    { (double[]){2.5, -2.5, 0.0, 1.0}, 0.0, 4 },
    { (double[]){3.14, 2.71}, 3.0, 2 },
    { (double[]){-5.0, -5.0, -5.0}, 1.5, 3 },
    { (double[]){10.0, -10.0, 10.0, -10.0}, -1.0, 4 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 0.5, 5 },
    { (double[]){-0.5, 0.5, -0.5, 0.5}, 2.0, 4 },
    { (double[]){100.0, -100.0}, 0.01, 2 },
    { (double[]){0.001, -0.001, 0.001}, -0.001, 3 },
    { (double[]){7.0, 0.0, -7.0}, 1.0, 3 },
    { (double[]){5.5, 5.5}, -2.5, 2 },
    { (double[]){-2.2, 3.3, -4.4, 5.5}, 1.1, 4 },
    { (double[]){0.0, 0.0, 0.0}, 10.0, 3 },
    { (double[]){9.9}, -9.9, 1 },
    { (double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 0.9, 5 },
    { (double[]){-3.3, 2.2}, 3.3, 2 },
    { (double[]){4.4, -4.4, 4.4}, -4.4, 3 },
    { (double[]){0.123, -0.456, 0.789}, 0.321, 3 },
    { (double[]){-0.001, 0.0, 0.001}, 1000.0, 3 },
    { (double[]){8.0, 6.0, 4.0, 2.0}, -0.5, 4 },
    { (double[]){-9.0, -8.0, -7.0}, -1.0, 3 },
    { (double[]){3.0, 1.0, 4.0, 1.5, 2.5}, 2.0, 5 },
    { (double[]){0.0, 1.0, 0.0, -1.0}, 0.0, 4 },
    { (double[]){2.0, -3.0, 5.0}, 1.0, 3 },
    { (double[]){-1.5, 2.5, -3.5, 4.5}, -2.0, 4 },
    { (double[]){0.25, 0.75}, 4.0, 2 },
    { (double[]){-0.75, 0.25, -0.125}, 0.5, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, -1.0, 6 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling: deep copy of coefficients array
    double* follow_case_coefficients = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_coefficients, t1.coefficients, t1.n * sizeof(double));
    follow_case.coefficients = follow_case_coefficients;

    // Defensive check: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }

    // Operation: multiply each element by 2.0
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.coefficients[i] *= 2.0;
    }

    return follow_case;
}

#include <cmath>

int z3check(double result1, double result2) {
    double epsilon = 1e-5;

    // Rearrange invariant_condition: 2 * result1 - result2 == 0
    // Rearranged to: 2 * result1 == result2
    double A = 2.0 * result1;
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

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double source = evaluateHoners(test_cases[test_case_id].coefficients, test_cases[test_case_id].argument, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = evaluateHoners(follow_case.coefficients, follow_case.argument, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}