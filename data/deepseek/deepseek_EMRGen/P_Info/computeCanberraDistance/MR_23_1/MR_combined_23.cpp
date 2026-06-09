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


double computeCanberraDistance(double a[], double b[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double num = abs(a[i] - b[i]);
        double denom = abs(a[i]) + abs(b[i]);
        sum += num == 0.0 && denom == 0.0 ? 0.0 : num / denom;
    }
        return sum;
    }



typedef struct {
    double* a; double* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-4.0, -5.0, -6.0}, 3},
    {(double[]){1.5, 2.5}, (double[]){3.5, 4.5}, 2},
    {(double[]){10.0}, (double[]){20.0}, 1},
    {(double[]){-10.0}, (double[]){5.0}, 1},
    {(double[]){100.0, 200.0}, (double[]){100.0, 200.0}, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6}, 3},
    {(double[]){-0.1, -0.2}, (double[]){0.3, 0.4}, 2},
    {(double[]){1.0, 0.0, -1.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){3.14159, 2.71828}, (double[]){1.41421, 1.73205}, 2},
    {(double[]){1e-6, 2e-6}, (double[]){3e-6, 4e-6}, 2},
    {(double[]){1e6, 2e6}, (double[]){3e6, 4e6}, 2},
    {(double[]){5.0}, (double[]){-5.0}, 1},
    {(double[]){7.2, 8.9, 10.1}, (double[]){7.2, 8.9, 10.1}, 3},
    {(double[]){0.0}, (double[]){0.0}, 1},
    {(double[]){-100.0, 50.0}, (double[]){25.0, -75.0}, 2},
    {(double[]){12.34, 56.78}, (double[]){98.76, 54.32}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){0.5, 1.5, 2.5}, (double[]){2.5, 1.5, 0.5}, 3},
    {(double[]){9.99}, (double[]){10.01}, 1},
    {(double[]){-2.5, 0.0, 2.5}, (double[]){2.5, 0.0, -2.5}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){0.001, 0.002}, (double[]){0.003, 0.004}, 2},
    {(double[]){999.999}, (double[]){1000.001}, 1},
    {(double[]){-1.1, -2.2, -3.3}, (double[]){-4.4, -5.5, -6.6}, 3},
    {(double[]){42.0}, (double[]){-42.0}, 1},
    {(double[]){1.0, 0.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){8.0, 6.0, 4.0}, (double[]){2.0, 0.0, -2.0}, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z23Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_a = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_a, t1.a, t1.n * sizeof(double));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<1时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    int half_length = follow_case.n / 2;
    // 取前一半元素，即子数组长度变为 half_length
    follow_case.n = half_length;
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z23check(double result1, double result2) {
    // 1. 防御性编程 (标量情况无需指针和长度检查)
    // 2. 核心判断逻辑 (标量直接比较)
    // 浮点数比较的特殊处理
    double epsilon = 1e-5;
    
    // 提取左右操作数 A 和 B (代数移项)
    // 条件: result1 >= result2
    // 移项后: result1 >= result2
    double A = result1;
    double B = result2;
    
    // 防御 NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        if (A >= B) return 1;
        else return 0;
    }
    
    // 计算动态宽容度
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较判定 (>=)
    // 若 A < B - tol，则违反条件
    if (A < B - tol) {
        return 0;
    }
    
    // 3. 满足条件，返回 1
    return 1;
}

TestResult z23runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z23Change(test_cases[test_case_id]);
    // 原始调用
    double source = computeCanberraDistance(test_cases[test_case_id].a, test_cases[test_case_id].b, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = computeCanberraDistance(follow_case.a, follow_case.b, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z23check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z23runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}