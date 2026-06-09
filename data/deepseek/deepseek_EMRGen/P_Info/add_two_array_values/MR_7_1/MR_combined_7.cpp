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


double add_two_array_values(int a[], int i, int j, int n)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
    {
        return -100000;
    }
    else {
        return (a[i] + a[j]) / 2;
    }
    
}


typedef struct {
    int* a; int i; int j; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 0, 1, 5},
    {(int[]){1, 2, 3, 4, 5}, 2, 3, 5},
    {(int[]){1, 2, 3, 4, 5}, 4, 0, 5},
    {(int[]){10, 20}, 0, 1, 2},
    {(int[]){10, 20}, 1, 0, 2},
    {(int[]){-5, 0, 5}, 0, 2, 3},
    {(int[]){-5, 0, 5}, 1, 1, 3},
    {(int[]){100, 200, 300, 400}, 0, 3, 4},
    {(int[]){100, 200, 300, 400}, 1, 2, 4},
    {(int[]){7}, 0, 0, 1},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 5, 10},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 9, 0, 10},
    {(int[]){0, 0, 0, 0}, 0, 2, 4},
    {(int[]){0, 0, 0, 0}, 3, 3, 4},
    {(int[]){-10, -20, -30}, 0, 1, 3},
    {(int[]){-10, -20, -30}, 2, 2, 3},
    {(int[]){2, 4, 6, 8}, 0, 2, 4},
    {(int[]){2, 4, 6, 8}, 3, 1, 4},
    {(int[]){1, 3, 5, 7, 9}, 2, 4, 5},
    {(int[]){1, 3, 5, 7, 9}, 0, 4, 5},
    {(int[]){15, 25, 35, 45}, 0, 0, 4},
    {(int[]){15, 25, 35, 45}, 3, 3, 4},
    {(int[]){-1, 1}, 0, 1, 2},
    {(int[]){-1, 1}, 1, 0, 2},
    {(int[]){1000, 2000, 3000}, 0, 2, 3},
    {(int[]){1000, 2000, 3000}, 1, 1, 3},
    {(int[]){8, 6, 4, 2, 0}, 0, 4, 5},
    {(int[]){8, 6, 4, 2, 0}, 2, 3, 5},
    {(int[]){12, 24, 36}, 0, 1, 3},
    {(int[]){12, 24, 36}, 2, 0, 3}
};
int num_test_cases = 30;


    typedef struct {
        double result1;
        double result2;
        int** memory_to_free;
        int memory_count; 
        int status;
} TestResult;

TestCase z7Change(TestCase t1) {
TestCase follow_case = t1;
// --- 这是根据规则4生成的内存处理代码 ---
int* follow_case_a = (int*)malloc(t1.n * sizeof(int));
memcpy(follow_case_a, t1.a, t1.n * sizeof(int));
follow_case.a = follow_case_a;
// ------------------------------------

// 这是根据规则6a生成的防御性代码，防止n<=0时出错
if (follow_case.n > 0) {
    // 这是根据规则5生成的具体操作代码
    for (int idx = 0; idx < follow_case.n; idx++) {
        follow_case.a[idx] = follow_case.a[idx] * follow_case.a[idx];
    }
}

return follow_case;}

#include <cmath>
#include <cfloat>

int z7check(double result1, double result2) {
    // 浮点数比较的特殊处理
    double epsilon = 1e-5;
    
    // 提取左右操作数（移项后：result1 <= result2）
    double A = result1;
    double B = result2;
    
    // 防御NaN
    if (std::isnan(A) || std::isnan(B)) return 0;
    
    // 处理无穷大情况
    if (std::isinf(A) || std::isinf(B)) {
        if (A <= B) return 1;
        else return 0;
    }
    
    // 计算动态容差
    double tol = epsilon * fmax(1.0, fmax(fabs(A), fabs(B)));
    
    // 带容差的比较判定
    if (A > B + tol) return 0;
    
    // 满足条件
    return 1;
}

TestResult z7runTest(int test_case_id) { // MODIFIED: Return type
    TestCase follow_case = z7Change(test_cases[test_case_id]);
    // 原始调用
    double source = add_two_array_values(test_cases[test_case_id].a, test_cases[test_case_id].i, test_cases[test_case_id].j, test_cases[test_case_id].n); // MODIFIED: Explicit type
    // 变换后调用
    double follow = add_two_array_values(follow_case.a, follow_case.i, follow_case.j, follow_case.n);
    
    int** memory_list = (int**)malloc(1 * sizeof(int*));
    memory_list[0] = follow_case.a;
    
    TestResult test_result;
    test_result.memory_to_free = memory_list;
    test_result.memory_count = 1;
    
    test_result.result2 = follow; // MODIFIED    
    test_result.result1 = source; // MODIFIED
    int status = z7check(source, follow);
    test_result.status = status;
    return test_result; // MODIFIED: Return TestResult
}


int main() {
    srand(time(NULL));
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        TestResult result = z7runTest(i);
        if (result.status == 0) status_end = 0;
        for (int j = 0; j < result.memory_count; j++) {
            free(result.memory_to_free[j]);
        }
        free(result.memory_to_free);  // 释放指针数组本身
    }
    std::cout << status_end << std::endl;
    return 0;
}