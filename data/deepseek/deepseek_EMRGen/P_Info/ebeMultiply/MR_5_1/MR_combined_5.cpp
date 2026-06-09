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


double* ebeMultiply(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL;  
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] * b[i];  
    }

    return result;  
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2},
    {(double[]){-1.5, 2.5}, (double[]){2.0, -4.0}, 2, 2},
    {(double[]){10.0}, (double[]){-2.0}, 1, 1},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.0, 2.0, 2.0}, 3, 3},
    {(double[]){-2.0, -3.0, -4.0}, (double[]){-1.0, -2.0, -3.0}, 3, 3},
    {(double[]){1.1, 2.2}, (double[]){10.0, 20.0}, 2, 2},
    {(double[]){100.0, 200.0, 300.0}, (double[]){0.1, 0.2, 0.3}, 3, 3},
    {(double[]){3.14159, 2.71828}, (double[]){1.0, 1.0}, 2, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){5.0, 6.0, 7.0, 8.0}, 4, 4},
    {(double[]){-10.5, 20.5}, (double[]){2.0, 0.5}, 2, 2},
    {(double[]){0.0, 1.0, 0.0}, (double[]){5.0, 0.0, 5.0}, 3, 3},
    {(double[]){2.5}, (double[]){4.0}, 1, 1},
    {(double[]){1.0, 0.0, -1.0}, (double[]){-1.0, 0.0, 1.0}, 3, 3},
    {(double[]){1.2, 3.4, 5.6}, (double[]){7.8, 9.0, 1.2}, 3, 3},
    {(double[]){}, (double[]){}, 0, 0},
    {(double[]){1.0, 2.0}, (double[]){3.0, 4.0}, 2, 2},
    {(double[]){-0.1, -0.2, -0.3}, (double[]){10.0, 20.0, 30.0}, 3, 3},
    {(double[]){999.999, 888.888}, (double[]){1.001, 2.002}, 2, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5, 5},
    {(double[]){0.25, 0.5, 0.75}, (double[]){4.0, 2.0, 1.33333}, 3, 3},
    {(double[]){12.34, 56.78}, (double[]){9.87, 6.54}, 2, 2},
    {(double[]){1.0}, (double[]){0.0}, 1, 1},
    {(double[]){2.0, 4.0, 8.0}, (double[]){0.5, 0.25, 0.125}, 3, 3},
    {(double[]){-100.0, 50.0, -25.0}, (double[]){2.0, -2.0, 4.0}, 3, 3},
    {(double[]){1.5}, (double[]){-2.0}, 1, 1},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 3.0, 4.0, 5.0}, 4, 4},
    {(double[]){7.0, 8.0, 9.0}, (double[]){10.0, 11.0, 12.0}, 3, 3},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4},
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 0.5, 0.333333}, 3, 3}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z5Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_a = (double*)malloc(t1.n1 * sizeof(double));
memcpy(follow_case_a, t1.a, t1.n1 * sizeof(double));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n1<=0时出错
if (follow_case.n1 > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n1; i++) {
        follow_case.a[i] = -follow_case.a[i];
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z5check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        // 提取移项后的操作数：result1[i] + result2[i] == 0 等价于 result1[i] == -result2[i]
        double A = result1[i];
        double B = -result2[i]; // 移项后，比较符是 ==

        // 第三步：防御 NaN，并对 Inf 进行特殊放行
        if (std::isnan(A) || std::isnan(B)) return 0;
        if (std::isinf(A) || std::isinf(B)) {
            // 无穷大时，退化为精确数学比较
            if (!(A == B)) return 0;
            continue; // 当前元素比较通过，继续下一个
        }

        // 第四步：计算动态宽容度
        double epsilon = 1e-5;
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 第五步：带容差的比较判定 (若违反则 return 0)
        // 条件为 A == B
        if (fabs(A - B) > tol) {
            return 0;
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z5runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z5Change(test_cases[test_case_id]);
    // 原始调用
    double* source = ebeMultiply(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n1, test_cases[test_case_id].n2); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = ebeMultiply(follow_case.a, follow_case.b, follow_case.n1, follow_case.n2);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z5check(source, follow, test_cases[test_case_id].n1);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z5runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}