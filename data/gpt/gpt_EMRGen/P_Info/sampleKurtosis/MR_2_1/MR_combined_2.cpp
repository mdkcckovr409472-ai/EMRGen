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


double sampleKurtosis(double moment4, double sampleVariance,int size) {
    int n = size;
    double s2 = sampleVariance;
    double m4 = moment4 * n;
    return m4 * n * (n + 1) / ((n - 1) * (n - 2) * (n - 3) * s2 * s2) - 3.0 * (n - 1) * (n - 1) / ((n - 2) * (n - 3));
}


typedef struct {
    double moment4; double sampleVariance; int size;
} TestCase;

TestCase test_cases[] = {
    {1.0, 2.0, 5},
    {0.0, 1.0, 4},
    {-1.5, 0.5, 6},
    {2.5, 3.0, 8},
    {10.0, 5.0, 10},
    {0.1, 0.2, 7},
    {3.1415, 1.618, 9},
    {-2.0, 4.0, 12},
    {5.5, 2.5, 15},
    {0.0001, 0.0002, 4},
    {-0.75, 0.25, 11},
    {7.2, 3.3, 13},
    {1.23, 4.56, 14},
    {-3.33, 2.22, 16},
    {9.99, 0.99, 18},
    {0.5, 0.5, 20},
    {-0.1, 0.9, 22},
    {4.0, 1.0, 24},
    {2.718, 2.718, 26},
    {-5.5, 5.5, 28},
    {6.0, 0.1, 30},
    {0.333, 0.666, 32},
    {-1.0, 1.0, 34},
    {8.8, 2.2, 36},
    {0.125, 0.875, 38},
    {-2.5, 3.5, 40},
    {3.0, 0.75, 42},
    {1.0, 1.0, 44},
    {-0.5, 2.0, 46},
    {5.0, 0.2, 48}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z2Change(TestCase t1) {
    TestCase follow_case = t1;
    // Operation: subtract 1.0 from moment4
    follow_case.moment4 -= 1.0;
    return follow_case;
}

int z2check(double result1, double result2) {
    double epsilon = 1e-5;
    double A = result1;
    double B = result2;

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A > B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    if (A <= B + tol) return 0;

    return 1;
}

TestResult z2runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z2Change(test_cases[test_case_id]);
    // 原始调用
    double source = sampleKurtosis(test_cases[test_case_id].moment4, test_cases[test_case_id].sampleVariance, test_cases[test_case_id].size); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sampleKurtosis(follow_case.moment4, follow_case.sampleVariance, follow_case.size);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z2check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z2runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}