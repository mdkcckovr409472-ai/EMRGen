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
    {(int[]){5}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){3, 1, 2}, 3},
    {(int[]){4, 3, 2, 1}, 4},
    {(int[]){0, -1, 5, 3, 2}, 5},
    {(int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){7, -3, 2, 2, 5, -1, 0}, 7},
    {(int[]){10, -10, 5, -5, 0, 3, -2, 1}, 8},
    {(int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3}, 9},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, 10},
    {(int[]){9, -9, 0}, 3},
    {(int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){0, 0, 1, 1}, 4},
    {(int[]){-3, 5, -1, 4, -2, 3}, 6},
    {(int[]){8, 7, 6, 5, 4, 3, 2}, 7},
    {(int[]){0, 0}, 2},
    {(int[]){-2, 4, -1, 3, 0}, 5},
    {(int[]){1, -1, 2, -2, 3, -3, 4, -4}, 8},
    {(int[]){5, 5, 4, 4, 3, 3, 2, 2, 1}, 9},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){9, 8, 7, 6, 5, 4}, 6},
    {(int[]){1, 3, 5, 7, 9}, 5},
    {(int[]){2, -2, 2, -2}, 4},
    {(int[]){-5, 0, 5, -5, 0, 5, -5}, 7},
    {(int[]){0, 1, 0, 1, 0, 1, 0, 1}, 8},
    {(int[]){-9, -8, -7, -6, -5, -4, -3, -2, -1}, 9},
    {(int[]){3, -3, 3, -3, 0}, 5},
    {(int[]){1, 2, 1, 2, 1, 2}, 6},
    {(int[]){-3, 3}, 2},
    {(int[]){0, 0, 1}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for tf.a to avoid modifying original input array
    tf.a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        tf.a[i] = tc.a[i];
    }
    // Find max value in original array
    int max_val = tf.a[0];
    for (int i = 1; i < tf.n; i++) {
        if (tf.a[i] > max_val) {
            max_val = tf.a[i];
        }
    }
    // Set first element to max value
    tf.a[0] = max_val;
    return tf;
}

int check(TestCase tc) {
    double Os = find_median(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    double Of = find_median(Tf_case.a, Tf_case.n);
    // Check MR: Of >= Os
    int is_valid = (Of >= Os) ? 1 : 0;
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