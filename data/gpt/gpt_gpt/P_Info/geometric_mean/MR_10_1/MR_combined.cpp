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


double geometric_mean(int a[], int n) {
    long product = 1;
    for (int i = 0; i < n; i++) {
        product *= a[i];
    }
    return pow(product, (double) 1 / n);
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, 3},
    {(int[]){4, 5, 6}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){7, 3, 11, 2, 8}, 5},
    {(int[]){15, 25, 35, 45, 55, 65}, 6},
    {(int[]){9, 13, 17, 19}, 4},
    {(int[]){21, 22, 23, 24, 25}, 5},
    {(int[]){11, 13, 12, 15, 14}, 5},
    {(int[]){2, 11, 7, 9, 5, 10}, 6},
    {(int[]){100, 150, 200}, 3},
    {(int[]){5, 8, 6, 7, 3, 12}, 6},
    {(int[]){3, 17, 29, 101}, 4},
    {(int[]){45, 55, 60, 73, 85}, 5},
    {(int[]){13, 23, 19, 31}, 4},
    {(int[]){19, 7, 22}, 3},
    {(int[]){27, 33, 29, 24}, 4},
    {(int[]){8, 14, 9, 16, 11}, 5},
    {(int[]){2, 4, 6, 8, 10, 12, 14}, 7},
    {(int[]){50, 70, 65, 80}, 4},
    {(int[]){95, 85, 75, 65, 55}, 5},
    {(int[]){28, 39, 47, 35}, 4},
    {(int[]){44, 42, 38, 50}, 4},
    {(int[]){60, 72, 84, 96, 108}, 5},
    {(int[]){18, 29, 41, 37}, 4},
    {(int[]){1, 3, 7, 9, 13}, 5},
    {(int[]){6, 12, 24, 36, 48}, 5},
    {(int[]){16, 32, 64, 128}, 4},
    {(int[]){5, 10, 15, 20, 25, 30}, 6},
    {(int[]){70, 55, 40, 25}, 4},
    {(int[]){33, 44, 55, 66, 77}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for follow-up input to avoid modifying original
    int* new_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_a[i] = tc.a[i];
    }
    // Add 1 to first half elements
    int half = tc.n / 2;
    for (int i = 0; i < half; i++) {
        new_a[i] += 1;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input
    int* Ts = tc.a;
    int n = tc.n;
    // (2) Get source output
    double Os = geometric_mean(Ts, n);
    // (3) Construct follow-up input
    TestCase Tf_case = change(tc);
    // (4) Get follow-up output
    double Of = geometric_mean(Tf_case.a, Tf_case.n);
    // (5) Verify MR: Os < Of
    int is_valid = 0;
    if (Os < Of) {
        is_valid = 1;
    }
    // (6) Free dynamically allocated memory in Tf_case
    if (Tf_case.a != tc.a) {
        delete[] Tf_case.a;
    }
    // (7) Return verification result
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