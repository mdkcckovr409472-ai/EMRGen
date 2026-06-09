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


double harmonicMean(double data[], int n) {
    double sumOfInversions = 0;
    for (int i = 0; i < n; i++) {
        sumOfInversions += 1 / data[i];
    }
    return n / sumOfInversions;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){2.5, 3.5, 4.5}, 3},
    {(double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){2.0, 2.0}, 2},
    {(double[]){3.0}, 1},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 4},
    {(double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){5.0, 10.0, 15.0, 20.0}, 4},
    {(double[]){8.0, 12.0}, 2},
    {(double[]){6.0, 6.0, 6.0}, 3},
    {(double[]){2.2, 3.3, 4.4}, 3},
    {(double[]){7.0, 14.0, 21.0}, 3},
    {(double[]){0.25, 0.5, 0.75}, 3},
    {(double[]){9.0, 18.0, 27.0, 36.0}, 4},
    {(double[]){1.2, 2.4, 3.6}, 3},
    {(double[]){4.0, 8.0, 12.0, 16.0}, 4},
    {(double[]){11.0, 22.0}, 2},
    {(double[]){0.8, 1.6, 2.4, 3.2}, 4},
    {(double[]){15.0, 30.0, 45.0}, 3},
    {(double[]){1.75, 3.5, 5.25}, 3},
    {(double[]){2.1, 4.2, 6.3, 8.4}, 4},
    {(double[]){13.0, 26.0, 39.0}, 3},
    {(double[]){0.3, 0.6, 0.9, 1.2}, 4},
    {(double[]){17.0, 34.0}, 2},
    {(double[]){1.9, 3.8, 5.7}, 3},
    {(double[]){2.8, 5.6, 8.4, 11.2}, 4},
    {(double[]){19.0, 38.0, 57.0}, 3},
    {(double[]){0.4, 0.8, 1.2, 1.6, 2.0}, 5}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z9Change(TestCase t1) {
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
        follow_case.data[i] = -follow_case.data[i];
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z9check(double result1, double result2) {
    // 1. 核心判断逻辑 (标量直接比较)
    // 条件: result1 % result2 == 0
    // 对于浮点数，需要特殊处理

    // 第一步：定义基础容差
    double epsilon = 1e-5;

    // 第二步：提取左右操作数 A 和 B
    // 条件 result1 % result2 == 0 等价于 result1 == k * result2，其中k为整数
    // 但更直接的数学表达是：余数 = result1 - floor(result1 / result2) * result2 == 0
    // 移项后：result1 == floor(result1 / result2) * result2
    // 然而，对于浮点数取余，我们通常检查 fmod(result1, result2) == 0
    // 因此我们提取：A = fmod(result1, result2); B = 0.0;
    // 但根据规则3，不能令B=0，因为会丢失量级。
    // 重新思考：条件 fmod(result1, result2) == 0
    // 可以视为：result1 / result2 是整数（在浮点误差内）
    // 令 quotient = result1 / result2;
    // 条件变为：quotient == round(quotient) （在容差内）
    // 即：A = quotient; B = round(quotition);
    // 但result2可能为0，需要先检查。

    // 防御性检查：除数不能为0（或接近0）
    if (fabs(result2) < epsilon) {
        // 如果result2为0，则取余运算未定义，通常视为不满足条件
        return 0;
    }

    double quotient = result1 / result2;
    double rounded = round(quotient);

    double A = quotient;
    double B = rounded;

    // 第三步：防御NaN和Inf
    if (isnan(A) || isnan(B)) return 0;
    if (isinf(A) || isinf(B)) {
        // 如果出现无穷大，直接比较
        if (A == B) return 1;
        else return 0;
    }

    // 第四步：计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 第五步：带容差的比较判定
    // 条件：quotient == round(quotient)  (即 A == B)
    if (fabs(A - B) > tol) {
        return 0;
    }

    // 2. 满足条件，返回 1
    return 1;
}

TestResult z9runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z9Change(test_cases[test_case_id]);
    // 原始调用
    double source = harmonicMean(test_cases[test_case_id].data, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = harmonicMean(follow_case.data, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.data;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z9check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z9runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}