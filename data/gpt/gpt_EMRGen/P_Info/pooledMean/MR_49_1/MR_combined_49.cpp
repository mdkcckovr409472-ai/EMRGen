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


double pooledMean(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
    }
    double mean1 = sum1 / n1;
    double sum2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
    }
    double mean2 = sum2 / n2;
    return (n1 * mean1 + n2 * mean2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0}, (double[]){2.0}, 1, 1 },
    { (double[]){0.5, -0.5}, (double[]){1.0, 1.0}, 2, 2 },
    { (double[]){3.0, 4.0, 5.0}, (double[]){10.0}, 3, 1 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){5.0, -5.0}, 3, 2 },
    { (double[]){-2.5, 2.5, -2.5, 2.5}, (double[]){-1.0, 1.0, -1.0}, 4, 3 },
    { (double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5}, 3, 2 },
    { (double[]){100.0, 200.0}, (double[]){300.0, 400.0, 500.0}, 2, 3 },
    { (double[]){-100.0, -200.0, -300.0}, (double[]){-400.0}, 3, 1 },
    { (double[]){0.0, 10.0, -10.0}, (double[]){5.0, -5.0, 0.0}, 3, 3 },
    { (double[]){-3.14}, (double[]){2.71}, 1, 1 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){10.0, 20.0}, 5, 2 },
    { (double[]){-1.0, -2.0}, (double[]){-3.0, -4.0, -5.0, -6.0, -7.0}, 2, 5 },
    { (double[]){7.0, 7.0, 7.0}, (double[]){3.0, 3.0}, 3, 2 },
    { (double[]){0.123, -0.456, 0.789}, (double[]){-0.321, 0.654}, 3, 2 },
    { (double[]){-10.0, 0.0, 10.0, 20.0}, (double[]){5.0, -5.0, 15.0, -15.0}, 4, 4 },
    { (double[]){42.0}, (double[]){-42.0, 0.0, 42.0}, 1, 3 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, (double[]){-1.1, -2.2, -3.3}, 6, 3 },
    { (double[]){-1.1, -2.2, -3.3}, (double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 3, 6 },
    { (double[]){0.0001, -0.0002}, (double[]){0.0003, -0.0004, 0.0005}, 2, 3 },
    { (double[]){1000.0, -0.5}, (double[]){-1000.0, 0.5}, 2, 2 },
    { (double[]){8.0, 8.0, 8.0, 8.0}, (double[]){8.0, 8.0, 8.0}, 4, 3 },
    { (double[]){1.0, -1.0, 1.0, -1.0}, (double[]){-1.0, 1.0, -1.0, 1.0}, 4, 4 },
    { (double[]){2.0, 3.0, 5.0, 7.0}, (double[]){11.0, 13.0}, 4, 2 },
    { (double[]){1.0, 1.0, 2.0, 3.0, 5.0}, (double[]){8.0, 13.0}, 5, 2 },
    { (double[]){-5.0, 10.0, -15.0, 20.0}, (double[]){-25.0, 30.0}, 4, 2 },
    { (double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4 },
    { (double[]){9.0, 8.0, 7.0}, (double[]){6.0, 5.0, 4.0}, 3, 3 },
    { (double[]){3.3, -2.2, 5.5, -1.1}, (double[]){0.0, 4.4, -3.3}, 4, 3 },
    { (double[]){0.0, 0.0, 5.0}, (double[]){0.0, 10.0, 0.0}, 3, 3 },
    { (double[]){1.0, 2.5, 3.75}, (double[]){4.125, 5.5}, 3, 2 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z49Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    double* follow_case_data2 = (double*)malloc(t1.n2 * sizeof(double));
    memcpy(follow_case_data2, t1.data2, t1.n2 * sizeof(double));
    follow_case.data2 = follow_case_data2;
    // ------------------------------------
    
    // Defensive code: ensure there are at least 2 elements to sort
    if (follow_case.n2 < 2) {
        return follow_case;
    }
    
    // Sort data2 in ascending order
    for (int i = 0; i < follow_case.n2 - 1; ++i) {
        for (int j = i + 1; j < follow_case.n2; ++j) {
            if (follow_case.data2[i] > follow_case.data2[j]) {
                double temp = follow_case.data2[i];
                follow_case.data2[i] = follow_case.data2[j];
                follow_case.data2[j] = temp;
            }
        }
    }
    
    return follow_case;
}

int z49check(double result1, double result2) {
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

TestResult z49runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z49Change(test_cases[test_case_id]);
    // 原始调用
    double source = pooledMean(test_cases[test_case_id].data1, test_cases[test_case_id].data2, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double follow = pooledMean(follow_case.data1, follow_case.data2, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z49check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z49runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}