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


double evaluateNewton(double a[], double c[], double z, int nc) {
    int n = nc - 1;
    double value = a[n];
    for (int i = n - 1; i >= 0; i--) {
        value = a[i] + (z - c[i]) * value;
    }
    return value;
}


typedef struct {
    double* a; double* c; double z; int nc;
} TestCase;

TestCase test_cases[] = {
    {(double[]){5.0}, (double[]){2.0}, 3.0, 1},
    {(double[]){1.0, 2.0}, (double[]){0.0, 1.0}, 0.5, 2},
    {(double[]){-3.0, 4.0}, (double[]){1.0, -1.0}, -2.0, 2},
    {(double[]){0.0, 1.0, -1.0}, (double[]){3.0, -2.0, 4.0}, 2.0, 3},
    {(double[]){2.0, -2.0, 2.0}, (double[]){-1.0, 0.0, 1.0}, 1.5, 3},
    {(double[]){-0.5, 1.5, -2.5}, (double[]){2.5, -3.5, 0.5}, 0.0, 3},
    {(double[]){2.5, -1.5, 3.0, 0.0}, (double[]){-1.0, 2.0, 0.5, -3.0}, -0.5, 4},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 10.0, 4},
    {(double[]){1.0, -1.0, 1.0, -1.0}, (double[]){-2.0, -1.0, 0.0, 1.0}, 2.0, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 0.0, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 6.0, 5},
    {(double[]){-1.0, 2.0, -3.0, 4.0, -5.0}, (double[]){0.0, -1.0, 1.0, -2.0, 2.0}, -1.0, 5},
    {(double[]){1.1, -2.2, 3.3, -4.4, 5.5, -6.6}, (double[]){6.6, -5.5, 4.4, -3.3, 2.2, -1.1}, 0.5, 6},
    {(double[]){0.0, 1.0, 0.0, 1.0, 0.0, 1.0}, (double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0}, 3.0, 6},
    {(double[]){10.0, -10.0}, (double[]){5.0, -5.0}, 5.0, 2},
    {(double[]){3.3, 2.2, 1.1}, (double[]){-1.1, -2.2, -3.3}, -2.0, 3},
    {(double[]){-2.0, 0.0, 2.0, -4.0}, (double[]){4.0, 2.0, 0.0, -2.0}, 1.0, 4},
    {(double[]){0.5, -0.5, 0.5, -0.5, 0.5}, (double[]){-0.5, 0.5, -0.5, 0.5, -0.5}, 0.0, 5},
    {(double[]){100.0, -50.0, 25.0}, (double[]){10.0, -10.0, 5.0}, 2.0, 3},
    {(double[]){-10.0, 5.0, -2.5, 1.25}, (double[]){1.0, -1.0, 2.0, -2.0}, -1.0, 4},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 123.456, 2},
    {(double[]){1.0, 0.0, -1.0}, (double[]){-1.0, 0.0, 1.0}, 0.0, 3},
    {(double[]){2.0, 2.0, 2.0, 2.0}, (double[]){-2.0, -1.0, 0.0, 1.0}, 2.0, 4},
    {(double[]){-3.3, 3.3, -3.3, 3.3, -3.3}, (double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 1.0, 5},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){6.0,5.0,4.0,3.0,2.0,1.0}, -1.0, 6},
    {(double[]){-0.1, 0.2, -0.3}, (double[]){0.3, -0.2, 0.1}, 0.0, 3},
    {(double[]){0.0, 1.0, -1.0, 0.0}, (double[]){1.0, -1.0, 1.0, -1.0}, 0.5, 4},
    {(double[]){9.9, -9.9, 9.9, -9.9, 9.9}, (double[]){-9.9, 9.9, -9.9, 9.9, -9.9}, 0.0, 5},
    {(double[]){3.14, 2.71}, (double[]){1.61, 0.0}, 1.0, 2},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){5.0, 0.0, -5.0}, 2.5, 3}
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
    // Memory handling for deep copy of array a
    double* follow_case_a = (double*)malloc(t1.nc * sizeof(double));
    memcpy(follow_case_a, t1.a, t1.nc * sizeof(double));
    follow_case.a = follow_case_a;
    // Defensive check: ensure there is at least one element
    if (follow_case.nc == 0) {
        return follow_case;
    }
    // Operation: divide all elements by 2.0
    for (int i = 0; i < follow_case.nc; ++i) {
        follow_case.a[i] /= 2.0;
    }
    return follow_case;
}

int z4check(double result1, double result2) {
    const double epsilon = 1e-5;
    // Rearrange return.result1 - 2 * return.result2 == 0 as result1 == 2 * result2
    double A = result1;
    double B = 2 * result2;

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
    double source = evaluateNewton(test_cases[test_case_id].a, test_cases[test_case_id].c, test_cases[test_case_id].z, test_cases[test_case_id].nc); // MODIFIED: Explicit type
    // 变换后调用
    double follow = evaluateNewton(follow_case.a, follow_case.c, follow_case.z, follow_case.nc);
    
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