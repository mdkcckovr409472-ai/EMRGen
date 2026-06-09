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


double weightedMean(double elements[], double theWeights[], int n) {
    int size = n;
    double sum = 0.0;
    double weightsSum = 0.0;
    for(int i = size; --i >= 0; ) {
        double w = theWeights[i];
        sum += elements[i] * w;
        weightsSum += w;
    }
    return sum / weightsSum;
}


typedef struct {
    double* elements; double* theWeights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.5, 1.5, 2.0}, 3},
    {(double[]){-2.0, 0.0, 2.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){1.5, 2.5, 3.5}, (double[]){2.0, 3.0, 4.0}, 3},
    {(double[]){100.0, 200.0}, (double[]){0.1, 0.9}, 2},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){5.0}, (double[]){10.0}, 1},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.2, 4.4, 6.6}, (double[]){1.1, 2.2, 3.3}, 3},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){3.14, 6.28}, (double[]){0.5, 0.5}, 2},
    {(double[]){10.0, 20.0, 30.0, 40.0}, (double[]){0.25, 0.25, 0.25, 0.25}, 4},
    {(double[]){0.5, 1.5}, (double[]){2.0, 6.0}, 2},
    {(double[]){-10.0, 10.0}, (double[]){1.0, 1.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){0.0, 1.0, 0.0, 1.0}, 4},
    {(double[]){7.0, 8.0, 9.0}, (double[]){1.0, 0.5, 1.5}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){3.0, 4.0, 5.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){50.0, 60.0, 70.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){2.0, 3.0, 2.0}, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){9.0, 18.0, 27.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){20.0, 40.0}, (double[]){0.3, 0.7}, 2},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4},
    {(double[]){11.0, 22.0, 33.0}, (double[]){2.0, 3.0, 5.0}, 3}
};
int num_test_cases = 29;


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
double* follow_case_theWeights = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_theWeights, t1.theWeights, t1.n * sizeof(double));
follow_case.theWeights = follow_case_theWeights;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.theWeights[i] = follow_case.theWeights[i] * 0.5;
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z32check(double result1, double result2) {
    // 1. 防御 NaN
    if (isnan(result1) || isnan(result2)) return 0;
    
    // 2. 处理无穷大情况
    if (isinf(result1) || isinf(result2)) {
        // 移项后条件为 result1 == result2
        if (result1 == result2) return 1;
        else return 0;
    }
    
    // 3. 定义基础容差
    double epsilon = 1e-5;
    
    // 4. 提取移项后的操作数
    // 原始条件: result1 == result2
    // 移项后: result1 == result2 (无需移项)
    double A = result1;
    double B = result2;
    
    // 5. 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 6. 带容差的相等比较
    if (fabs(A - B) > tol) {
        return 0;
    }
    
    // 7. 满足条件，返回 1
    return 1;
}

TestResult z32runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z32Change(test_cases[test_case_id]);
    // 原始调用
    double source = weightedMean(test_cases[test_case_id].elements, test_cases[test_case_id].theWeights, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = weightedMean(follow_case.elements, follow_case.theWeights, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.theWeights;
    
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