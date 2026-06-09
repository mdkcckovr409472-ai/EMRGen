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


double evaluateInternal(double x[], double y[], double z, int n) {
    int nearest = 0;
    double c[1000];
    double d[1000];
    double min_dist = INFINITY;
    for (int i = 0; i < n; i++) {
        c[i] = y[i];
        d[i] = y[i];
        double dist = abs(z - x[i]);
        if (dist < min_dist) {
            nearest = i;
            min_dist = dist;
        }
    }
    double value = y[nearest];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            double tc = x[j] - z;
            double td = x[i + j] - z;
            double divider = x[j] - x[i + j];
            double w = (c[j + 1] - d[j]) / divider;
            c[j] = tc * w;
            d[j] = td * w;
        }
        if (nearest < 0.5 * (n - i + 1)) {
            value += c[nearest];
        } else {
            nearest--;
            value += d[nearest];
        }
    }
    return value;
}


typedef struct {
    double* x; double* y; double z; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){10.0, 20.0, 30.0}, 2.5, 3},
    {(double[]){5.0, -1.0, 3.5, 0.0}, (double[]){0.0, 1.0, -1.0, 2.0}, -0.5, 4},
    {(double[]){0.0, 10.0}, (double[]){5.0, 15.0}, 7.0, 2},
    {(double[]){-3.2, 4.1, 2.5, -1.0, 8.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0.0, 5},
    {(double[]){100.0, -50.0, 25.0}, (double[]){-10.0, 20.0, -30.0}, 60.0, 3},
    {(double[]){0.5, -0.5, 1.5, -1.5, 2.5, -2.5}, (double[]){10.0, 9.0, 8.0, 7.0, 6.0, 5.0}, 0.0, 6},
    {(double[]){3.14}, (double[]){2.71}, 3.0, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){4.4, 3.3, 2.2, 1.1}, 2.0, 4},
    {(double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0}, -3.0, 5},
    {(double[]){0.01, 0.02, 0.03}, (double[]){1000.0, -1000.0, 500.0}, 0.025, 3},
    {(double[]){-100.0, 100.0}, (double[]){0.5, -0.5}, 0.0, 2},
    {(double[]){7.0, 3.0, -2.0, 9.0}, (double[]){-7.0, 3.0, 2.0, -9.0}, 5.0, 4},
    {(double[]){2.0, 8.0, 5.0, 1.0, 7.0}, (double[]){1.5, -1.5, 2.5, -2.5, 0.0}, 6.0, 5},
    {(double[]){-0.5, 0.5, 1.5}, (double[]){0.0, 0.0, 0.0}, 0.0, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0, 60.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 35.0, 6},
    {(double[]){-3.0, -1.0, 2.0, 4.0}, (double[]){4.0, -2.0, 0.0, 1.0}, -2.0, 4},
    {(double[]){0.0, 1.0, 4.0, 9.0, 16.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 3.0, 5},
    {(double[]){0.5, 0.5001}, (double[]){1.0, 2.0}, 0.5, 2},
    {(double[]){-100.0, 0.0, 100.0}, (double[]){10.0, 0.0, -10.0}, 50.0, 3},
    {(double[]){0.2, -0.2, 0.4, -0.4}, (double[]){2.0, -2.0, 2.5, -2.5}, 0.0, 4},
    {(double[]){3.14, 2.71, 1.62, 0.58, -0.5}, (double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 1.0, 5},
    {(double[]){9.0, 3.0, 6.0}, (double[]){0.0, 1.0, 2.0}, 4.5, 3},
    {(double[]){-5.0, -3.0, -1.0, 1.0, 3.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0, 0.0}, 0.0, 6},
    {(double[]){1.5, 2.5, 3.5, 4.5}, (double[]){10.0, 20.0, 30.0, 40.0}, 2.0, 4},
    {(double[]){-0.1, 0.1}, (double[]){0.5, -0.5}, 0.0, 2},
    {(double[]){5.0, -5.0, 10.0, -10.0, 15.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, -7.0, 5},
    {(double[]){0.001, 0.002, 0.003}, (double[]){100.0, 200.0, 300.0}, 0.0025, 3},
    {(double[]){-2.0, 2.0, -1.0, 1.0}, (double[]){-10.0, 10.0, -20.0, 20.0}, 0.0, 4},
    {(double[]){-0.75, 0.25, 1.25, 2.25, 3.25}, (double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 1.0, 5},
    {(double[]){8.0, 3.0, -2.0}, (double[]){-3.0, 0.0, 3.0}, 5.0, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z31Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_y = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_y, t1.y, t1.n * sizeof(double));
    follow_case.y = follow_case_y;
    // ------------------------------------
    
    // Defensive code: ensure there is at least one element
    if (follow_case.n <= 0) {
        return follow_case;
    }
    
    // Subtract 1.0 from each element of y
    for (int i = 0; i < follow_case.n; ++i) {
        follow_case.y[i] -= 1.0;
    }
    
    return follow_case;
}

int z31check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2 + 1.0; // rearranged from result1 - result2 - 1 == 0 to result1 == result2 + 1

    if (std::isnan(A) || std::isnan(B)) return 0;

    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (fabs(A - B) > tol) {
        return 0;
    }

    return 1;
}

TestResult z31runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z31Change(test_cases[test_case_id]);
    // 原始调用
    double source = evaluateInternal(test_cases[test_case_id].x, test_cases[test_case_id].y, test_cases[test_case_id].z, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = evaluateInternal(follow_case.x, follow_case.y, follow_case.z, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z31check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z31runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}