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
    // Reuse the original TestCase struct fields but modify the array contents by subtracting 1 from every element
    TestCase tf = tc;
    if (tf.a != nullptr && tf.n > 0) {
        // Allocate new memory for the follow-up input array
        int* new_arr = new int[tf.n];
        for (int i = 0; i < tf.n; i++) {
            new_arr[i] = tf.a[i] - 1;
        }
        tf.a = new_arr;
    }
    return tf;
}

int check(TestCase tc) {
    // Extract the source input
    int* Ts = tc.a;
    int n = tc.n;
    if (Ts == nullptr || n <= 0) {
        return 0;
    }
    // Call the function under test to get Os
    // Note: The function modifies the input array a[], so copy input before call to prevent altering it
    int* Ts_copy = new int[n];
    for (int i = 0; i < n; i++) {
        Ts_copy[i] = Ts[i];
    }
    double Os = find_median(Ts_copy, n);
    delete[] Ts_copy;

    // Construct follow-up test case
    TestCase Tf_case = change(tc);

    if (Tf_case.a == nullptr || Tf_case.n != n) {
        // Free any allocated memory if any
        if (Tf_case.a != tc.a) {
            delete[] Tf_case.a;
        }
        return 0;
    }

    // Call function under test with follow-up input, copy it to avoid modifying original
    int* Tf_copy = new int[n];
    for (int i = 0; i < n; i++) {
        Tf_copy[i] = Tf_case.a[i];
    }
    double Of = find_median(Tf_copy, n);
    delete[] Tf_copy;

    // Verify MR: Os > Of
    int is_valid = (Os > Of) ? 1 : 0;

    // Free dynamic memory from change()
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