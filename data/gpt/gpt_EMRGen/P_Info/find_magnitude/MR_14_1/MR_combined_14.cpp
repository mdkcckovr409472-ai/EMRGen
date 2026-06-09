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


double find_magnitude(int a[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * a[i];
    }
    double result = sqrt(sum);
    return result;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0 },
    { (int[]){0}, 1 },
    { (int[]){5}, 1 },
    { (int[]){-3}, 1 },
    { (int[]){3, -4}, 2 },
    { (int[]){1, 2, 2}, 3 },
    { (int[]){-1, 0, 1}, 3 },
    { (int[]){5, -2, 7, -1}, 4 },
    { (int[]){2, 2, 2, 2}, 4 },
    { (int[]){-3, 4, -5, 6, -7}, 5 },
    { (int[]){0, -2, 5, -1, 3}, 5 },
    { (int[]){-4, 1, -6, 2, -8, 3}, 6 },
    { (int[]){0, 0, 5, -5, 0, 3}, 6 },
    { (int[]){7, -3, 0, 2, -2, 4, -1}, 7 },
    { (int[]){-5, 9, -2, 8, -6, 1, -3}, 7 },
    { (int[]){3, 3, 3, 3, 3, 3, 3, 3}, 8 },
    { (int[]){-4, -4, -4, -4, -4, -4, -4, -4}, 8 },
    { (int[]){1, -1, 2, -2, 3, -3, 4, -4}, 8 },
    { (int[]){5, -7, 2, -3, 6, -1, 0, 4, -2}, 9 },
    { (int[]){-2, 3, -5, 1, -4, 6, -1, 2, -3, 0}, 10 },
    { (int[]){9, 8, 7, 6, 5}, 5 },
    { (int[]){-9, -8, -7, -6, -5}, 5 },
    { (int[]){0, 5, 0, -5, 0, 3, 0, -3}, 8 },
    { (int[]){1, 2, 3, 2, 1}, 5 },
    { (int[]){4, -2, 4, -2, 0}, 5 },
    { (int[]){-5, -5}, 2 },
    { (int[]){0, 0, 0}, 3 },
    { (int[]){1, -1, 1, -1}, 4 },
    { (int[]){10, -10, 5, -5, 0}, 5 },
    { (int[]){8, -8, 0, 7, -7, 1}, 6 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z14Change(TestCase t1) {
    TestCase follow_case = t1;
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    if (follow_case.n < 2) {
        return follow_case;
    }
    for (int i = 0; i < follow_case.n - 1; ++i) {
        for (int j = 0; j < follow_case.n - i - 1; ++j) {
            if (follow_case.a[j] > follow_case.a[j + 1]) {
                int tmp = follow_case.a[j];
                follow_case.a[j] = follow_case.a[j + 1];
                follow_case.a[j + 1] = tmp;
            }
        }
    }
    return follow_case;
}

int z14check(double result1, double result2) {
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

TestResult z14runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z14Change(test_cases[test_case_id]);
    // 原始调用
    double source = find_magnitude(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = find_magnitude(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
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