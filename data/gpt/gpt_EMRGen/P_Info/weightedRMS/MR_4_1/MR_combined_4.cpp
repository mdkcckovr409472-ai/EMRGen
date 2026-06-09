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


double weightedRMS(double data[], double weights[], int n) {
    double sumOfProducts = 0;
    double sumOfSquaredProducts = 0;
    for(int i = 0; i < n; i++) {
        sumOfProducts += data[i] * weights[i];
        sumOfSquaredProducts += data[i] * data[i] * weights[i];
    }
    return sumOfProducts / sumOfSquaredProducts;
}


typedef struct {
    double* data; double* weights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){0.0, 5.0, -2.0}, (double[]){2.0, 0.5, 1.0}, 3},
    {(double[]){3.5}, (double[]){2.0}, 1},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){10.0, -10.0}, (double[]){0.1, 0.2}, 2},
    {(double[]){5.0, 0.0, 5.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.2, 3.3, 4.4, 5.5}, (double[]){1.1, 0.9, 1.0, 1.2}, 4},
    {(double[]){1.5, -1.5, 2.5, -2.5}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){9.9, 8.8, 7.7, 6.6}, (double[]){0.0, 1.0, 0.0, 1.0}, 4},
    {(double[]){-5.0, 5.0, -5.0}, (double[]){2.0, 2.0, 2.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4},
    {(double[]){0.0, 0.0, 1.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-0.5, 0.5}, (double[]){-1.0, 1.0}, 2},
    {(double[]){2.0, 2.0, 2.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.1415, 2.718, -1.618}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){100.0, -100.0, 50.0}, (double[]){0.01, 0.01, 0.02}, 3},
    {(double[]){0.001, 0.002, 0.003}, (double[]){1000.0, 1000.0, 1000.0}, 3},
    {(double[]){7.0, 8.0, 9.0}, (double[]){9.0, 8.0, 7.0}, 3},
    {(double[]){-3.0, 4.0, -5.0, 6.0}, (double[]){2.0, -2.0, 2.0, -2.0}, 4},
    {(double[]){1.0}, (double[]){0.5}, 1},
    {(double[]){-2.0, -4.0}, (double[]){0.5, 0.5}, 2},
    {(double[]){5.0, -5.0, 5.0, -5.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){0.0, 1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0, 0.0}, 4},
    {(double[]){9.0, -9.0, 9.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.5, 3.5, 4.5}, (double[]){-0.5, -0.5, -0.5}, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){2.0, 2.0, 2.0}, 3},
    {(double[]){6.0, 7.0}, (double[]){0.1, 0.2}, 2},
    {(double[]){0.25, 0.75}, (double[]){4.0, 4.0}, 2},
    {(double[]){-3.3, 3.3}, (double[]){1.5, 1.5}, 2}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z4Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
    follow_case.data = follow_case_data;
    // ------------------------------------
    
    // Defensive check: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }
    
    // Operation: divide each non‑zero element by 2.0
    for (int i = 0; i < follow_case.n; ++i) {
        if (follow_case.data[i] != 0.0) {
            follow_case.data[i] /= 2.0;
        }
    }
    
    return follow_case;
}

int z4check(double result1, double result2) {
    const double epsilon = 1e-5;
    double A = result1;
    double B = 0.5 * result2; // Rearranged from 2*result1 - result2 == 0 to result1 == result2/2 -> compare result1 and result2/2

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z4runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z4Change(test_cases[test_case_id]);
    // 原始调用
    double source = weightedRMS(test_cases[test_case_id].data, test_cases[test_case_id].weights, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = weightedRMS(follow_case.data, follow_case.weights, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z4check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z4runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}