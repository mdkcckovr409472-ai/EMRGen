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


int sum(int values[],  int n) {
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += values[i];
}
    return sum;
}


typedef struct {
    int* values; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 3},
    {(int[]){0}, 1},
    {(int[]){-1, 1}, 2},
    {(int[]){10, 20, 30, 40, 50}, 5},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){100}, 1},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){1, -1, 2, -2, 3, -3}, 6},
    {(int[]){2147483647, 0, -2147483648}, 3},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){5}, 1},
    {(int[]){2, 4, 6, 8}, 4},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){100, 200, 300}, 3},
    {(int[]){15, 25, 35, 45}, 4},
    {(int[]){-100, 100, -200, 200}, 4},
    {(int[]){0, 10, 0, 20, 0}, 5},
    {(int[]){1, 0, 0, 0, 1}, 5},
    {(int[]){-7, 8, -9, 10}, 4},
    {(int[]){50, 60, 70, 80, 90, 100}, 6},
    {(int[]){-50, -60, -70}, 3},
    {(int[]){12, 24, 36}, 3},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7},
    {(int[]){-2, 4, -6, 8, -10}, 5},
    {(int[]){999, -999, 1000, -1000}, 4},
    {(int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
    {(int[]){-15, -25, -35, -45, -55}, 5},
    {(int[]){42}, 1},
    {(int[]){6, 12, 18, 24, 30, 36}, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0) {
        int index = 0; // 选择第一个元素进行增加操作
        int k = 5; // 增加的值，可调整
        tf.values = new int[tf.n];
        for (int i = 0; i < tf.n; i++) {
            tf.values[i] = tc.values[i];
        }
        tf.values[index] += k;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = sum(tc.values, tc.n);
    TestCase Tf_case = change(tc);
    int Of = sum(Tf_case.values, Tf_case.n);
    int k = 5;
    int is_valid = 0;
    if (Os + k == Of) {
        is_valid = 1;
    }
    if (Tf_case.values != tc.values) {
        delete[] Tf_case.values;
    }
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