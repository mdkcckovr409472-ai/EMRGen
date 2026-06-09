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


double pooledVariance(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    double sumSq1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
        sumSq1 += data1[i] * data1[i];
    }
    double mean1 = sum1 / n1;
    double var1 = (sumSq1 - mean1 * sum1) / n1;
    double sum2 = 0;
    double sumSq2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
        sumSq2 += data2[i] * data2[i];
    }
    double mean2 = sum2 / n2;
    double var2 = (sumSq2 - mean2 * sum2) / n2;
    return (n1 * var1 + n2 * var2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0}, (double[]){3.0, 4.0}, 2, 2 },
    { (double[]){5.5}, (double[]){-2.2}, 1, 1 },
    { (double[]){-1.0, 4.5, -3.2}, (double[]){2.2, -5.0, 0.0}, 3, 3 },
    { (double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2 },
    { (double[]){7.1, -6.3}, (double[]){-1.5, 8.8}, 2, 2 },
    { (double[]){3.3, 3.3, 3.3}, (double[]){-2.2, -2.2, -2.2}, 3, 3 },
    { (double[]){9.9, -9.9, 0.1, -0.1}, (double[]){5.5, -5.5, 2.2, -2.2}, 4, 4 },
    { (double[]){1.2, -3.4, 5.6}, (double[]){-7.8, 9.0, -0.2}, 3, 3 },
    { (double[]){4.0}, (double[]){4.0, 4.0}, 1, 2 },
    { (double[]){-4.0, 4.0}, (double[]){2.5}, 2, 1 },
    { (double[]){2.5, -2.5, 2.5, -2.5}, (double[]){1.0, -1.0, 1.0, -1.0}, 4, 4 },
    { (double[]){6.6, 7.7}, (double[]){-8.8, -9.9}, 2, 2 },
    { (double[]){0.5, -0.5, 0.5}, (double[]){-0.5, 0.5, -0.5}, 3, 3 },
    { (double[]){3.14, 2.71}, (double[]){1.41, 1.73}, 2, 2 },
    { (double[]){-3.0, 0.0, 3.0}, (double[]){-1.0, 1.0, -1.0}, 3, 3 },
    { (double[]){5.0, -5.0, 5.0, -5.0, 5.0}, (double[]){-5.0, 5.0, -5.0, 5.0, -5.0}, 5, 5 },
    { (double[]){2.0, 8.0}, (double[]){4.0, 6.0}, 2, 2 },
    { (double[]){-2.0, -8.0}, (double[]){-4.0, -6.0}, 2, 2 },
    { (double[]){1.0, 3.0, 5.0}, (double[]){2.0, 4.0, 6.0}, 3, 3 },
    { (double[]){6.0, 4.0, 2.0}, (double[]){5.0, 3.0, 1.0}, 3, 3 },
    { (double[]){-1.1, 2.2, -3.3, 4.4}, (double[]){-4.4, 3.3, -2.2, 1.1}, 4, 4 },
    { (double[]){7.0}, (double[]){-7.0, 7.0, -7.0}, 1, 3 },
    { (double[]){-7.0, 7.0, -7.0}, (double[]){7.0}, 3, 1 },
    { (double[]){0.123, -0.456, 0.789}, (double[]){-0.321, 0.654, -0.987}, 3, 3 },
    { (double[]){9.0, 1.0, 4.0}, (double[]){2.0, 8.0, 5.0}, 3, 3 },
    { (double[]){-9.0, -1.0, -4.0}, (double[]){-2.0, -8.0, -5.0}, 3, 3 },
    { (double[]){3.0, -3.0, 3.0, -3.0, 3.0, -3.0}, (double[]){-3.0, 3.0, -3.0, 3.0, -3.0, 3.0}, 6, 6 },
    { (double[]){0.0, 1.0, -1.0, 2.0, -2.0}, (double[]){3.0, -3.0, 4.0, -4.0, 5.0}, 5, 5 }
};
int num_test_cases = 28;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z14Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code ---
    double* follow_case_data1 = (double*)malloc(t1.n1 * sizeof(double));
    memcpy(follow_case_data1, t1.data1, t1.n1 * sizeof(double));
    follow_case.data1 = follow_case_data1;
    // --------------------------------

    // Defensive check: ensure there is at least one element to shift
    if (follow_case.n1 == 0) {
        return follow_case;
    }

    // Right circular shift: move last element to front
    double temp = follow_case.data1[follow_case.n1 - 1];
    for (int i = follow_case.n1 - 1; i > 0; --i) {
        follow_case.data1[i] = follow_case.data1[i - 1];
    }
    follow_case.data1[0] = temp;

    return follow_case;
}

int z14check(double result1, double result2) {
    const double epsilon = 1e-5;
    double A = result1;
    double B = result2;

    #include <cmath>

    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        if (A == B) return 1;
        else return 0;
    }

    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    if (fabs(A - B) > tol) return 0;

    return 1;
}

TestResult z14runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z14Change(test_cases[test_case_id]);
    // 原始调用
    double source = pooledVariance(test_cases[test_case_id].data1, test_cases[test_case_id].data2, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double follow = pooledVariance(follow_case.data1, follow_case.data2, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data1;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z14check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z14runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}