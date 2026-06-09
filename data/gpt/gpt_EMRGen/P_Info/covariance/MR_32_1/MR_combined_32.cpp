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


double covariance(double elements1[], double elements2[], int n) {

    double sumx = elements1[0];
    double sumy = elements2[0];
    double Sxy = 0;
    
    for (int i = 1; i < n; ++i) {
        double x = elements1[i];
        double y = elements2[i];
        sumx += x;
        Sxy += (x - sumx / (i + 1)) * (y - sumy / i);
        sumy += y;
    }
    return Sxy / (n - 1);
}


typedef struct {
    double* elements1; double* elements2; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){5.0, 7.0}, (double[]){3.0, 4.0}, 2 },
    { (double[]){-2.5, 0.0, 1.5}, (double[]){4.0, -1.0, 2.0}, 3 },
    { (double[]){10.0, 10.0, 10.0, 10.0}, (double[]){5.0, 5.0, 5.0, 5.0}, 4 },
    { (double[]){-3.0, 2.0, -1.0, 4.0, 0.0}, (double[]){1.0, -2.0, 3.0, -4.0, 5.0}, 5 },
    { (double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2 },
    { (double[]){8.2, -3.1, 4.5, -6.7}, (double[]){-2.2, 7.3, -1.5, 3.1}, 4 },
    { (double[]){1.0, 2.0, 3.0}, (double[]){3.0, 2.0, 1.0}, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, (double[]){60.0, -50.0, 40.0, -30.0, 20.0, -10.0}, 6 },
    { (double[]){0.5, -0.5, 0.5, -0.5}, (double[]){-0.5, 0.5, -0.5, 0.5}, 4 },
    { (double[]){3.3, 3.3, 3.3}, (double[]){-1.1, -1.1, -1.1}, 3 },
    { (double[]){7.0, 2.0, 9.0, 4.0, 6.0}, (double[]){1.0, 5.0, 2.0, 8.0, 3.0}, 5 },
    { (double[]){-4.0, -2.0, -6.0}, (double[]){-1.0, -3.0, -5.0}, 3 },
    { (double[]){12.5, 0.0, -12.5}, (double[]){-12.5, 0.0, 12.5}, 3 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, (double[]){6.6, 5.5, 4.4, 3.3, 2.2, 1.1}, 6 },
    { (double[]){-0.1, 0.2, -0.3, 0.4, -0.5}, (double[]){0.5, -0.4, 0.3, -0.2, 0.1}, 5 },
    { (double[]){100.0, -100.0}, (double[]){-100.0, 100.0}, 2 },
    { (double[]){9.9, 8.8, 7.7, 6.6}, (double[]){6.6, 7.7, 8.8, 9.9}, 4 },
    { (double[]){0.0, 5.0, 10.0, 15.0, 20.0}, (double[]){20.0, 15.0, 10.0, 5.0, 0.0}, 5 },
    { (double[]){3.1415, 2.7182, 1.6180}, (double[]){1.4142, 0.5772, 0.6931}, 3 },
    { (double[]){-7.0, 14.0, -21.0, 28.0}, (double[]){28.0, -21.0, 14.0, -7.0}, 4 },
    { (double[]){0.25, 0.5, 0.75, 1.0}, (double[]){1.0, 0.75, 0.5, 0.25}, 4 },
    { (double[]){-5.5, 5.5, -5.5, 5.5}, (double[]){5.5, -5.5, 5.5, -5.5}, 4 },
    { (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, (double[]){1.0, 3.0, 5.0, 7.0, 9.0}, 5 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0}, (double[]){6.0, -5.0, 4.0, -3.0, 2.0, -1.0}, 6 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, (double[]){1.0, 0.0, 1.0, 0.0, 1.0}, 5 },
    { (double[]){-2.2, -2.2, -2.2, -2.2}, (double[]){3.3, 3.3, 3.3, 3.3}, 4 },
    { (double[]){5.5, -4.5, 3.5, -2.5, 1.5}, (double[]){-1.5, 2.5, -3.5, 4.5, -5.5}, 5 },
    { (double[]){0.0, -0.0, 0.0, -0.0}, (double[]){0.0, 0.0, 0.0, 0.0}, 4 }
};
int num_test_cases = 28;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z32Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_elements2 = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements2, t1.elements2, t1.n * sizeof(double));
    follow_case.elements2 = follow_case_elements2;
    // ------------------------------------
    
    // Defensive code generated based on rule (a) to prevent errors when n == 0
    if (follow_case.n > 0) {
        for (int i = 0; i < follow_case.n; ++i) {
            if (follow_case.elements2[i] != 0.0) {
                follow_case.elements2[i] /= 2.0;
            }
        }
    }
    
    return follow_case;
}

#include <math.h>
#include <stdbool.h>

int z32check(double result1, double result2) {
    // Core evaluation logic (direct scalar comparison)
    double epsilon = 1e-5;

    // Rearranged comparison: result1 == 2 * result2
    double A = result1;
    double B = 2 * result2;

    if (isnan(A) || isnan(B)) return 0;
    if (isinf(A) || isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double source = covariance(test_cases[test_case_id].elements1, test_cases[test_case_id].elements2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = covariance(follow_case.elements1, follow_case.elements2, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z32check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z32runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}