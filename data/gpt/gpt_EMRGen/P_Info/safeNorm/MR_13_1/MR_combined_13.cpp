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


double safeNorm(double v[], int n) {
    double rdwarf = 3.834e-20;
    double rgiant = 1.304e+19;
    double s1 = 0;
    double s2 = 0;
    double s3 = 0;
    double x1max = 0;
    double x3max = 0;
    double floatn = n;
    double agiant = rgiant / floatn;
    
    for (int i = 0; i < n; i++) {
        double xabs = abs(v[i]);
        if (xabs < rdwarf || xabs > agiant) {
            if (xabs > rdwarf) {
                if (xabs > x1max) {
                    double r = x1max / xabs;
                    s1 = 1 + s1 * r * r;
                    x1max = xabs;
                } else {
                    double r = xabs / x1max;
                    s1 += r * r;
                }
            } else {
                if (xabs > x3max) {
                    double r = x3max / xabs;
                    s3 = 1 + s3 * r * r;
                    x3max = xabs;
                } else {
                    if (xabs != 0) {
                        double r = xabs / x3max;
                        s3 += r * r;
                    }
                }
            }
        } else {
            s2 += xabs * xabs;
        }
    }
    double norm;
    if (s1 != 0) {
        norm = x1max * sqrt(s1 + s2 / x1max / x1max);
    } else {
        if (s2 == 0) {
            norm = x3max * sqrt(s3);
        } else {
            if (s2 >= x3max) {
                norm = sqrt(s2 * (1 + x3max / s2 * (x3max * s3)));
            } else {
                norm = sqrt(x3max * (s2 / x3max + x3max * s3));
            }
        }
    }
    return norm;
}


typedef struct {
    double* v; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){0.0}, 1 },
    { (double[]){}, 0 },
    { (double[]){-3.5, 2.1, 0.0, 4.8}, 4 },
    { (double[]){1e-10, -2e-10, 3e-10}, 3 },
    { (double[]){5.0, -5.0, 5.0, -5.0, 5.0}, 5 },
    { (double[]){123.456, -987.654}, 2 },
    { (double[]){0.001, 0.002, 0.003, 0.004}, 4 },
    { (double[]){-0.1, 0.2, -0.3, 0.4, -0.5}, 5 },
    { (double[]){7.89, 0.0, -7.89}, 3 },
    { (double[]){1000.0, -1000.0, 500.0}, 3 },
    { (double[]){0.000001, 0.000002, 0.000003}, 3 },
    { (double[]){-250.0, 250.0, -125.0, 125.0}, 4 },
    { (double[]){3.14, 2.71, 1.62, 0.577, 1.414}, 5 },
    { (double[]){-0.0005, 0.0005}, 2 },
    { (double[]){42.0}, 1 },
    { (double[]){-42.0, 42.0}, 2 },
    { (double[]){0.9, 1.1, 0.95, 1.05}, 4 },
    { (double[]){-9999.9, 9999.9, -0.01, 0.01}, 4 },
    { (double[]){0.123, -0.456, 0.789}, 3 },
    { (double[]){-1e5, 1e5, 0.0}, 3 },
    { (double[]){0.333, 0.666, 0.999}, 3 },
    { (double[]){-3.3, 3.3, -6.6, 6.6}, 4 },
    { (double[]){0.05, -0.05, 0.15, -0.15, 0.25}, 5 },
    { (double[]){500.5, -500.5, 250.25}, 3 },
    { (double[]){-0.000001, 0.000002, -0.000003, 0.000004}, 4 },
    { (double[]){2.71828, -2.71828, 3.14159}, 3 },
    { (double[]){-0.777, 0.777, -0.888, 0.888}, 4 },
    { (double[]){12345.6, -12345.6, 0.0, 1.0}, 4 },
    { (double[]){0.0001, 0.0002, 0.0003, 0.0004, 0.0005}, 5 },
    { (double[]){-50.0, 0.0, 50.0, -25.0, 25.0}, 5 }
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
    // --- Memory handling code generated based on the rule ---
    double* follow_case_v = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_v, t1.v, t1.n * sizeof(double));
    follow_case.v = follow_case_v;
    // ------------------------------------
    
    // Defensive code to ensure there are at least 2 elements
    if (follow_case.n < 2) {
        return follow_case;
    }
    
    // Operation: reverse subarray between two random indices i < j
    int i = rand() % follow_case.n;
    int j = rand() % follow_case.n;
    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }
    // Now i <= j, if i == j nothing changes, which is safe
    int left = i;
    int right = j;
    while (left < right) {
        double temp = follow_case.v[left];
        follow_case.v[left] = follow_case.v[right];
        follow_case.v[right] = temp;
        ++left;
        --right;
    }
    
    return follow_case;
}

#include <cmath>

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
    double source = safeNorm(test_cases[test_case_id].v, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = safeNorm(follow_case.v, follow_case.n);
    
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