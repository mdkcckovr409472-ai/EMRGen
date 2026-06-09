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


bool checkNonNegative(double a[], int n){
    
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            return false;
        }
    }
    return true; 
}


typedef struct {
    double* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){2.5}, 1 },
    { (double[]){-1.0}, 1 },
    { (double[]){3.1, 4.2, 5.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){1.0, 0.0, 2.5}, 3 },
    { (double[]){5.5, 2.2, -0.5}, 3 },
    { (double[]){-0.3, 1.1, 2.2}, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}, 10 },
    { (double[]){1.0, -2.0, 3.0, -4.0, 5.0, -6.0, 7.0, -8.0, 9.0, -10.0}, 10 },
    { (double[]){0.5, 2.3, 4.1, 3.3, 1.0}, 5 },
    { (double[]){5.0, 3.0, -1.0, 2.0, 4.0}, 5 },
    { (double[]){7.7, 7.7, 7.7}, 3 },
    { (double[]){2.0, 0.5, 2.0}, 3 },
    { (double[]){-2.2, -2.2, -2.2}, 3 },
    { (double[]){1.0, 0.0, 2.0, 0.0}, 4 },
    { (double[]){1.0, -1.0, 2.0, -2.0}, 4 },
    { (double[]){3.3, 2.2, 1.1, 4.4, 5.5, 6.6}, 6 },
    { (double[]){3.3, -2.2, 1.1, -4.4, 5.5, -6.6}, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8}, 8 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8}, 8 },
    { (double[]){12345.6}, 1 },
    { (double[]){-9876.5}, 1 },
    { (double[]){2.2, 3.3}, 2 },
    { (double[]){-2.2, -3.3}, 2 },
    { (double[]){0.0, -1.0}, 2 },
    { (double[]){4.4, -3.3, 2.2, -1.1, 0.0, 1.1, -2.2, 3.3, -4.4}, 9 },
    { (double[]){4.4, 3.3, 2.2, 1.1, 0.0, 1.1, 2.2, 3.3, 4.4}, 9 },
    { (double[]){-5.5, 0.0, 2.2, -1.1, 3.3, 0.0, -0.5}, 7 }
};
int num_test_cases = 30;


    typedef struct {
        bool result1;
        bool result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z28Change(TestCase t1) {
    TestCase follow_case = t1;
    double* follow_case_a = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_a, t1.a, t1.n * sizeof(double));
    follow_case.a = follow_case_a;

    if (follow_case.n == 0) {
        return follow_case;
    }

    int random_idx = rand() % follow_case.n;
    follow_case.a[random_idx] *= 2.0;

    return follow_case;
}

int z28check(bool result1, bool result2) {
    if (!(result1 == result2)) {
        return 0;
    }
    return 1;
}

TestResult z28runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z28Change(test_cases[test_case_id]);
    // 原始调用
    bool source = checkNonNegative(test_cases[test_case_id].a, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    bool follow = checkNonNegative(follow_case.a, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z28check(source, follow);
    test_result.status = status;
    
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z28runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}