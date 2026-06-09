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


double weightedMean(double elements[], double theWeights[], int n) {
    int size = n;
    double sum = 0.0;
    double weightsSum = 0.0;
    for(int i = size; --i >= 0; ) {
        double w = theWeights[i];
        sum += elements[i] * w;
        weightsSum += w;
    }
    return sum / weightsSum;
}


typedef struct {
    double* elements; double* theWeights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){5.5}, (double[]){2.0}, 1},
    {(double[]){-2.0, 4.0, -6.0}, (double[]){1.0, 0.5, 2.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){0.5, 1.5, 2.5}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){3.0, -1.0, 4.0, 0.0, 2.0}, (double[]){2.0, 1.0, 3.0, 0.5, 1.5}, 5},
    {(double[]){7.0, 7.0, 7.0, 7.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){8.0, 2.0}, (double[]){0.75, 0.25}, 2},
    {(double[]){1.0, 2.0}, (double[]){-1.0, 2.0}, 2},
    {(double[]){0.001, 0.002}, (double[]){0.0001, 0.0002}, 2},
    {(double[]){0.0, -5.0, 10.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){4.0, 4.0, 4.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){9.0, -3.0, 5.0, 2.0}, (double[]){2.0, 1.0, 3.0, 4.0}, 4},
    {(double[]){1.2, 3.4, 5.6}, (double[]){0.1, 0.2, 0.7}, 3},
    {(double[]){-9.0, 8.0, -7.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.0, 5.0, 8.0, 11.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){100.0, 200.0}, (double[]){0.0, 1.0}, 2},
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.1, 0.2, 0.2}, 3},
    {(double[]){1.0, 2.0, 1.0, 2.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){0.123456, 0.654321, 0.111111}, (double[]){0.333333, 0.333333, 0.333334}, 3},
    {(double[]){5.0, -5.0, 5.0, -5.0, 5.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){10.0, 20.0, 30.0}, (double[]){-1.0, -2.0, 1.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){0.0, 0.0, 0.0, 5.0}, 4},
    {(double[]){0.0, 0.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){3.0, 6.0, 9.0}, (double[]){0.2, 0.3, 0.5}, 3},
    {(double[]){-2.5, 3.5, -1.5, 4.5, 0.0}, (double[]){1.5, 0.5, 2.0, 1.0, 0.0}, 5},
    {(double[]){7.0, -2.0, 5.0, 1.0}, (double[]){3.0, 0.5, 2.0, 1.5}, 4},
    {(double[]){0.0, 5.0, 10.0}, (double[]){0.0, 1.0, 1.0}, 3},
    {(double[]){-3.0, 3.0}, (double[]){2.0, 2.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){-0.5, 0.5, -0.5, 0.5, 1.0}, 5}
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
    // --- Memory handling code ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ---------------------------

    // Defensive check: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }

    // Operation: multiply all elements by 2.0
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.elements[i] *= 2.0;
    }

    return follow_case;
}

#include <math.h>
#include <stddef.h>
int z3check(double result1, double result2) {
    double epsilon = 1e-5;

    // Rearranged equation: 2 * result1 == result2
    double A = 2.0 * result1;
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

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double source = weightedMean(test_cases[test_case_id].elements, test_cases[test_case_id].theWeights, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = weightedMean(follow_case.elements, follow_case.theWeights, follow_case.n);
    
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