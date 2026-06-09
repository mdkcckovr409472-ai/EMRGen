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


double meanDifference(double sample1[], double sample2[], int n ) {
    double sumDifference = 0;
    for (int i = 0; i < n; i++) {
        sumDifference += sample1[i] - sample2[i];
    }
    return sumDifference / n;
}


typedef struct {
    double* sample1; double* sample2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.5, -2.5}, (double[]){1.5, 2.5}, 2},
    {(double[]){10.2, 20.4, 30.6}, (double[]){5.1, 10.2, 15.3}, 3},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){100.0, 200.0, 300.0, 400.0}, (double[]){50.0, 150.0, 250.0, 350.0}, 4},
    {(double[]){2.5, 3.5}, (double[]){7.5, 6.5}, 2},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -10.0, -15.0}, 3},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.3, 0.2, 0.1}, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5},
    {(double[]){8.0, 6.0, 4.0}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){15.0, 25.0, 35.0}, 3},
    {(double[]){12.34, 45.67}, (double[]){98.76, 54.32}, 2},
    {(double[]){7.0}, (double[]){3.0}, 1},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){2.0, 4.0, 6.0, 8.0, 10.0}, 5},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){-1.0, -3.0, -5.0}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5}, (double[]){3.5, 2.5, 1.5, 0.5}, 4},
    {(double[]){1000.0, 2000.0}, (double[]){500.0, 1500.0}, 2},
    {(double[]){9.9, 8.8, 7.7}, (double[]){1.1, 2.2, 3.3}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, (double[]){3.0, 6.0, 9.0, 12.0}, 4},
    {(double[]){-7.5, 7.5}, (double[]){7.5, -7.5}, 2},
    {(double[]){1.2, 3.4, 5.6}, (double[]){1.2, 3.4, 5.6}, 3},
    {(double[]){22.0, 33.0, 44.0}, (double[]){11.0, 22.0, 33.0}, 3},
    {(double[]){0.01, 0.02}, (double[]){0.02, 0.01}, 2},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0}, (double[]){55.0, 65.0, 75.0, 85.0, 95.0}, 5},
    {(double[]){4.0, 8.0, 12.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-100.0, 100.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, (double[]){6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 6},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3}
};
int num_test_cases = 29;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z31Change(TestCase t1) {
    TestCase follow_case = t1;
    // --- 这是根据规则4生成的内存处理代码 ---
    double* follow_case_sample2 = (double*)malloc(t1.n * sizeof(double));
    memcpy(follow_case_sample2, t1.sample2, t1.n * sizeof(double));
    follow_case.sample2 = follow_case_sample2;
    // ------------------------------------

    // 这是根据规则6a生成的防御性代码，防止n<=0时出错
    if (follow_case.n > 0) {
        // 这是根据规则5生成的具体操作代码
        for (int i = 0; i < follow_case.n; i++) {
            follow_case.sample2[i] = follow_case.sample2[i] - 1.0;
        }
    }

    return follow_case;
}

#include <math.h>
#include <stddef.h>

int z31check(double result1, double result2) {
    // 1. 防御性编程 (标量版本无需空指针和长度检查)
    // 2. 核心判断逻辑 (标量直接比较)
    // 对于浮点数比较，必须进行特殊处理
    
    // 第一步：定义基础容差
    double epsilon = 1e-5;
    
    // 第二步：提取左右操作数 A 和 B（代数移项，恢复数据量级）
    // 原始条件: result1 < result2
    // 移项后: result1 < result2 (已经是标准形式)
    double A = result1;
    double B = result2;
    
    // 第三步：防御 NaN，并对 Inf 进行特殊放行
    if (isnan(A) || isnan(B)) return 0;
    
    // 如果出现无穷大，动态容差会失效(Inf-Inf=NaN)，此时应退化为数学上的直接比较
    if (isinf(A) || isinf(B)) {
        if (A < B) return 1;
        else return 0;
    }
    
    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 第五步：带容差的比较判定 (若违反则 return 0)
    // 移项后的条件是 (<): 若 A >= B - tol，则 return 0;
    if (A >= B - tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z31runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z31Change(test_cases[test_case_id]);
    // 原始调用
    double source = meanDifference(test_cases[test_case_id].sample1, test_cases[test_case_id].sample2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = meanDifference(follow_case.sample1, follow_case.sample2, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.sample2;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z31check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z31runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}