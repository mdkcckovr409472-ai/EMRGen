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


double* ebeDivide(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL;  
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        if (b[i] == 0.0) {
            result[i] = INFINITY;  
        } else {
            result[i] = a[i] / b[i];
        }
    }

    return result;  
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){10.0, 20.0}, (double[]){2.0, 4.0}, 2, 2},
    {(double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){1.0, 2.0, 3.0}, 3, 3},
    {(double[]){1.5, 2.5}, (double[]){0.5, 0.5}, 2, 2},
    {(double[]){100.0, 200.0, 300.0}, (double[]){100.0, 200.0, 300.0}, 3, 3},
    {(double[]){1.0}, (double[]){1.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){0.1, 0.2, 0.3, 0.4}, 4, 4},
    {(double[]){-10.0, 20.0, -30.0}, (double[]){5.0, -4.0, 6.0}, 3, 3},
    {(double[]){0.0}, (double[]){5.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 0.0, 3.0}, 3, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 5, 5},
    {(double[]){3.14, 2.71}, (double[]){1.0, 1.0}, 2, 2},
    {(double[]){1.0, 2.0}, (double[]){-1.0, -2.0}, 2, 2},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 3.0, 5.0}, 3, 3},
    {(double[]){10.0}, (double[]){3.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5, 5},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1000.0}, 2, 2},
    {(double[]){0.0, 0.0}, (double[]){1.0, -1.0}, 2, 2},
    {(double[]){-1.0, -1.0, -1.0}, (double[]){-1.0, -1.0, -1.0}, 3, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3, 3},
    {(double[]){9.0, 16.0, 25.0}, (double[]){3.0, 4.0, 5.0}, 3, 3},
    {(double[]){1.1, 2.2}, (double[]){1.1, 2.2}, 2, 2},
    {(double[]){7.0, 14.0, 21.0}, (double[]){7.0, 7.0, 7.0}, 3, 3},
    {(double[]){0.001, 0.002}, (double[]){0.001, 0.002}, 2, 2},
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.0, 0.0, 0.0}, 3, 3},
    {(double[]){5.0, 10.0, 15.0, 20.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4},
    {(double[]){12.0, 24.0}, (double[]){6.0, 8.0}, 2, 2},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 5, 5}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z4Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_a = (double*)malloc(t1.n1 * sizeof(double));
memcpy(follow_case_a, t1.a, t1.n1 * sizeof(double));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n1<=0时出错
if (follow_case.n1 <= 0) {
    // 数组为空或长度为负，无法进行除法操作，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
for (int i = 0; i < follow_case.n1; i++) {
    follow_case.a[i] = follow_case.a[i] / 4.0;
}

return follow_case;}

#include <cmath>
#include <cstddef>

int z4check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        // 条件: result1[] - 4 * result2[] == 0
        // 移项后: result1 == 4 * result2
        double A = result1[i];
        double B = 4.0 * result2[i];

        // 浮点数特殊处理
        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;

        // 处理无穷大
        if (std::isinf(A) || std::isinf(B)) {
            if (!(A == B)) return 0; // 直接数学比较
            continue; // 满足条件，继续检查下一个元素
        }

        // 定义基础容差
        double epsilon = 1e-5;
        // 计算动态宽容度
        double tol = epsilon * std::fmax(1.0, std::fmax(std::fabs(A), std::fabs(B)));

        // 带容差的相等判定 (==)
        if (std::fabs(A - B) > tol) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z4runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z4Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeDivide(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeDivide(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z4check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z4runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}