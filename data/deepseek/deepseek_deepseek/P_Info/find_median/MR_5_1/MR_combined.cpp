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


double find_median(int a[], int n) {
    int k = n / 2 + 1;
    int minIndex = 0;
    int minValue = a[0];
    for (int i = 0; i < k; i++) {
        minIndex = i;
        minValue = a[i];
        for (int j = i + 1; j < n; j++) {
            if (a[j] < minValue) {
                minIndex = j;
                minValue = a[j];
            }
        }
        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
    if (n % 2 == 0) {
        return (double) (a[n / 2 - 1] + a[n / 2]) / 2;
    } else {
        return a[n / 2];
    }
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 1, 2}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){1, 3, 2}, 3},
    {(int[]){1, 2, 3, 4}, 4},
    {(int[]){4, 3, 2, 1}, 4},
    {(int[]){2, 4, 1, 3}, 4},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){3, 5, 1, 4, 2}, 5},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){40, 10, 30, 20}, 4},
    {(int[]){7, 7, 7, 7, 7}, 5},
    {(int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){6, 5, 4, 3, 2, 1}, 6},
    {(int[]){2, 1, 4, 3, 6, 5}, 6},
    {(int[]){100, 200, 300}, 3},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 9},
    {(int[]){15, 25, 10, 30, 20}, 5},
    {(int[]){1, 2, 3, 4, 5, 6, 7}, 7},
    {(int[]){7, 6, 5, 4, 3, 2, 1}, 7},
    {(int[]){4, 2, 5, 1, 3, 6}, 6},
    {(int[]){8, 3, 9, 2, 7, 1}, 6},
    {(int[]){12, 15, 18, 21}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* arr_copy = new int[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        arr_copy[i] = tc.a[i];
    }
    tf.a = arr_copy;
    tf.n = tc.n;
    for (int i = 0; i < tf.n - 1; ++i) {
        for (int j = i + 1; j < tf.n; ++j) {
            if (tf.a[i] < tf.a[j]) {
                int temp = tf.a[i];
                tf.a[i] = tf.a[j];
                tf.a[j] = temp;
            }
        }
    }
    return tf;
}

int check(TestCase tc) {
    int* arr_copy_initial = new int[tc.n];
    for (int i = 0; i < tc.n; ++i) {
        arr_copy_initial[i] = tc.a[i];
    }
    double Os = find_median(arr_copy_initial, tc.n);
    delete[] arr_copy_initial;
    TestCase Tf_case = change(tc);
    double Of = find_median(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    delete[] Tf_case.a;
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