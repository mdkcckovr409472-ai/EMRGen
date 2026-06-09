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


int find_max(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1},
    {(int[]){-3, 7, 2}, 3},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){10, -5, 10, -5}, 4},
    {(int[]){3, 3, 3}, 3},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){8, 1, 6, 3, 7, 9, 2, 5, 4}, 9},
    {(int[]){2, 2, 5, 1, 5, 3}, 6},
    {(int[]){-10, 0, 10}, 3},
    {(int[]){4, -2, 4, -2, 4}, 5},
    {(int[]){7, 7, 6, 6, 5, 5}, 6},
    {(int[]){1, 2, 3, 2, 1}, 5},
    {(int[]){9, -9, 9, -9, 0}, 5},
    {(int[]){5, 1, 4, 2, 3, 0}, 6},
    {(int[]){0, 5, 0, 5, 0, 5}, 6},
    {(int[]){-3, -3, -2, -2, -1}, 5},
    {(int[]){12, 12, 12, 12}, 4},
    {(int[]){-7, 3, -7, 3, -7}, 5},
    {(int[]){6, 1, 6, 1, 6, 1}, 6},
    {(int[]){-4, 0, 4, -4, 0, 4}, 6},
    {(int[]){2, 8, 5, 3, 9, 1, 7}, 7},
    {(int[]){-5, -10, -3, -8, -2}, 5},
    {(int[]){15, 5, 15, 5, 15, 5, 15}, 7},
    {(int[]){0}, 1},
    {(int[]){-1, 1, -1, 1, -1, 1}, 6},
    {(int[]){3, -3, 3, -3, 3}, 5},
    {(int[]){8, 8, 8, 7, 9}, 5},
    {(int[]){-6, -6, -6, -6, -5}, 5},
    {(int[]){4, 2, 4, 2, 4, 2, 4, 2}, 8},
    {(int[]){5, -2, 5, -2, 5, -2, 5}, 7}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new memory for modified array
    int* new_a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_a[i] = tf.a[i] + 1; // add 1 to each element according to MR
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    int Os = find_max(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = find_max(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os < Of) {
        is_valid = 1;
    }
    delete[] Tf_case.a; // free dynamically allocated memory
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