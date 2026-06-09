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


int count_non_zeroes(int a[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            cnt++;
        }
    }
    return cnt;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){1, 0, 0, 0, 0}, 5},
    {(int[]){0, 0, 0, 0, 1}, 5},
    {(int[]){0, 1, 0, 1, 0}, 5},
    {(int[]){1, 2, 0, 4, 5}, 5},
    {(int[]){-1, -2, -3, 0, 0}, 5},
    {(int[]){0, 0, 10, 20, 30}, 5},
    {(int[]){1}, 1},
    {(int[]){0}, 1},
    {(int[]){}, 0},
    {(int[]){1, 2, 3}, 3},
    {(int[]){0, 0, 0}, 3},
    {(int[]){1, 0, 3}, 3},
    {(int[]){-5, 0, 5}, 3},
    {(int[]){100, 200, 300}, 3},
    {(int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
    {(int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10},
    {(int[]){1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10},
    {(int[]){1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, 10},
    {(int[]){2, 4, 6, 8, 0, 10, 12}, 7},
    {(int[]){-1, 0, -2, 0, -3}, 5},
    {(int[]){7, 0, 0, 8, 0, 9}, 6},
    {(int[]){15}, 1},
    {(int[]){0, 0, 1}, 3},
    {(int[]){1, 2, 0, 0, 5, 0, 7}, 7},
    {(int[]){0, 0, 0, 1, 0, 0, 0, 1}, 8},
    {(int[]){3, 6, 9, 12, 15, 18}, 6},
    {(int[]){0, 20, 0, 40, 0, 60, 0, 80, 0, 100}, 10},
    {(int[]){11, 0, 13, 0, 0, 16, 17, 0, 19, 0}, 10}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 分配新数组用于打乱
    int* shuffled_array = new int[tc.n];
    // 复制原始数据
    for (int i = 0; i < tc.n; i++) {
        shuffled_array[i] = tc.a[i];
    }
    // 使用 std::random_shuffle 打乱数组
    // 注意：为了使用 std::random_shuffle，需要包含 <algorithm> 和 <random>
    // 这里使用一个简单的 Fisher-Yates 洗牌算法实现
    std::srand(std::time(0)); // 使用当前时间作为随机种子
    for (int i = tc.n - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(shuffled_array[i], shuffled_array[j]);
    }
    tf.a = shuffled_array;
    // 注意：tf.n 保持不变，因为数组大小未变
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts)
    int* Ts_a = tc.a;
    int Ts_n = tc.n;
    
    // (2) 调用待测函数，获取初始输出 (Os)
    int Os = count_non_zeroes(Ts_a, Ts_n);
    
    // (3) 调用 change 函数，构造衍生用例对象
    TestCase Tf_case = change(tc);
    
    // (4) 提取衍生输入并获取衍生输出 (Of)
    int* Tf_a = Tf_case.a;
    int Tf_n = Tf_case.n;
    int Of = count_non_zeroes(Tf_a, Tf_n);
    
    // (5) 根据 MR 验证 Os 和 Of 是否满足蜕变关系
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    
    // (6) 释放 Tf_case 中产生的动态内存
    // 注意：Tf_case.a 指向的是 change 函数中 new 分配的内存
    if (Tf_case.a != tc.a) { // 确保不是指向原始数组
        delete[] Tf_case.a;
    }
    
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