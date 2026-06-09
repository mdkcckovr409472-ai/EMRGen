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


int find_max2(int a[], int n) {
    int max = a[0] + a[1];
    for (int i = 0; i < n - 1; i++) {
        if (a[i] + a[i + 1] > max) {
            max = a[i] + a[i + 1];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){1, 2, 3, 4}, 4 },
    { (int[]){5, 5, 5, 5}, 4 },
    { (int[]){-1, -2, -3, -4}, 4 },
    { (int[]){10, -5, 3, -2, 8}, 5 },
    { (int[]){1, 2, 100, 3, 4}, 5 },
    { (int[]){50, 50, 1, 2, 3}, 5 },
    { (int[]){1, 2, 3, 40, 40}, 5 },
    { (int[]){0, 0, 0, 0}, 4 },
    { (int[]){7, -7, 7, -7, 7}, 5 },
    { (int[]){3, -1, 4, -2, 5, -3}, 6 },
    { (int[]){9, -1}, 2 },
    { (int[]){0, 0}, 2 },
    { (int[]){1, 2, 3}, 3 },
    { (int[]){-10, 20, -30, 40}, 4 },
    { (int[]){-50, -40, -30, -20}, 4 },
    { (int[]){0, 5, 0, 5, 0}, 5 },
    { (int[]){12, -3, 7, 19, -8, 4}, 6 },
    { (int[]){5, 5, 5, 5, 5}, 5 },
    { (int[]){-99, -1, -2, -3}, 4 },
    { (int[]){1, 9, 1, 9, 1}, 5 },
    { (int[]){20, 15, 10, 5, 10, 15, 20}, 7 },
    { (int[]){8, -6, 2, 9, -1, 3, 7}, 7 },
    { (int[]){-5, -4, -3, 2, -1}, 5 },
    { (int[]){1, 2, 3, 4, 100, 5, 6}, 7 },
    { (int[]){3, 1, 4, 1, 3}, 5 },
    { (int[]){-2, 7, -3, 8, -1, 6, -4, 5}, 8 },
    { (int[]){0, 0, 0, 10, 0, 0}, 6 },
    { (int[]){-99, 99, -50, 50}, 4 },
    { (int[]){2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 10 },
    { (int[]){1, 2, 1, 2, 1, 2, 1, 2}, 8 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // We must create a new array to apply the change without modifying original input
    tf.a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        tf.a[i] = tc.a[i];
    }
    if (tf.n > 0) {
        tf.a[0] -= 2;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = find_max2(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = find_max2(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Of <= Os) {
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