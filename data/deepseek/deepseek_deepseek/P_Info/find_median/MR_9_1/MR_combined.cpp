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
    if (tf.n > 0) {
        int minIndex = 0;
        int minValue = tf.a[0];
        for (int i = 1; i < tf.n; i++) {
            if (tf.a[i] < minValue) {
                minIndex = i;
                minValue = tf.a[i];
            }
        }
        int c = 10;
        tf.a[minIndex] += c;
    }
    return tf;
}

int check(TestCase tc) {
    if (tc.n <= 0) {
        return 1;
    }
    int* copy_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        copy_a[i] = tc.a[i];
    }
    double Os = find_median(copy_a, tc.n);
    TestCase Tf_case = change(tc);
    double Of = find_median(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os <= Of) {
        is_valid = 1;
    }
    delete[] copy_a;
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