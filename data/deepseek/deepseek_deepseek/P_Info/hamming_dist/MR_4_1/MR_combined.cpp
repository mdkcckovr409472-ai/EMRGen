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


int hamming_dist(int a[], int b[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            cnt++;
        }
    }
    return cnt;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0}, 4},
    {(int[]){1, 2, 3, 4}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){1, 0, 1, 0}, (int[]){0, 1, 0, 1}, 4},
    {(int[]){5, 10, 15}, (int[]){5, 10, 15}, 3},
    {(int[]){-1, -2, -3}, (int[]){-1, -2, -3}, 3},
    {(int[]){100, 200}, (int[]){100, 201}, 2},
    {(int[]){7, 8, 9}, (int[]){7, 8, 10}, 3},
    {(int[]){1}, (int[]){2}, 1},
    {(int[]){0, 1, 0, 1, 0}, (int[]){1, 0, 1, 0, 1}, 5},
    {(int[]){10, 20, 30, 40}, (int[]){11, 20, 30, 40}, 4},
    {(int[]){-5, 0, 5}, (int[]){-5, 0, 6}, 3},
    {(int[]){2, 4, 6, 8, 10}, (int[]){2, 4, 6, 8, 10}, 5},
    {(int[]){1, 3, 5, 7}, (int[]){1, 3, 6, 7}, 4},
    {(int[]){0, 0, 0}, (int[]){1, 1, 1}, 3},
    {(int[]){12, 24, 36}, (int[]){13, 24, 36}, 3},
    {(int[]){9, 8, 7, 6}, (int[]){9, 8, 7, 5}, 4},
    {(int[]){-10, -20}, (int[]){-10, -21}, 2},
    {(int[]){100, 101, 102}, (int[]){100, 101, 102}, 3},
    {(int[]){1, 2, 3, 4, 5, 6}, (int[]){1, 2, 3, 4, 5, 7}, 6},
    {(int[]){0, 0, 1, 1}, (int[]){0, 1, 0, 1}, 4},
    {(int[]){50, 60, 70, 80, 90}, (int[]){50, 60, 70, 80, 90}, 5},
    {(int[]){-1, -1, -1}, (int[]){-1, -1, -2}, 3},
    {(int[]){3, 6, 9, 12}, (int[]){3, 6, 9, 13}, 4},
    {(int[]){255, 128, 64}, (int[]){255, 128, 63}, 3},
    {(int[]){1, 1, 1, 1, 1}, (int[]){1, 1, 1, 1, 1}, 5},
    {(int[]){42}, (int[]){42}, 1},
    {(int[]){0, 10, 20, 30}, (int[]){0, 10, 21, 30}, 4},
    {(int[]){-100, 0, 100}, (int[]){-100, 0, 100}, 3},
    {(int[]){8, 7, 6, 5, 4, 3, 2, 1}, (int[]){8, 7, 6, 5, 4, 3, 2, 0}, 8},
    {(int[]){99, 98, 97}, (int[]){99, 98, 97}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 需要为衍生用例分配新的数组，因为原数组内容需要被修改
    // 但根据约束1，我们复用传入结构体的数据指针，所以这里需要深拷贝a数组
    // 因为原函数不修改数组，但我们的MR操作需要修改a数组的一个元素。
    // 我们将分配新内存并复制数据，然后修改一个元素。
    // 寻找一个位置i，使得 a[i] == b[i]，然后修改 a[i] 使其不等于 b[i]。
    // 如果找不到这样的位置，我们需要处理（例如，将所有元素设为不同，但根据MR描述，我们假设存在）。
    // 为了简单和确定性，我们找到第一个满足 a[i] == b[i] 的位置。
    int* new_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_a[i] = tc.a[i];
    }
    int idx_to_change = -1;
    for (int i = 0; i < tc.n; i++) {
        if (new_a[i] == tc.b[i]) {
            idx_to_change = i;
            break;
        }
    }
    // 如果找到了，修改它，使其不等于 b[i]
    if (idx_to_change != -1) {
        // 简单修改：如果 b[i] 是某个值，我们加1。需要考虑溢出，但这里假设为示例。
        new_a[idx_to_change] = tc.b[idx_to_change] + 1;
    } else {
        // 如果没有找到 a[i] == b[i] 的位置，根据MR描述无法执行操作。
        // 但为了函数完整性，我们不做修改（或者可以抛出异常，但这里简单处理）。
        // 实际上，这种初始用例可能不适用于此MR，但框架可能仍会调用。
        // 我们选择不做任何改变。
    }
    tf.a = new_a;
    // tf.b 和 tf.n 保持不变，直接复用
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts)
    // Ts 就是 tc 本身
    // (2) 获取初始输出 Os
    int Os = hamming_dist(tc.a, tc.b, tc.n);
    // (3) 构造衍生用例
    TestCase Tf_case = change(tc);
    // (4) 获取衍生输出 Of
    int Of = hamming_dist(Tf_case.a, Tf_case.b, Tf_case.n);
    // (5) 验证蜕变关系 Of == Os + 1
    int is_valid = 0;
    if (Of == Os + 1) {
        is_valid = 1;
    }
    // (6) 释放动态内存：Tf_case 中我们分配了新的 a 数组
    delete[] Tf_case.a;
    // 注意：我们不应该删除 tc.a，因为它不是我们分配的。
    // Tf_case.b 指向的是 tc.b，所以也不应该删除。
    // (7) 返回结果
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