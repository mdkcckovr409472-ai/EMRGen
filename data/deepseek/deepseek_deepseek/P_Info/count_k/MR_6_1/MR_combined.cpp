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


int count_k(int a[], int k, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == k) {
            cnt++;
        }
    }
    return cnt;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 3, 5},
    {(int[]){10, 20, 30}, 10, 3},
    {(int[]){5, 5, 5, 5}, 5, 4},
    {(int[]){0, 0, 0}, 0, 3},
    {(int[]){-1, -2, -3, -1}, -1, 4},
    {(int[]){100}, 100, 1},
    {(int[]){7, 8, 9}, 1, 3},
    {(int[]){}, 0, 0},
    {(int[]){15, 25, 35, 45}, 25, 4},
    {(int[]){2, 4, 6, 8, 10, 2, 4}, 2, 7},
    {(int[]){1, 1, 2, 2, 3, 3}, 2, 6},
    {(int[]){-5, 0, 5, 10}, 5, 4},
    {(int[]){99, 99, 99}, 99, 3},
    {(int[]){12, 24, 36, 48}, 60, 4},
    {(int[]){3, 6, 9, 12, 15}, 9, 5},
    {(int[]){0, 1, 2, 3, 4, 5}, 3, 6},
    {(int[]){8, 8, 8, 8, 8}, 8, 5},
    {(int[]){-10, -20, -30, -40}, -20, 4},
    {(int[]){42}, 42, 1},
    {(int[]){1, 3, 5, 7, 9, 11}, 7, 6},
    {(int[]){6, 7, 8, 9, 10}, 6, 5},
    {(int[]){50, 51, 52, 53, 54, 55}, 55, 6},
    {(int[]){0, 0, 1, 1, 2, 2}, 1, 6},
    {(int[]){100, 200, 300, 400}, 500, 4},
    {(int[]){9, 8, 7, 6, 5}, 7, 5},
    {(int[]){-3, -2, -1, 0, 1, 2}, 0, 6},
    {(int[]){11, 22, 33, 44, 55}, 33, 5},
    {(int[]){4, 5, 6, 4, 5, 6}, 4, 6},
    {(int[]){20, 40, 60, 80}, 40, 4},
    {(int[]){1, 2, 3, 1, 2, 3, 1, 2, 3}, 2, 9}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 为衍生输入数组分配新的内存，复制初始数组
    tf.a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.a[i] = tc.a[i];
        // 执行「将所有等于k-1的元素修改为k」操作
        if (tf.a[i] == tc.k - 1) {
            tf.a[i] = tc.k;
        }
    }
    // 注意：k和n字段保持不变
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts)
    // tc 本身就是 Ts
    // (2) 获取初始输出 (Os)
    int Os = count_k(tc.a, tc.k, tc.n);
    
    // (3) 构造衍生用例对象
    TestCase Tf_case = change(tc);
    
    // (4) 获取衍生输出 (Of)
    int Of = count_k(Tf_case.a, Tf_case.k, Tf_case.n);
    
    // (5) 验证蜕变关系 Os <= Of
    int is_valid = 0;
    if (Os <= Of) {
        is_valid = 1;
    }
    
    // (6) 释放 change 函数中为衍生数组分配的内存
    delete[] Tf_case.a;
    
    // (7) 返回验证结果
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