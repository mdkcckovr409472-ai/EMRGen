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


double sumOfPowerOfDeviations(double data[], int k, double c, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += pow(data[i] - c, k);
        }
    return sum;
}


typedef struct {
    double* data; int k; double c; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 1, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 2, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 3, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 4, 2.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 0, 2.5, 3},
    {(double[]){-1.0, -2.0, -3.0}, 1, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 2, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 4, -2.0, 3},
    {(double[]){-1.0, -2.0, -3.0}, 0, -2.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 1, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 2, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 3, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 4, 0.0, 3},
    {(double[]){0.0, 0.0, 0.0}, 0, 0.0, 3},
    {(double[]){2.5, 2.5, 2.5}, 1, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 2, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 3, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 4, 2.5, 3},
    {(double[]){2.5, 2.5, 2.5}, 0, 2.5, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 1, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 2, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 3, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4, 2.75, 4},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 0, 2.75, 4},
    {(double[]){-1.5, 0.0, 1.5}, 1, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 2, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 3, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 4, 0.0, 3},
    {(double[]){-1.5, 0.0, 1.5}, 0, 0.0, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z15Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_data = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_data, t1.data, t1.n * sizeof(double));
    follow_case.data = follow_case_data;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n <= 0) {
        // 数组为空或长度为负，无法操作，直接返回副本
        return follow_case;
    }

    // 这是根据规则5生成的具体操作代码
    // 随机位置元素置为最大值（如1e6）
    srand(time(NULL)); // 初始化随机数种子
    int random_index = rand() % follow_case.n; // 生成[0, n-1]范围内的随机索引
    follow_case.data[random_index] = 1e6; // 将随机位置的元素置为最大值

    return follow_case;}

#include <math.h>
#include <stddef.h>

int z15check(double result1, double result2) {
    // 1. 防御性编程 (标量版本无需空指针和长度检查)

    // 2. 核心判断逻辑 (标量直接比较)
    // 条件为 return.result1 <= return.result2，即 result1 <= result2
    // 数据类型为 double，需进行浮点数特殊处理

    // 第一步：定义基础容差
    const double epsilon = 1e-5;

    // 第二步：提取左右操作数 A 和 B（代数移项）
    // 条件 result1 <= result2 已经是标准形式
    double A = result1;
    double B = result2;

    // 第三步：防御 NaN，并对 Inf 进行特殊放行
    if (isnan(A) || isnan(B)) return 0;
    if (isinf(A) || isinf(B)) {
        // 无穷大时退化为数学上的直接比较
        if (A <= B) return 1;
        else return 0;
    }

    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 第五步：带容差的比较判定 (若违反则 return 0)
    // 条件为 A <= B，违反条件是 A > B + tol
    if (A > B + tol) {
        return 0;
    }

    // 3. 满足条件，返回 1
    return 1;
}

TestResult z15runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z15Change(test_cases[test_case_id]);
    // 原始调用
    double source = sumOfPowerOfDeviations(test_cases[test_case_id].data, test_cases[test_case_id].k, test_cases[test_case_id].c, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = sumOfPowerOfDeviations(follow_case.data, follow_case.k, follow_case.c, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z15check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z15runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}