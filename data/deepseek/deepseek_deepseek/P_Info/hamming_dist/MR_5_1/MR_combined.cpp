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
    tf.b = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.b[i] = tc.b[i];
    }
    for (int i = 0; i < tc.n; i++) {
        if (tc.a[i] != tc.b[i]) {
            tf.b[i] = tc.a[i];
            break;
        }
    }
    return tf;
}

int check(TestCase tc) {
    int Os = hamming_dist(tc.a, tc.b, tc.n);
    TestCase Tf_case = change(tc);
    int Of = hamming_dist(Tf_case.a, Tf_case.b, Tf_case.n);
    int is_valid = 0;
    if (Of == Os - 1) {
        is_valid = 1;
    }
    delete[] Tf_case.b;
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