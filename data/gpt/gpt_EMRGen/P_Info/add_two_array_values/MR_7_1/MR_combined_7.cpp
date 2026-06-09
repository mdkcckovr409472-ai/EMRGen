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


double add_two_array_values(int a[], int i, int j, int n)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
    {
        return -100000;
    }
    else {
        return (a[i] + a[j]) / 2;
    }
    
}


typedef struct {
    int* a; int i; int j; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){10, 20, 30, 40, 50}, 1, 3, 5 },
    { (int[]){5, -5, 15, -15}, 2, 2, 4 },
    { (int[]){1, 2, 3}, -1, 1, 3 },
    { (int[]){4, 5, 6}, 3, 0, 3 },
    { (int[]){7, 8}, 0, -2, 2 },
    { (int[]){9, 10}, 1, 2, 2 },
    { (int[]){100}, -1, 2, 1 },
    { (int[]){}, 0, 0, 0 },
    { (int[]){42}, 0, 0, 1 },
    { (int[]){-10, 20}, 0, 1, 2 },
    { (int[]){7, -3, 9}, 2, 0, 3 },
    { (int[]){1000, -1000, 500, -500}, 1, 2, 4 },
    { (int[]){3, 8, -2, 7, 0}, 4, 3, 5 },
    { (int[]){-20, 15, 30, -5, 10, 25}, 0, 5, 6 },
    { (int[]){1, 2, 3, 4, 5, 6}, 2, 2, 6 },
    { (int[]){-100, 0, 100}, 1, 2, 3 },
    { (int[]){-1, -2, -3, -4}, 3, 0, 4 },
    { (int[]){9, 8, 7, 6, 5}, 2, 4, 5 },
    { (int[]){0, 0, 0, 0, 0}, 0, 4, 5 },
    { (int[]){-5, 5, 10}, 0, 1, 3 },
    { (int[]){123, -123}, 1, 1, 2 },
    { (int[]){50, 60, 70, 80}, 2, 1, 4 },
    { (int[]){3, -3, 6, -6, 9, -9, 12}, 3, 6, 7 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8}, 0, 7, 8 },
    { (int[]){-10, -9, -8, -7, -6, -5, -4, -3, -2}, 4, 5, 9 },
    { (int[]){100, 200, 300, 400, 500}, 2, 3, 5 },
    { (int[]){-200, -100, 0, 100, 200}, 1, 4, 5 },
    { (int[]){0, 1, 2, 3, 4, 5}, 5, 5, 6 },
    { (int[]){7, 14, 21}, 1, 1, 3 },
    { (int[]){-7, 0, 7, 14}, 0, 2, 4 }
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z7Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- Memory handling code generated based on the rule ---
    int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
    follow_case.a = follow_case_a;
    // ------------------------------------
    
    // Defensive checks: ensure there are enough elements
    if (follow_case.n < 2) {
        return follow_case;
    }
    // Defensive checks: ensure indices are within bounds
    if (follow_case.i < 0 || follow_case.i >= follow_case.n ||
        follow_case.j < 0 || follow_case.j >= follow_case.n) {
        return follow_case;
    }
    
    // Swap elements at indices i and j
    int temp = follow_case.a[follow_case.i];
    follow_case.a[follow_case.i] = follow_case.a[follow_case.j];
    follow_case.a[follow_case.j] = temp;
    
    return follow_case;
}

int z7check(double result1, double result2) {
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

TestResult z7runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z7Change(test_cases[test_case_id]);
    // 原始调用
    double source = add_two_array_values(test_cases[test_case_id].a, test_cases[test_case_id].i, test_cases[test_case_id].j, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = add_two_array_values(follow_case.a, follow_case.i, follow_case.j, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z7check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z7runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}