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


double sumOfPowerOfDeviations(double data[], int k, double c, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += pow(data[i] - c, k);
        }
    return sum;
}


typedef struct {
    double* data; int k; double c; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 2, 0.0, 3},
    {(double[]){}, 1, 5.0, 0},
    {(double[]){-1.5, 0.0, 2.5}, 1, 1.0, 3},
    {(double[]){3.0, -3.0, 3.0}, 3, 0.0, 3},
    {(double[]){0.5, -0.5, 0.5, -0.5}, 2, 0.0, 4},
    {(double[]){10.0, -10.0}, 1, 5.0, 2},
    {(double[]){2.0, 2.0, 2.0}, 0, 2.0, 3},
    {(double[]){-2.0, -4.0, -6.0}, 2, -3.0, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 1, 2.5, 4},
    {(double[]){5.0, 0.0, -5.0}, 4, 1.0, 3},
    {(double[]){0.0}, 5, 0.0, 1},
    {(double[]){-1.0, 1.0, -1.0, 1.0}, 3, 0.0, 4},
    {(double[]){3.5, -2.5, 0.0}, -1, 1.0, 3},
    {(double[]){7.0, 8.0, 9.0}, 2, 8.0, 3},
    {(double[]){-3.3, 3.3}, 1, -3.3, 2},
    {(double[]){0.1, 0.2, 0.3}, 2, 0.15, 3},
    {(double[]){4.0, -1.0, 2.0, -3.0}, 1, -0.5, 4},
    {(double[]){6.0, 6.0}, 0, 0.0, 2},
    {(double[]){-0.7, 0.7, -0.7}, 2, 0.0, 3},
    {(double[]){2.5, -2.5, 2.5, -2.5, 0.0}, 3, 1.0, 5},
    {(double[]){1.0, 2.0}, 10, 0.0, 2},
    {(double[]){-5.0, 5.0, -5.0, 5.0}, 2, 0.0, 4},
    {(double[]){3.14, -3.14}, 1, 0.0, 2},
    {(double[]){0.0, 0.0, 0.0}, 5, 0.0, 3},
    {(double[]){9.0, -9.0, 1.0}, 2, 5.0, 3},
    {(double[]){1.5, -1.5, 2.5, -2.5}, 1, 0.0, 4},
    {(double[]){-2.2, 3.3, -4.4, 5.5}, 3, -1.0, 4},
    {(double[]){0.25, -0.25, 0.75, -0.75}, 2, 0.5, 4},
    {(double[]){8.0}, 0, 8.0, 1},
    {(double[]){-1.0, 0.0, 1.0}, 1, 0.0, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z12Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
    follow_case.data = follow_case_data;
    // ------------------------------------
    
    // Defensive code: ensure there is at least one element to shift
    if (follow_case.n > 0) {
        double temp = follow_case.data[follow_case.n - 1];
        for (int i = follow_case.n - 1; i > 0; --i) {
            follow_case.data[i] = follow_case.data[i - 1];
        }
        follow_case.data[0] = temp;
    }
    
    return follow_case;
}

int z12check(double result1, double result2) {
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

TestResult z12runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z12Change(test_cases[test_case_id]);
    // 原始调用
    double source = sumOfPowerOfDeviations(test_cases[test_case_id].data, test_cases[test_case_id].k, test_cases[test_case_id].c, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sumOfPowerOfDeviations(follow_case.data, follow_case.k, follow_case.c, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z12check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z12runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}