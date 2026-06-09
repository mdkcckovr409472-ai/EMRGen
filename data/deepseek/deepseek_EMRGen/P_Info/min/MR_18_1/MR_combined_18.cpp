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


double min(double elements[], int n) {
    int size = n;
    double min = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] < min) {
            min = elements[i];
        }
    }
    return min;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){1.0, 2.0}, 2},
    {(double[]){2.0, 1.0}, 2},
    {(double[]){5.0, 3.0, 9.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.5, 2.7, 3.1}, 3},
    {(double[]){3.1, 1.5, 2.7}, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 4},
    {(double[]){40.0, 30.0, 20.0, 10.0}, 4},
    {(double[]){-5.5, 10.2, 0.0, -3.3}, 4},
    {(double[]){1.1, 1.1, 1.1}, 3},
    {(double[]){2.0}, 1},
    {(double[]){-100.0, 50.0}, 2},
    {(double[]){3.14, 2.71, 1.41}, 3},
    {(double[]){1.41, 3.14, 2.71}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){0.003, 0.001, 0.002}, 3},
    {(double[]){1000000.0, 2000000.0}, 2},
    {(double[]){-2000000.0, -1000000.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){2.5, -1.2, 0.0, 4.8, -3.1}, 5},
    {(double[]){10.5}, 1},
    {(double[]){-7.3, -7.3}, 2},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 6},
    {(double[]){0.6, 0.5, 0.4, 0.3, 0.2, 0.1}, 6},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){9.9, 8.8, 7.7}, 3},
    {(double[]){7.7, 9.9, 8.8}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z18Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_elements = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_elements, t1.elements, t1.n * sizeof(double));
    follow_case.elements = follow_case_elements;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        int random_index = rand() % follow_case.n;
        follow_case.elements[random_index] = -INFINITY;
    }

    return follow_case;
}

#include <cmath>
#include <cfloat>

int z18check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件为 result1 > result2，移项后 A = result1, B = result2, 比较符为 >
    
    double A = result1;
    double B = result2;
    
    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时直接进行数学比较
        if (A > B) return 1;
        else return 0;
    }
    
    // 定义基础容差
    double epsilon = 1e-5;
    
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较判定: 检查是否违反 result1 > result2
    // 对于 > 条件: 若 A <= B + tol，则违反条件
    if (A <= B + tol) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z18runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z18Change(test_cases[test_case_id]);
    // 原始调用
    double source = min(test_cases[test_case_id].elements, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = min(follow_case.elements, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.elements;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z18check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z18runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}