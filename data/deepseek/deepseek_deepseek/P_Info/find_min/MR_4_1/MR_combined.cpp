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


int find_min(int a[], int n) {
    int min = a[0];
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40, 50}, 5},
    {(int[]){50, 40, 30, 20, 10}, 5},
    {(int[]){0, 0, 0}, 3},
    {(int[]){100}, 1},
    {(int[]){-5, -10, -3}, 3},
    {(int[]){-10, -5, -3}, 3},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){12, 10, 8, 6, 4, 2}, 6},
    {(int[]){7, 3, 9, 1, 5}, 5},
    {(int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){-2, 4, -6, 8, -10}, 5},
    {(int[]){15, 11, 19, 14, 16}, 5},
    {(int[]){100, 200, 150}, 3},
    {(int[]){0, -1, -2, -3}, 4},
    {(int[]){-3, -2, -1, 0}, 4},
    {(int[]){42}, 1},
    {(int[]){6, 2, 8, 4, 10}, 5},
    {(int[]){10, 4, 8, 2, 6}, 5},
    {(int[]){-7, -7, -7}, 3},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9}, 9},
    {(int[]){13, 17, 12, 19, 11}, 5},
    {(int[]){25, 50, 75}, 3},
    {(int[]){-100, -50, -200}, 3},
    {(int[]){8, 3, 8, 1, 8}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0) {
        tf.a = new int[tf.n];
        for (int i = 0; i < tc.n; i++) {
            tf.a[i] = tc.a[tc.n - 1 - i];
        }
    }
    return tf;
}

int check(TestCase tc) {
    int Os = find_min(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = find_min(Tf_case.a, Tf_case.n);
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