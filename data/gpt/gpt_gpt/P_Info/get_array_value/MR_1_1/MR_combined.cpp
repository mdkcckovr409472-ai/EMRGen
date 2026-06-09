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
    {(int[]){5}, 1, 1},
    {(int[]){0, -1, 2}, 2, 3},
    {(int[]){3, 3, 3, 3}, 4, 4},
    {(int[]){-5, 10, -2, 7}, 3, 4},
    {(int[]){1, 2, 3, 4, 5}, 5, 5},
    {(int[]){9, 1, 8, 2, 7, 3}, 2, 6},
    {(int[]){0, 0, 0, 0, 0}, 4, 5},
    {(int[]){-3, 4, -1, 6, -2}, 1, 5},
    {(int[]){2, -2, 2, -2, 2}, 5, 5},
    {(int[]){8, -7, 6, -5, 4, -3, 2, -1}, 8, 8},
    {(int[]){100, -100, 50, -50}, 3, 4},
    {(int[]){7, 7, 5, 5, 3, 3, 1, 1}, 6, 8},
    {(int[]){1, -1, 1, -1, 1}, 2, 5},
    {(int[]){4, 2, 0, -2, -4}, 4, 5},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 9, 9},
    {(int[]){5, -3, 9, -8, 2}, 3, 5},
    {(int[]){0}, 1, 1},
    {(int[]){-10, 10, -9, 9, -8, 8}, 5, 6},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6, 5}, 7, 9},
    {(int[]){2, 4, 8, 16, 32}, 4, 5},
    {(int[]){1, 0, -1, 0, 1}, 5, 5},
    {(int[]){6, -6, 6, -6, 6, -6}, 2, 6},
    {(int[]){5, -4, 3, -2, 1, 0, -1, 2, -3, 4}, 10, 10},
    {(int[]){7, 2, -5, 3, -1}, 3, 5},
    {(int[]){0, 1, 0, 1, 0, 1}, 6, 6},
    {(int[]){9, -9, 8, -8, 7, -7}, 1, 6},
    {(int[]){3, -3, 3, -3, 3}, 4, 5},
    {(int[]){2, 5, 2, 5, 2, 5, 2}, 7, 7},
    {(int[]){1, 2, 3, 2, 1}, 2, 5},
    {(int[]){4, -2, 0, 2, -4}, 5, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for tf.a to add 1 to all elements
    tf.a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        tf.a[i] = tc.a[i] + 1;
    }
    return tf;
}

int check(TestCase tc) {
    // Source input
    int* Ts = tc.a;
    int k = tc.k;
    int n = tc.n;
    // Source output
    int Os = get_array_value(Ts, k, n);

    // Follow-up test case
    TestCase Tf_case = change(tc);
    int* Tf = Tf_case.a;
    // Follow-up output
    int Of = get_array_value(Tf, k, n);

    int is_valid = 0;
    if (Os + 1 == Of) {
        is_valid = 1;
    }

    // Cleanup dynamically allocated memory in Tf_case.a if different from original
    if (Tf_case.a != tc.a) {
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