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


double entropy(double k[], int n){
    double h = 0;
    double sum_k = 0;
    for (int i = 0; i < n; i++) {
        sum_k += (double) k[i];
    }
    for (int i = 0; i < n; i++) {
        if (k[i] != 0) {
            double p_i = (double) k[i] / sum_k;
            h += p_i * log(p_i);
        }
    }
    return -h;
}


typedef struct {
    double* k; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){5.0}, 1},
    {(double[]){0.5, 0.5}, 2},
    {(double[]){1.0, 0.0, 1.0}, 3},
    {(double[]){0.0, 5.0, 0.0, 5.0}, 4},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){0.25, 0.25, 0.25, 0.25}, 4},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){7.0, 14.0, 21.0}, 3},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 4},
    {(double[]){0.0, 1.0, 0.0, 0.0}, 4},
    {(double[]){3.0, 3.0, 3.0, 3.0, 3.0}, 5},
    {(double[]){1.2, 2.4, 3.6}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){8.0, 8.0}, 2},
    {(double[]){1.0, 2.0, 1.0, 2.0}, 4},
    {(double[]){0.0, 0.0, 10.0}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, 4},
    {(double[]){0.75, 0.75}, 2},
    {(double[]){9.0, 18.0, 27.0}, 3},
    {(double[]){1.0, 0.0, 0.0, 1.0}, 4},
    {(double[]){4.0, 4.0, 4.0, 4.0, 4.0}, 5},
    {(double[]){0.15, 0.25, 0.35, 0.25}, 4},
    {(double[]){20.0, 40.0, 60.0}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z21Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_k = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_k, t1.k, t1.n * sizeof(double));
    follow_case.k = follow_case_k;
    // ------------------------------------
    
    // 这是根据规则6a生成的防御性代码，防止n<2时出错
    if (follow_case.n < 2) {
        // 元素不足2个，无法进行随机重排，直接返回副本
        return follow_case;
    }
    
    // 这是根据规则5生成的具体操作代码
    srand(time(NULL)); // 初始化随机数种子
    for (int i = follow_case.n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        double temp = follow_case.k[i];
        follow_case.k[i] = follow_case.k[j];
        follow_case.k[j] = temp;
    }
    
    return follow_case;
}

#include <cmath>
#include <cfloat>

int z21check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 == result2
    // 浮点数比较需要特殊处理
    
    // 第一步：定义基础容差
    double epsilon = 1e-5;
    
    // 第二步：代数移项，恢复数据量级
    // 原条件: result1 == result2
    // 移项后: result1 == result2 (已经是标准形式)
    double A = result1;
    double B = result2;
    
    // 第三步：防御NaN，处理Inf
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时退化为数学直接比较
        if (A == B) return 1;
        else return 0;
    }
    
    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 第五步：带容差的比较判定
    // 条件为相等 (==)
    if (fabs(A - B) > tol) {
        return 0;
    }
    
    // 2. 满足条件，返回 1
    return 1;
}

TestResult z21runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z21Change(test_cases[test_case_id]);
    // 原始调用
    double source = entropy(test_cases[test_case_id].k, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = entropy(follow_case.k, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.k;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z21check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z21runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}