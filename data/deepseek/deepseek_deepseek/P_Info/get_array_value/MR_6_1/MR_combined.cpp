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


int get_array_value(int a[], int k, int n) {
        return a[k - 1];
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){10, 20, 30, 40, 50}, 1, 5},
    {(int[]){10, 20, 30, 40, 50}, 3, 5},
    {(int[]){10, 20, 30, 40, 50}, 5, 5},
    {(int[]){7}, 1, 1},
    {(int[]){-1, 0, 1}, 1, 3},
    {(int[]){-1, 0, 1}, 2, 3},
    {(int[]){-1, 0, 1}, 3, 3},
    {(int[]){100, 200, 300, 400}, 2, 4},
    {(int[]){100, 200, 300, 400}, 4, 4},
    {(int[]){5, 4, 3, 2, 1}, 1, 5},
    {(int[]){5, 4, 3, 2, 1}, 5, 5},
    {(int[]){0, 0, 0, 0}, 2, 4},
    {(int[]){15, 25, 35}, 1, 3},
    {(int[]){15, 25, 35}, 2, 3},
    {(int[]){15, 25, 35}, 3, 3},
    {(int[]){2, 4, 6, 8, 10, 12}, 3, 6},
    {(int[]){2, 4, 6, 8, 10, 12}, 6, 6},
    {(int[]){-10, -20, -30}, 1, 3},
    {(int[]){-10, -20, -30}, 3, 3},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 4, 7},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7, 7},
    {(int[]){42}, 1, 1},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 1, 7},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 4, 7},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 7, 7},
    {(int[]){1000, 2000, 3000}, 2, 3},
    {(int[]){-5, -3, -1, 1, 3, 5}, 3, 6},
    {(int[]){-5, -3, -1, 1, 3, 5}, 5, 6},
    {(int[]){9, 8, 7, 6, 5}, 2, 5},
    {(int[]){9, 8, 7, 6, 5}, 5, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int m = 2;
    for (int i = 0; i < tf.n; ++i) {
        if (i != tf.k - 1) {
            tf.a[i] *= m;
        }
    }
    return tf;
}

int check(TestCase tc) {
    int Os = get_array_value(tc.a, tc.k, tc.n);
    TestCase Tf_case = change(tc);
    int Of = get_array_value(Tf_case.a, Tf_case.k, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
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