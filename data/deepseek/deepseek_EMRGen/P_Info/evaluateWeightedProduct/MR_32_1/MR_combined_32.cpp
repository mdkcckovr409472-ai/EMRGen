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


double evaluateWeightedProduct( double values[],  double weights[],  int begin, int lengths, int n) {
    double product = 1.0;
     
    for (int i = begin; i < begin + lengths; i++) {
        product *= pow(values[i], weights[i]);
    }
    return product;
}


typedef struct {
    double* values; double* weights; int begin; int lengths; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.5, 1.0, 1.5}, 0, 3, 3},
    {(double[]){2.5, 3.5}, (double[]){1.0, 2.0}, 0, 2, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){0.0, 0.0, 0.0, 0.0}, 0, 4, 4},
    {(double[]){4.0, 9.0}, (double[]){0.5, 0.5}, 0, 2, 2},
    {(double[]){2.0, 3.0, 4.0}, (double[]){1.0, 0.0, 2.0}, 0, 3, 3},
    {(double[]){0.5, 2.0}, (double[]){2.0, -1.0}, 0, 2, 2},
    {(double[]){1.5}, (double[]){3.0}, 0, 1, 1},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.1, 0.2, 0.3}, 0, 3, 3},
    {(double[]){-2.0, 3.0}, (double[]){2.0, 3.0}, 0, 2, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){1.0, 2.0, 1.0}, 0, 3, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 1, 2, 4},
    {(double[]){5.0, 6.0, 7.0, 8.0}, (double[]){0.5, 0.5, 0.5, 0.5}, 2, 2, 4},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 0, 4, 4},
    {(double[]){3.0, 3.0, 3.0}, (double[]){1.0, 2.0, 3.0}, 0, 3, 3},
    {(double[]){1.0, 10.0, 100.0}, (double[]){0.0, 1.0, 0.5}, 0, 3, 3},
    {(double[]){0.25, 4.0}, (double[]){-1.0, 0.5}, 0, 2, 2},
    {(double[]){1.2, 2.4, 3.6}, (double[]){2.0, 1.0, 0.5}, 0, 3, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){2.0, 2.0, 2.0}, 0, 3, 3},
    {(double[]){8.0}, (double[]){1.0/3.0}, 0, 1, 1},
    {(double[]){9.0, 16.0, 25.0}, (double[]){0.5, 0.5, 0.5}, 0, 3, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 2, 3, 5},
    {(double[]){0.0, 5.0}, (double[]){0.0, 2.0}, 0, 2, 2},
    {(double[]){2.0, 2.0, 2.0}, (double[]){1.0, 2.0, 3.0}, 1, 2, 3},
    {(double[]){1.5, 2.5, 3.5, 4.5}, (double[]){1.0, -1.0, 2.0, -2.0}, 0, 4, 4},
    {(double[]){100.0, 0.01}, (double[]){0.5, 0.5}, 0, 2, 2},
    {(double[]){6.0}, (double[]){2.5}, 0, 1, 1},
    {(double[]){1.0, 1.0}, (double[]){100.0, -100.0}, 0, 2, 2},
    {(double[]){2.71828, 3.14159}, (double[]){1.0, 2.0}, 0, 2, 2},
    {(double[]){7.0, 8.0, 9.0, 10.0}, (double[]){0.0, 1.0, 0.0, 1.0}, 1, 3, 4},
    {(double[]){-4.0, 4.0}, (double[]){3.0, 0.25}, 0, 2, 2}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z32Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_weights = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_weights, t1.weights, t1.n * sizeof(double));
follow_case.weights = follow_case_weights;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.weights[i] = follow_case.weights[i] * 2.0;
    }
}

return follow_case;}

#include <cmath>
#include <cstddef>

int z32check(double result1, double result2) {
    // 1. 防御性编程 (标量版本无需空指针和长度检查)

    // 2. 核心判断逻辑 (标量直接比较)
    // 条件: return.result2 == return.result1**2
    // 移项: result2 == result1 * result1

    // 提取移项后的操作数
    double A = result2;
    double B = result1 * result1;

    // 第三步：防御 NaN，并对 Inf 进行特殊放行
    if (std::isnan(A) || std::isnan(B)) return 0;
    if (std::isinf(A) || std::isinf(B)) {
        // 无穷大时退化为精确比较
        if (A == B) return 1;
        else return 0;
    }

    // 第四步：计算动态宽容度
    double epsilon = 1e-5;
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));

    // 第五步：带容差的相等判定 (若违反则 return 0)
    // 移项后的条件是相等 (==)
    if (fabs(A - B) > tol) {
        return 0;
    }

    // 3. 满足条件，返回 1
    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double source = evaluateWeightedProduct(test_cases[test_case_id].values, test_cases[test_case_id].weights, test_cases[test_case_id].begin, test_cases[test_case_id].lengths, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = evaluateWeightedProduct(follow_case.values, follow_case.weights, follow_case.begin, follow_case.lengths, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.weights;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z32check(source, follow);
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