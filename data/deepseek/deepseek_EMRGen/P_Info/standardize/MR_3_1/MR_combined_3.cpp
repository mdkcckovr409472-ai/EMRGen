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


double* standardize(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    double sum = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += cp1[i];
        sumSq += cp1[i] * cp1[i];
    }
    double mean = sum / n;
    double sd = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        cp1[i] = (cp1[i] - mean) / sd;
    }
    return cp1;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){0.0, 0.0}, 2},
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-1.0, 0.0, 1.0}, 3},
    {(double[]){10.5, 20.3, 30.7}, 3},
    {(double[]){-5.2, -3.1, -1.8}, 3},
    {(double[]){2.5, 2.5, 2.5, 2.5}, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5},
    {(double[]){-10.0, -5.0, 0.0, 5.0, 10.0}, 5},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){-0.5, 0.0, 0.5}, 3},
    {(double[]){3.14, 6.28, 9.42}, 3},
    {(double[]){1.0, 4.0, 9.0, 16.0}, 4},
    {(double[]){2.0, 4.0, 8.0, 16.0, 32.0}, 5},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 5},
    {(double[]){7.0}, 1},
    {(double[]){1.5, 3.0, 4.5, 6.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 6},
    {(double[]){-20.0, -10.0, 0.0, 10.0, 20.0}, 5},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0}, 5},
    {(double[]){-3.0, -2.0, -1.0}, 3},
    {(double[]){12.34, 45.67, 78.90}, 3},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 7},
    {(double[]){-7.5, -2.5, 2.5, 7.5}, 4},
    {(double[]){1.0, 1.0, 2.0, 3.0, 5.0, 8.0}, 6},
    {(double[]){0.25, 0.5, 0.75, 1.0}, 4},
    {(double[]){-100.0, 0.0, 100.0}, 3},
    {(double[]){9.8, 8.7, 7.6, 6.5}, 4},
    {(double[]){2.718, 3.142, 1.618}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double* result1;
        double* result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
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
        follow_case.data[i] = follow_case.data[i] * 2.0;
    }
}

return follow_case;}

#include <cmath>
#include <cstddef>

int z3check(double* result1, double* result2, int n) {
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
            // 如果相等，继续检查下一个元素
            continue;
        }

        // 定义基础容差并计算动态容差
        double epsilon = 1e-5;
        double tol = epsilon * std::fmax(1.0, std::fmax(std::fabs(A), std::fabs(B)));

        // 带容差的相等比较 (移项后为 A == B)
        if (std::fabs(A - B) > tol) {
            return 0; // 一旦违反条件，立即返回 0
        }
    }

    // 3. 全部满足，返回 1
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double* source = standardize(test_cases[test_case_id].data, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double* follow = standardize(follow_case.data, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow, test_cases[test_case_id].n);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z3runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}