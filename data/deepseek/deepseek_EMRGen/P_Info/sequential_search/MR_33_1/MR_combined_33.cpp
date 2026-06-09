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


int sequential_search(int a[], int key, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] == key) {
            return i;
        }
    }
    return -1;
}


typedef struct {
    int* a; int key; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 3, 5},
    {(int[]){1, 2, 3, 4, 5}, 1, 5},
    {(int[]){1, 2, 3, 4, 5}, 5, 5},
    {(int[]){1, 2, 3, 4, 5}, 0, 5},
    {(int[]){1, 2, 3, 4, 5}, 6, 5},
    {(int[]){5, 4, 3, 2, 1}, 3, 5},
    {(int[]){5, 4, 3, 2, 1}, 5, 5},
    {(int[]){5, 4, 3, 2, 1}, 1, 5},
    {(int[]){5, 4, 3, 2, 1}, 0, 5},
    {(int[]){5, 4, 3, 2, 1}, 6, 5},
    {(int[]){10}, 10, 1},
    {(int[]){10}, 5, 1},
    {(int[]){10}, 20, 1},
    {(int[]){-5, -2, 0, 2, 5}, 0, 5},
    {(int[]){-5, -2, 0, 2, 5}, -5, 5},
    {(int[]){-5, -2, 0, 2, 5}, 5, 5},
    {(int[]){-5, -2, 0, 2, 5}, -3, 5},
    {(int[]){-5, -2, 0, 2, 5}, 3, 5},
    {(int[]){100, 200, 300}, 200, 3},
    {(int[]){100, 200, 300}, 100, 3},
    {(int[]){100, 200, 300}, 300, 3},
    {(int[]){100, 200, 300}, 150, 3},
    {(int[]){7, 7, 7, 7}, 7, 4},
    {(int[]){7, 7, 7, 7}, 8, 4},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7, 7},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 13, 7},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 1, 7},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 4, 7},
    {(int[]){}, 5, 0},
    {(int[]){2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 14, 10}
};
int num_test_cases = 30;


    typedef struct {
        int result1;
        int result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z33Change(TestCase t1) {
    TestCase follow_case = t1;
    // 操作描述为"取绝对值"，目标参数为key，类型为int，不是数组类型。
    // 根据规则4，仅当目标参数是数组类型时才执行malloc和memcpy。
    // 因此，此处无需进行数组内存深拷贝。

    // 防御性编程：取绝对值操作不依赖于数组长度n，无需检查n。
    // 取绝对值操作不涉及除法或数学函数域检查。
    // 直接对follow_case.key执行取绝对值操作。

    // 根据规则5生成的具体操作代码：取绝对值
    if (follow_case.key < 0) {
        follow_case.key = -follow_case.key;
    }

    return follow_case;
}

int z33check(int result1, int result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    if (!(result1 <= result2)) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z33runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z33Change(test_cases[test_case_id]);
    // 原始调用
    int source = sequential_search(test_cases[test_case_id].a, test_cases[test_case_id].key, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    int follow = sequential_search(follow_case.a, follow_case.key, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z33check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z33runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}