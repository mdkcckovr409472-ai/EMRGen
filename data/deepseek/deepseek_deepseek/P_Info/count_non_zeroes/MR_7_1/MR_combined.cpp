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
    if (tf.n > 1 && tf.a != nullptr) {
        int k = 1; // 循环左移1位
        int* new_a = new int[tf.n];
        for (int i = 0; i < tf.n; i++) {
            new_a[i] = tf.a[(i + k) % tf.n];
        }
        tf.a = new_a;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = count_non_zeroes(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = count_non_zeroes(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    if (Tf_case.a != tc.a && Tf_case.a != nullptr) {
        delete[] Tf_case.a;
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