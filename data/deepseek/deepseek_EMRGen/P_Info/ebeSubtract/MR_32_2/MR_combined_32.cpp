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


double* ebeSubtract(double a[], double b[], int n1, int n2) {
    if (n1 != n2 || a == NULL || b == NULL) {
        return NULL;
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (!result) return NULL;

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] - b[i];
    }
    return result;
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.5, 1.5, 2.5}, 3, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2},
    {(double[]){-1.0, -2.0}, (double[]){-3.0, -4.0}, 2, 2},
    {(double[]){10.5, 20.25}, (double[]){5.25, 10.125}, 2, 2},
    {(double[]){100.0}, (double[]){50.0}, 1, 1},
    {(double[]){3.14159, 2.71828}, (double[]){1.0, 1.0}, 2, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.3, 0.2, 0.1}, 3, 3},
    {(double[]){-10.0, 0.0, 10.0}, (double[]){5.0, 5.0, 5.0}, 3, 3},
    {(double[]){1.0e-6, 2.0e-6}, (double[]){0.5e-6, 1.5e-6}, 2, 2},
    {(double[]){999.999, 888.888}, (double[]){111.111, 222.222}, 2, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){0.5, 0.5, 0.5, 0.5, 0.5}, 5, 5},
    {(double[]){2.5, 5.0, 7.5}, (double[]){2.5, 5.0, 7.5}, 3, 3},
    {(double[]){-1.5, -3.0, -4.5}, (double[]){-0.5, -1.0, -1.5}, 3, 3},
    {(double[]){1000.0, 2000.0, 3000.0}, (double[]){500.0, 1500.0, 2500.0}, 3, 3},
    {(double[]){0.0, -0.0}, (double[]){0.0, -0.0}, 2, 2},
    {(double[]){1.0, 2.0}, (double[]){2.0, 1.0}, 2, 2},
    {(double[]){12.34, 56.78}, (double[]){9.87, 65.43}, 2, 2},
    {(double[]){0.001, 0.002, 0.003}, (double[]){0.0005, 0.0015, 0.0025}, 3, 3},
    {(double[]){-100.5, 200.75}, (double[]){50.25, -100.375}, 2, 2},
    {(double[]){1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0}, 3, 3},
    {(double[]){9.0, 8.0, 7.0, 6.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4},
    {(double[]){1.5}, (double[]){3.0}, 1, 1},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0, 0.0}, 6, 6},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 4.0, 8.0}, 4, 4},
    {(double[]){-1.0, -1.0, -1.0, -1.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4, 4},
    {(double[]){7.7, 8.8, 9.9}, (double[]){0.7, 0.8, 0.9}, 3, 3},
    {(double[]){1.0, 0.0, -1.0}, (double[]){-1.0, 0.0, 1.0}, 3, 3},
    {(double[]){42.0}, (double[]){24.0}, 1, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5, 5}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z32Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_b = (double*)malloc(t1.n2 * sizeof(double));
memcpy(follow_case_b, t1.b, t1.n2 * sizeof(double));
follow_case.b = follow_case_b;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n2<=0时出错
if (follow_case.n2 <= 0) {
    // 数组为空或长度为负，无法操作，直接返回副本
    return follow_case;
}

// 这是根据规则5生成的具体操作代码
for (int i = 0; i < follow_case.n2; i++) {
    follow_case.b[i] = follow_case.b[i] + 0.5;
}

return follow_case;}

#include <cmath>
#include <algorithm>

int z32check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        // 提取移项后的操作数 A = result1[i], B = result2[i]
        double A = result1[i];
        double B = result2[i];
        
        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;
        
        // 处理无穷大情况
        if (std::isinf(A) || std::isinf(B)) {
            // 移项后的条件为 A > B
            if (!(A > B)) return 0;
            continue; // 当前元素检查通过，继续下一个
        }
        
        // 定义基础容差
        double epsilon = 1e-5;
        // 计算动态宽容度
        double tol = epsilon * std::max(1.0, std::max(std::fabs(A), std::fabs(B)));
        
        // 移项后的条件为 A > B
        // 违反条件为 A <= B + tol
        if (A <= B + tol) {
            return 0;
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeSubtract(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeSubtract(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.b;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z32check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z32runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}