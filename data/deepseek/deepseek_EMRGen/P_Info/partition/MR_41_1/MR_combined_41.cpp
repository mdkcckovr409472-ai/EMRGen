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


int partition(double work[], int begin, int end, int pivot) {
    double value = work[pivot];
    work[pivot] = work[begin];
    int i = begin + 1;
    int j = end - 1;
    while (i < j) {
        while (i < j && work[j] > value) {
            --j;
        }
        while (i < j && work[i] < value) {
            ++i;
        }
        if (i < j) {
            double tmp = work[i];
            work[i++] = work[j];
            work[j--] = tmp;
        }
    }
    if (i >= end || work[i] > value) {
        --i;
    }
    work[begin] = work[i];
    work[i] = value;
    return i;
}


typedef struct {
    double* work; int begin; int end; int pivot;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0, 5, 2},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 0, 5, 2},
    {(double[]){3.0, 1.0, 4.0, 1.0, 5.0}, 0, 5, 0},
    {(double[]){3.0, 1.0, 4.0, 1.0, 5.0}, 0, 5, 4},
    {(double[]){2.5}, 0, 1, 0},
    {(double[]){9.8, 1.2}, 0, 2, 1},
    {(double[]){-1.5, -3.0, 0.0, 2.2}, 0, 4, 1},
    {(double[]){1.1, 2.2, 3.3}, 1, 3, 1},
    {(double[]){1.1, 2.2, 3.3}, 1, 3, 2},
    {(double[]){5.5, 4.4, 3.3, 2.2, 1.1, 0.0}, 1, 5, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 0, 5, 0},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0}, 0, 5, 4},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 0, 4, 1},
    {(double[]){3.14, 1.59, 2.65}, 0, 3, 0},
    {(double[]){3.14, 1.59, 2.65}, 0, 3, 2},
    {(double[]){10.1, 20.2, 30.3, 40.4}, 0, 4, 2},
    {(double[]){-5.0, 0.0, 5.0}, 0, 3, 1},
    {(double[]){1.0}, 0, 1, 0},
    {(double[]){7.0, 3.0, 9.0, 5.0, 1.0}, 0, 5, 2},
    {(double[]){6.6, 7.7, 8.8, 9.9}, 1, 4, 2},
    {(double[]){0.5, 1.5, 2.5, 3.5}, 0, 4, 1},
    {(double[]){100.0, 200.0, 150.0}, 0, 3, 0},
    {(double[]){100.0, 200.0, 150.0}, 0, 3, 2},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 1, 4, 2},
    {(double[]){9.0, 8.0, 7.0, 6.0}, 0, 4, 3},
    {(double[]){1.2, 3.4, 5.6, 7.8}, 0, 4, 1},
    {(double[]){0.1, 0.01, 0.001}, 0, 3, 0},
    {(double[]){0.1, 0.01, 0.001}, 0, 3, 2},
    {(double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 2, 5, 3},
    {(double[]){3.0, 6.0, 9.0, 12.0}, 0, 4, 1}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z41Change(TestCase t1) {
TestCase follow_case = t1;

// 交换 begin 和 end 的值
int temp = follow_case.begin;
follow_case.begin = follow_case.end;
follow_case.end = temp;

return follow_case;}

int z41check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 < result2)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z41runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z41Change(test_cases[test_case_id]);
    // 原始调用
    int source = partition(test_cases[test_case_id].work, test_cases[test_case_id].begin, test_cases[test_case_id].end, test_cases[test_case_id].pivot); // MODIFIED: Explicit type
    // 变换后调用
    int follow = partition(follow_case.work, follow_case.begin, follow_case.end, follow_case.pivot);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z41check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z41runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}