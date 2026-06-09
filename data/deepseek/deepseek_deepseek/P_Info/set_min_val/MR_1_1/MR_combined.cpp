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


int* set_min_val(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        if (cp1[i] < k) {
            cp1[i] = k;
        }
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3, 4, 5}, 3, 5},
    {(int[]){5, 4, 3, 2, 1}, 2, 5},
    {(int[]){10, 20, 30}, 25, 3},
    {(int[]){-10, -5, 0, 5, 10}, 0, 5},
    {(int[]){7, 7, 7, 7}, 7, 4},
    {(int[]){100}, 50, 1},
    {(int[]){15, 25, 35, 45}, 30, 4},
    {(int[]){0, 1, 2, 3, 4, 5}, 3, 6},
    {(int[]){-3, -2, -1}, -1, 3},
    {(int[]){8, 6, 4, 2}, 5, 4},
    {(int[]){12, 24, 36, 48, 60}, 40, 5},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 5, 9},
    {(int[]){-20, -10, 0, 10, 20}, -5, 5},
    {(int[]){2, 4, 6, 8, 10, 12}, 7, 6},
    {(int[]){99, 101}, 100, 2},
    {(int[]){50, 60, 70, 80, 90}, 65, 5},
    {(int[]){-1, -1, -1, -1}, -2, 4},
    {(int[]){3, 1, 4, 1, 5, 9}, 2, 6},
    {(int[]){11, 22, 33, 44, 55, 66, 77}, 40, 7},
    {(int[]){6, 7, 8, 9, 10}, 8, 5},
    {(int[]){-50, -25, 0, 25, 50}, 10, 5},
    {(int[]){19, 28, 37, 46}, 30, 4},
    {(int[]){13, 26, 39, 52}, 35, 4},
    {(int[]){0, 0, 0, 0, 0}, 1, 5},
    {(int[]){100, 200, 300, 400}, 250, 4},
    {(int[]){5, 10, 15, 20, 25, 30}, 12, 6},
    {(int[]){-8, -4, 0, 4, 8}, 0, 5},
    {(int[]){14, 21, 28, 35, 42}, 25, 5},
    {(int[]){17, 34, 51, 68}, 40, 4},
    {(int[]){9, 18, 27, 36, 45, 54}, 20, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 为数组 a 的每个元素加1，构造衍生输入
    for (int i = 0; i < tf.n; ++i) {
        tf.a[i] += 1;
    }
    return tf;
}

int check(TestCase tc) {
    // 获取初始输出 Os
    int* Os = set_min_val(tc.a, tc.k, tc.n);
    
    // 构造衍生用例
    TestCase Tf_case = change(tc);
    // 获取衍生输出 Of
    int* Of = set_min_val(Tf_case.a, Tf_case.k, Tf_case.n);
    
    int is_valid = 1;
    // 验证 Os <= Of (每个元素)
    for (int i = 0; i < tc.n; ++i) {
        if (Os[i] > Of[i]) {
            is_valid = 0;
            break;
        }
    }
    
    // 释放动态内存
    free(Os);
    free(Of);
    // 注意：tc.a 和 Tf_case.a 指向同一块内存，由调用者管理，此处不释放
    
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