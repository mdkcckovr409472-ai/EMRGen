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


double* square(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    for (int i = 0; i < n; i++) {
        cp1[i] = cp1[i] * cp1[i];
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){2.0, 3.0}, 2},
    {(double[]){0.0}, 1},
    {(double[]){-1.0}, 1},
    {(double[]){-2.0, -3.0}, 2},
    {(double[]){0.5}, 1},
    {(double[]){-0.5}, 1},
    {(double[]){1.5, 2.5}, 2},
    {(double[]){-1.5, -2.5}, 2},
    {(double[]){10.0}, 1},
    {(double[]){-10.0}, 1},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){-2.0, -4.0, -6.0}, 3},
    {(double[]){0.25, 0.75}, 2},
    {(double[]){-0.25, -0.75}, 2},
    {(double[]){100.0, 200.0}, 2},
    {(double[]){-100.0, -200.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){-1.0, -2.0, -3.0, -4.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){-0.1, -0.2, -0.3}, 3},
    {(double[]){5.0}, 1},
    {(double[]){-5.0}, 1},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){3.14159}, 1},
    {(double[]){-3.14159}, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z6Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
follow_case.data = follow_case_data;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.data[i] = fabs(follow_case.data[i]);
    }
}

return follow_case;}

#include <cmath>
#include <cstddef>

int z6check(double* result1, double* result2, int n) {
    // 1. 防御性编程 (空指针与长度检查)
    if (result1 == NULL || result2 == NULL) return 0;
    if (n <= 0) return 1;

    // 2. 核心判断逻辑 (elementwise)
    for (int i = 0; i < n; i++) {
        // 提取移项后的操作数 A 和 B
        double A = result1[i];
        double B = result2[i];

        // 防御 NaN
        if (std::isnan(A) || std::isnan(B)) return 0;

        // 处理无穷大
        if (std::isinf(A) || std::isinf(B)) {
            if (!(A == B)) return 0;
            continue; // 当前元素满足，继续检查下一个
        }

        // 定义基础容差
        double epsilon = 1e-5;
        // 计算动态宽容度
        double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

        // 带容差的相等判定 (移项后条件为 A == B)
        if (fabs(A - B) > tol) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z6runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z6Change(test_cases[test_case_id]);
    // 原始调用
    double* source = square(test_cases[test_case_id].data, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = square(follow_case.data, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z6check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z6runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}