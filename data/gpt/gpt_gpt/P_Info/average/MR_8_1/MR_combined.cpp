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


double average(int a[], int n){
    double suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += a[i];
    }
    return suma/n;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){4, 1, 5, 2, 3}, 5},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){10, -10, 10, -10}, 4},
    {(int[]){100, 200, 50}, 3},
    {(int[]){-5, 0, 5}, 3},
    {(int[]){7}, 1},
    {(int[]){-100, 50, -30, 20, -10}, 5},
    {(int[]){3, 3, 2, 2, 1, 1}, 6},
    {(int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 9},
    {(int[]){-3, -1, -4, -2, -5}, 5},
    {(int[]){2, -2, 2, -2, 2}, 5},
    {(int[]){15, 0, -15, 30, -30}, 5},
    {(int[]){1, 1, 1, 2, 2, 2, 3, 3, 3}, 9},
    {(int[]){1000, -1000}, 2},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, 7},
    {(int[]){4, 4, 4, 4, 4, 4, 4, 4}, 8},
    {(int[]){-7, 14, -21, 28, -35}, 5},
    {(int[]){0, 1, 0, 1, 0, 1}, 6},
    {(int[]){-9, -8, -7, -6, -5, -4, -3, -2, -1}, 9},
    {(int[]){12, -12, 0, 24, -24}, 5},
    {(int[]){10, 5, 15, 0, 20, 25}, 6},
    {(int[]){-2, -4, -6, -8, -10}, 5},
    {(int[]){3, -3, 6, -6, 9, -9}, 6},
    {(int[]){1, 0, -1, 0, 1}, 5},
    {(int[]){16, 2, 64, 8, 32, 4}, 6},
    {(int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}, 11},
    {(int[]){35, 7, 42, 14, 49, 21, 28}, 7},
    {(int[]){-100, -50, 0, 50, 100}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc; 
    if (tf.n <= 0 || tf.a == nullptr) return tf;

    // Reuse the original array pointer but create a new array since we need to modify the first element 
    int* new_a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_a[i] = tf.a[i];
    }

    // Find max value in original array
    int max_val = new_a[0];
    for (int i = 1; i < tf.n; i++) {
        if (new_a[i] > max_val) {
            max_val = new_a[i];
        }
    }

    // Set the first element to the max value
    new_a[0] = max_val;
    tf.a = new_a;

    return tf;
}

int check(TestCase tc) {
    if (tc.n <= 0 || tc.a == nullptr) return 0;

    // Get source output Os
    double Os = average(tc.a, tc.n);

    // Get follow-up test case Tf
    TestCase Tf_case = change(tc);
    if (Tf_case.a == nullptr) return 0;

    // Get follow-up output Of
    double Of = average(Tf_case.a, Tf_case.n);

    // Check metamorphic relation Of >= Os
    int is_valid = (Of >= Os) ? 1 : 0;

    // Free dynamically allocated array in Tf_case if it differs from original
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