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


double cosineDistance(double p1[], double p2[], int n) {
    double dotProduct = 0.0;
    double lengthSquaredp1 = 0.0;
    double lengthSquaredp2 = 0.0;

    for (int i = 0; i < n; i++) {
        lengthSquaredp1 += p1[i] * p1[i];
        lengthSquaredp2 += p2[i] * p2[i];
        dotProduct += p1[i] * p2[i];
    }
    
    double denominator = sqrt(lengthSquaredp1) * sqrt(lengthSquaredp2);
    if (denominator < dotProduct) {
        denominator = dotProduct;
    }
    if (denominator == 0 && dotProduct == 0) {
        return 0;
    }
    return 1.0 - dotProduct / denominator;
}


typedef struct {
    double* p1; double* p2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){-1.0, -2.0}, (double[]){-3.0, -4.0}, 2},
    {(double[]){1.5, 2.5}, (double[]){3.5, 4.5}, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6}, 3},
    {(double[]){100.0, 200.0}, (double[]){300.0, 400.0}, 2},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){3.0, 4.0}, (double[]){-4.0, 3.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 0.0}, (double[]){0.0, 1.0}, 2},
    {(double[]){5.0}, (double[]){-5.0}, 1},
    {(double[]){0.5, 1.0, 1.5}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){0.0, 1.0, 2.0}, (double[]){3.0, 4.0, 5.0}, 3},
    {(double[]){7.0, 8.0, 9.0, 10.0}, (double[]){11.0, 12.0, 13.0, 14.0}, 4},
    {(double[]){1.1, 2.2}, (double[]){3.3, 4.4}, 2},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){6.0, 7.0}, (double[]){8.0, 9.0}, 2},
    {(double[]){-1.5, -2.5}, (double[]){-3.5, -4.5}, 2},
    {(double[]){9.0, 18.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){0.25, 0.5, 0.75}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){0.0, 0.0, 1.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){15.0, 30.0}, (double[]){3.0, 6.0}, 2},
    {(double[]){-10.0, 20.0, -30.0}, (double[]){40.0, -50.0, 60.0}, 3}
};
int num_test_cases = 29;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z3Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_p1 = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_p1, t1.p1, t1.n * sizeof(double));
follow_case.p1 = follow_case_p1;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.p1[i] = follow_case.p1[i] * 3.0;
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z3check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件为 return.result1 - return.result2 == 0，移项后为 result1 == result2
    // 提取左右操作数
    double A = result1;
    double B = result2;

    // 防御 NaN
    if (isnan(A) || isnan(B)) return 0;

    // 处理无穷大
    if (isinf(A) || isinf(B)) {
        // 无穷大时退化为数学直接比较
        if (A == B) return 1;
        else return 0;
    }

    // 定义基础容差
    double epsilon = 1e-5;
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 带容差的相等判定
    if (fabs(A - B) > tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z3runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z3Change(test_cases[test_case_id]);
    // 原始调用
    double source = cosineDistance(test_cases[test_case_id].p1, test_cases[test_case_id].p2, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = cosineDistance(follow_case.p1, follow_case.p2, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.p1;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z3check(source, follow);
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