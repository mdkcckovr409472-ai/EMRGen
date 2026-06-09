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


int* elementwise_min(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }

    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n; i++) {
        result[i] = (a[i] < b[i]) ? a[i] : b[i];  }

    return result;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){-1, -2, -3}, (int[]){-4, -5, -6}, 3},
    {(int[]){10, 20, 30}, (int[]){5, 25, 35}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){100}, (int[]){99}, 1},
    {(int[]){7, 8, 9, 10}, (int[]){6, 7, 8, 9}, 4},
    {(int[]){-10, 0, 10}, (int[]){-5, 5, 15}, 3},
    {(int[]){1, 3, 5}, (int[]){2, 4, 6}, 3},
    {(int[]){2, 4, 6}, (int[]){1, 3, 5}, 3},
    {(int[]){15, 25, 35, 45}, (int[]){20, 30, 40, 50}, 4},
    {(int[]){50, 40, 30, 20}, (int[]){45, 35, 25, 15}, 4},
    {(int[]){-100, 200, -300}, (int[]){-50, 150, -250}, 3},
    {(int[]){999, 888, 777}, (int[]){1000, 889, 776}, 3},
    {(int[]){42}, (int[]){42}, 1},
    {(int[]){1, 2}, (int[]){2, 1}, 2},
    {(int[]){-1, -1, -1, -1}, (int[]){-2, -2, -2, -2}, 4},
    {(int[]){5, 10, 15, 20, 25}, (int[]){4, 11, 14, 21, 24}, 5},
    {(int[]){0, 100, -100}, (int[]){1, 99, -99}, 3},
    {(int[]){6, 7, 8}, (int[]){6, 7, 8}, 3},
    {(int[]){9, 8, 7, 6, 5}, (int[]){10, 7, 8, 5, 6}, 5},
    {(int[]){-7, -8, -9}, (int[]){-6, -9, -10}, 3},
    {(int[]){123, 456, 789}, (int[]){124, 455, 790}, 3},
    {(int[]){11, 22, 33, 44, 55, 66}, (int[]){12, 21, 34, 43, 56, 65}, 6},
    {(int[]){2, 3, 5, 7, 11}, (int[]){1, 4, 6, 8, 13}, 5},
    {(int[]){1000, 2000, 3000}, (int[]){500, 2500, 3500}, 3},
    {(int[]){-20, -10, 0, 10, 20}, (int[]){-15, -5, 5, 15, 25}, 5},
    {(int[]){4, 4, 4}, (int[]){5, 5, 5}, 3},
    {(int[]){19, 28, 37, 46}, (int[]){21, 26, 39, 44}, 4},
    {(int[]){51, 62, 73}, (int[]){49, 64, 71}, 3},
    {(int[]){8, 6, 4, 2, 0}, (int[]){9, 5, 3, 1, -1}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 交换 a 和 b 数组指针
    int* temp = tf.a;
    tf.a = tf.b;
    tf.b = temp;
    return tf;
}

int check(TestCase tc) {
    // 获取初始输出 Os
    int* Os = elementwise_min(tc.a, tc.b, tc.n);
    if (Os == NULL) {
        return 0;
    }

    // 构造衍生用例
    TestCase Tf_case = change(tc);

    // 获取衍生输出 Of
    int* Of = elementwise_min(Tf_case.a, Tf_case.b, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        return 0;
    }

    // 验证 Os 和 Of 是否相等
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }

    // 释放动态内存
    free(Os);
    free(Of);
    // 注意：Tf_case 只是交换了指针，没有分配新内存，无需释放其 a 和 b

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