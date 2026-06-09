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
    {(int[]){1, 2, 3}, 2, 3},
    {(int[]){4, 5, 6}, 1, 3},
    {(int[]){7, 7, 7}, 7, 3},
    {(int[]){}, 0, 0},
    {(int[]){-1, -2, -3, -2}, -2, 4},
    {(int[]){-5, 0, 5, 0, 5}, 5, 5},
    {(int[]){2, 2, 2, 2}, 3, 4},
    {(int[]){9, 1, 2, 3, 9}, 9, 5},
    {(int[]){0, 1, 0, 2, 3}, 0, 5},
    {(int[]){4, 4, 5, 5, 6}, 7, 5},
    {(int[]){1, 3, 5, 7, 9, 1, 3, 5}, 5, 8},
    {(int[]){8}, 8, 1},
    {(int[]){9}, 8, 1},
    {(int[]){2, 3, 2, 4, 2, 5}, 2, 6},
    {(int[]){10, 20, 30, 40}, 5, 4},
    {(int[]){-3, -3, 0, 1}, -3, 4},
    {(int[]){6, 6}, 6, 2},
    {(int[]){6, 7}, 8, 2},
    {(int[]){10, 9, 8, 7, 6, 5}, 10, 6},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6}, 1, 8},
    {(int[]){0, 0, 0, 0}, 0, 4},
    {(int[]){-1, 2, -3, 4, -5}, 0, 5},
    {(int[]){5, 5, 5, 5, 5, 5, 5}, 5, 7},
    {(int[]){1, 2, 3, 4, 5}, 3, 5},
    {(int[]){-2, 0, 2, 0, -2}, 0, 5},
    {(int[]){8, 6, 7, 5, 3, 0, 9, 1, 2}, 7, 9},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9}, 10, 9},
    {(int[]){2, 2, 3, 2, 4, 2, 5}, 2, 7},
    {(int[]){-4}, 4, 1},
    {(int[]){1, 0, 1, 0, 1, 0}, 1, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tc.n > 1) {
        int* shifted = new int[tc.n];
        shifted[0] = tc.a[tc.n - 1];
        for (int i = 1; i < tc.n; i++) {
            shifted[i] = tc.a[i - 1];
        }
        tf.a = shifted;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = count_k(tc.a, tc.k, tc.n);
    TestCase tf = change(tc);
    int Of = count_k(tf.a, tf.k, tf.n);
    int is_valid = (Os == Of) ? 1 : 0;
    if (tf.a != tc.a) {
        delete[] tf.a;
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