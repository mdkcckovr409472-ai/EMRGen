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


double cosineDistance(double p1[], double p2[], int n) {
    double dotProduct = 0.0;
    double lengthSquaredp1 = 0.0;
    double lengthSquaredp2 = 0.0;

    for (int i = 0; i < n; i++) {
        lengthSquaredp1 += p1[i] * p1[i];
        lengthSquaredp2 += p2[i] * p2[i];
        dotProduct += p1[i] * p2[i];
    }
    
    double denominator = sqrt(lengthSquaredp1) * sqrt(lengthSquaredp2);
    if (denominator < dotProduct) {
        denominator = dotProduct;
    }
    if (denominator == 0 && dotProduct == 0) {
        return 0;
    }
    return 1.0 - dotProduct / denominator;
}


typedef struct {
    double* p1; double* p2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){}, (double[]){}, 0},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){-1.0}, (double[]){1.0}, 1},
    {(double[]){1.0, 0.0}, (double[]){0.0, 1.0}, 2},
    {(double[]){2.0, 3.0}, (double[]){2.0, 3.0}, 2},
    {(double[]){1.0, 2.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){1.0, -2.0, 3.0}, (double[]){-1.0, 2.0, -3.0}, 3},
    {(double[]){0.5, -1.2, 3.3}, (double[]){2.1, 0.0, -0.7}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){1.0, 0.0, 1.0, 0.0}, (double[]){0.0, 1.0, 0.0, 1.0}, 4},
    {(double[]){-0.3, 2.5, -1.7, 4.2}, (double[]){3.1, -0.8, 0.0, -2.6}, 4},
    {(double[]){5.0, 5.0, 5.0, 5.0, 5.0}, (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5},
    {(double[]){-2.0, -4.0, -6.0, -8.0, -10.0}, (double[]){-2.0, -4.0, -6.0, -8.0, -10.0}, 5},
    {(double[]){3.0, -1.0, 4.0, -5.0, 2.0}, (double[]){-2.0, 6.0, -8.0, 10.0, -4.0}, 5},
    {(double[]){0.0, 1.0, 0.0, -1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0, 0.0, 1.0, 0.0}, 6},
    {(double[]){1.2, -3.4, 5.6, -7.8, 9.0, -0.1}, (double[]){-1.2, 3.4, -5.6, 7.8, -9.0, 0.1}, 6},
    {(double[]){2.5, 0.0, -2.5, 0.0, 2.5, 0.0}, (double[]){0.0, 2.5, 0.0, -2.5, 0.0, 2.5}, 6},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {(double[]){1.0, 1.0, 1.0}, (double[]){-1.0, -1.0, -1.0}, 3},
    {(double[]){0.3, 0.6, 0.9}, (double[]){0.3, 0.6, 0.9}, 3},
    {(double[]){-0.5, 2.0, -1.5}, (double[]){0.5, -2.0, 1.5}, 3},
    {(double[]){4.0, -4.0, 4.0, -4.0}, (double[]){-4.0, 4.0, -4.0, 4.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){-3.0, 0.0, 3.0}, (double[]){3.0, 0.0, -3.0}, 3},
    {(double[]){0.1, 0.2, 0.3, 0.4}, (double[]){0.4, 0.3, 0.2, 0.1}, 4},
    {(double[]){2.0, -2.0, 2.0, -2.0, 2.0}, (double[]){-2.0, 2.0, -2.0, 2.0, -2.0}, 5},
    {(double[]){0.0, 1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0, 0.0}, 4},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){1.5, -0.5, 2.5, -1.5}, (double[]){-1.5, 0.5, -2.5, 1.5}, 4},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3}
};
int num_test_cases = 31;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z37Change(TestCase t1) {
    TestCase follow_case = t1;
    // Memory handling for p2
    double* follow_case_p2 = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_p2, t1.p2, t1.n * sizeof(double));
    follow_case.p2 = follow_case_p2;
    // Defensive check for array length
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            follow_case.p2[i] *= 1.5;
        }
    }
    return follow_case;
}

int z37check(double result1, double result2) {
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

TestResult z37runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z37Change(test_cases[test_case_id]);
    // 原始调用
    double source = cosineDistance(test_cases[test_case_id].p1, test_cases[test_case_id].p2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = cosineDistance(follow_case.p1, follow_case.p2, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z37check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z37runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}