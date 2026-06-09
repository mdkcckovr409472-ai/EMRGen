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


double meanDeviation(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        sum += fabs(elements[i] - mean);
    }
    return sum / size;
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, 2.0, 3 },
    { (double[]){5.5, 5.5, 5.5}, 5.5, 3 },
    { (double[]){-1.0, 0.0, 1.0}, 0.0, 3 },
    { (double[]){10.0, -10.0, 5.0, -5.0}, 0.0, 4 },
    { (double[]){2.5, 3.5}, 3.0, 2 },
    { (double[]){0.0}, 0.0, 1 },
    { (double[]){1.2, -1.2, 3.4, -3.4, 0.0}, 0.0, 5 },
    { (double[]){4.0, 4.0, 2.0, 6.0}, 4.0, 4 },
    { (double[]){7.0, 2.0, 5.0}, 5.0, 3 },
    { (double[]){-5.0, -3.0, -1.0, 1.0, 3.0, 5.0}, 0.0, 6 },
    { (double[]){8.0, 6.0, 4.0, 2.0, 0.0}, 4.0, 5 },
    { (double[]){1.0, 2.0, 1.0, 2.0}, 1.5, 4 },
    { (double[]){-2.0, -2.0, -2.0, -2.0}, -2.0, 4 },
    { (double[]){3.1415, 2.718, 1.618}, 2.5, 3 },
    { (double[]){0.5, -0.5, 0.5, -0.5}, 0.0, 4 },
    { (double[]){9.0, 1.0, 5.0, 5.0}, 5.0, 4 },
    { (double[]){-1.0, 2.0, -3.0, 4.0}, 0.5, 4 },
    { (double[]){6.0, -6.0, 3.0, -3.0}, 0.0, 4 },
    { (double[]){2.0, 2.1, 1.9, 2.05, 1.95}, 2.0, 5 },
    { (double[]){-0.1, 0.1, -0.2, 0.2}, 0.0, 4 },
    { (double[]){5.0, 5.0, 5.0, 5.0, 5.0}, 5.0, 5 },
    { (double[]){-4.0, 0.0, 4.0}, 0.0, 3 },
    { (double[]){1.0, 3.0, 5.0, 7.0}, 4.0, 4 },
    { (double[]){-2.5, 0.0, 2.5}, 0.0, 3 },
    { (double[]){0.0, 0.0, 0.0}, 1.0, 3 },
    { (double[]){-3.3, -1.1, 0.0, 1.1, 3.3}, 0.0, 5 },
    { (double[]){2.0, -2.0, 2.0, -2.0, 2.0}, 0.0, 5 },
    { (double[]){0.25, 0.75, 0.5}, 0.5, 3 },
    { (double[]){-1.5, -0.5, 0.5, 1.5}, 0.0, 4 },
    { (double[]){3.0, 3.0, 6.0, 0.0}, 3.0, 4 }
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
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;

    if (follow_case.n < 2) {
        return follow_case;
    }

    for (int i = follow_case.n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        double temp = follow_case.elements[i];
        follow_case.elements[i] = follow_case.elements[j];
        follow_case.elements[j] = temp;
    }

    return follow_case;
}

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
    double source = meanDeviation(test_cases[test_case_id].elements, test_cases[test_case_id].mean, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = meanDeviation(follow_case.elements, follow_case.mean, follow_case.n);
    
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