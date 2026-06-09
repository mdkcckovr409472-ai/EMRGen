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


double safeNorm(double v[], int n) {
    double rdwarf = 3.834e-20;
    double rgiant = 1.304e+19;
    double s1 = 0;
    double s2 = 0;
    double s3 = 0;
    double x1max = 0;
    double x3max = 0;
    double floatn = n;
    double agiant = rgiant / floatn;
    
    for (int i = 0; i < n; i++) {
        double xabs = abs(v[i]);
        if (xabs < rdwarf || xabs > agiant) {
            if (xabs > rdwarf) {
                if (xabs > x1max) {
                    double r = x1max / xabs;
                    s1 = 1 + s1 * r * r;
                    x1max = xabs;
                } else {
                    double r = xabs / x1max;
                    s1 += r * r;
                }
            } else {
                if (xabs > x3max) {
                    double r = x3max / xabs;
                    s3 = 1 + s3 * r * r;
                    x3max = xabs;
                } else {
                    if (xabs != 0) {
                        double r = xabs / x3max;
                        s3 += r * r;
                    }
                }
            }
        } else {
            s2 += xabs * xabs;
        }
    }
    double norm;
    if (s1 != 0) {
        norm = x1max * sqrt(s1 + s2 / x1max / x1max);
    } else {
        if (s2 == 0) {
            norm = x3max * sqrt(s3);
        } else {
            if (s2 >= x3max) {
                norm = sqrt(s2 * (1 + x3max / s2 * (x3max * s3)));
            } else {
                norm = sqrt(x3max * (s2 / x3max + x3max * s3));
            }
        }
    }
    return norm;
}


typedef struct {
    double* v; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){1.0, -2.0, 3.0, -4.0}, 4},
    {(double[]){1.5, 2.5, 3.5}, 3},
    {(double[]){1.0e-10, 2.0e-10, 3.0e-10}, 3},
    {(double[]){1.0e-15, 2.0e-15, 3.0e-15}, 3},
    {(double[]){1.0e10, 2.0e10, 3.0e10}, 3},
    {(double[]){1.0e15, 2.0e15, 3.0e15}, 3},
    {(double[]){1.304e19}, 1},
    {(double[]){3.834e-20}, 1},
    {(double[]){1.304e19 / 2.0}, 1},
    {(double[]){3.834e-20 * 2.0}, 1},
    {(double[]){1.0, 1.304e19, 1.0}, 3},
    {(double[]){1.0, 3.834e-20, 1.0}, 3},
    {(double[]){1.304e19, 3.834e-20}, 2},
    {(double[]){1.0, 2.0, 1.304e19, 3.834e-20}, 4},
    {(double[]){}, 0},
    {(double[]){0.5}, 1},
    {(double[]){-0.5}, 1},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){-100.0, -200.0, -300.0}, 3},
    {(double[]){1.0e-5, 1.0e5}, 2},
    {(double[]){1.0e-8, 1.0e8}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){-1.0, 2.0, -3.0, 4.0, -5.0}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){1.0e-12, 2.0e-12, 1.0e12, 2.0e12}, 4},
    {(double[]){1.0, 1.304e19 / 10.0, 3.834e-20 * 10.0}, 3},
    {(double[]){1.5e-19, 2.5e-19, 1.5e18, 2.5e18}, 4}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        double** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z10Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
double* follow_case_v = (double*)malloc(t1.n * sizeof(double));
memcpy(follow_case_v, t1.v, t1.n * sizeof(double));
follow_case.v = follow_case_v;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int i = 0; i < follow_case.n; i++) {
        follow_case.v[i] = follow_case.v[i] + follow_case.v[i];
    }
}

return follow_case;}

#include <math.h>
#include <stddef.h>

int z10check(double result1, double result2) {
    // 浮点数比较处理
    double epsilon = 1e-5;
    
    // 移项：条件为 result1 <= result2，直接提取
    double A = result1;
    double B = result2;
    
    // 防御NaN
    if (isnan(A) || isnan(B)) return 0;
    
    // 处理无穷大
    if (isinf(A) || isinf(B)) {
        // 无穷大时直接数学比较
        if (A <= B) return 1;
        else return 0;
    }
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的 <= 比较
    if (A > B + tol) return 0;
    
    // 满足条件
    return 1;
}

TestResult z10runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z10Change(test_cases[test_case_id]);
    // 原始调用
    double source = safeNorm(test_cases[test_case_id].v, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = safeNorm(follow_case.v, follow_case.n);
    
    double** memory_list = (double**)malloc(1 * sizeof(double*));
    memory_list[0] = follow_case.v;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z10check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z10runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}