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


double manhattan_dist(int a[], int b[], int n) {
    int i;
    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += abs(a[i] - b[i]);
    }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){1}, (int[]){2}, 1},
    {(int[]){-1}, (int[]){1}, 1},
    {(int[]){5}, (int[]){5}, 1},
    {(int[]){10}, (int[]){-10}, 1},
    {(int[]){1, 2}, (int[]){3, 4}, 2},
    {(int[]){-1, -2}, (int[]){-3, -4}, 2},
    {(int[]){0, 0}, (int[]){0, 0}, 2},
    {(int[]){100, 200}, (int[]){50, 150}, 2},
    {(int[]){-5, 10}, (int[]){5, -10}, 2},
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){-1, -2, -3}, (int[]){-4, -5, -6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){10, 20, 30}, (int[]){5, 15, 25}, 3},
    {(int[]){1, -1, 2}, (int[]){-1, 1, -2}, 3},
    {(int[]){1, 2, 3, 4}, (int[]){5, 6, 7, 8}, 4},
    {(int[]){-1, -2, -3, -4}, (int[]){-5, -6, -7, -8}, 4},
    {(int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0}, 4},
    {(int[]){100, 200, 300, 400}, (int[]){50, 150, 250, 350}, 4},
    {(int[]){1, 0, -1, 2}, (int[]){0, 1, 2, -1}, 4},
    {(int[]){1, 2, 3, 4, 5}, (int[]){6, 7, 8, 9, 10}, 5},
    {(int[]){-1, -2, -3, -4, -5}, (int[]){-6, -7, -8, -9, -10}, 5},
    {(int[]){0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){5, -5, 10, -10, 15}, (int[]){-5, 5, -10, 10, -15}, 5},
    {(int[]){1, 2, 3, 4, 5, 6}, (int[]){7, 8, 9, 10, 11, 12}, 6},
    {(int[]){-1, -2, -3, -4, -5, -6}, (int[]){-7, -8, -9, -10, -11, -12}, 6},
    {(int[]){0, 0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0, 0}, 6},
    {(int[]){10, 20, 30, 40, 50, 60}, (int[]){5, 15, 25, 35, 45, 55}, 6},
    {(int[]){1, 0, 2, 0, 3, 0}, (int[]){0, 1, 0, 2, 0, 3}, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 根据 MR 规则，将数组 a 的第 i 个元素设置为 b[i]
    // 这里选择 i = 0 作为示例，也可以根据需求修改为其他索引
    int i = 0;
    if (tf.n > i) {
        tf.a[i] = tf.b[i];
    }
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts) 并计算初始输出 (Os)
    double Os = manhattan_dist(tc.a, tc.b, tc.n);
    
    // (2) 构造衍生用例
    TestCase Tf_case = change(tc);
    
    // (3) 提取衍生输入并计算衍生输出 (Of)
    double Of = manhattan_dist(Tf_case.a, Tf_case.b, Tf_case.n);
    
    // (4) 验证蜕变关系 Os >= Of
    int is_valid = 0;
    if (Os >= Of) {
        is_valid = 1;
    }
    
    // (5) 释放动态内存
    // 由于 TestCase 结构体中的指针是浅拷贝，且原始用例 tc 由外部管理，
    // 这里只需要确保没有在 change 函数中为 Tf_case 分配新的数组。
    // 如果 change 函数中分配了新数组，则需要在此释放。
    // 根据当前 change 实现，没有分配新内存，因此无需额外释放。
    
    // (6) 返回验证结果
    return is_valid;
}

int main() {
    int status_end = 1;
    for (int i = 0; i < num_test_cases; i++) {
        int is_valid = check(test_cases[i]);
        if (is_valid == 0) {
            status_end = 0; 
        }
    }
    std::cout << status_end << std::endl;
    return 0;
}