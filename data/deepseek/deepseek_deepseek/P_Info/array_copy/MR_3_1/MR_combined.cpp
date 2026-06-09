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


int* array_copy(int a[], int n) {
    if (a == NULL || n <= 0) {
        return NULL;
    }


    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;  
    }


    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }

    return copy;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){1, 2}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){0}, 1},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){10, 20, 30, 40}, 4},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){100}, 1},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){1, 1, 1, 1}, 4},
    {(int[]){-10, 10, -20, 20}, 4},
    {(int[]){7}, 1},
    {(int[]){0, 0, 0}, 3},
    {(int[]){15, 25, 35}, 3},
    {(int[]){-100, -200, -300}, 3},
    {(int[]){999}, 1},
    {(int[]){1, 3, 5, 7, 9, 11, 13}, 7},
    {(int[]){-1, -2, -3, -4}, 4},
    {(int[]){50, 60, 70, 80, 90}, 5},
    {(int[]){6, 5, 4, 3, 2, 1, 0}, 7},
    {(int[]){12, 24, 36}, 3},
    {(int[]){-7, 7, -14, 14}, 4},
    {(int[]){1000, 2000, 3000, 4000}, 4},
    {(int[]){8, 6, 4, 2, 0, -2}, 6},
    {(int[]){9}, 1},
    {(int[]){11, 22, 33, 44, 55, 66, 77, 88}, 8},
    {(int[]){-50, 0, 50}, 3},
    {(int[]){19, 28, 37, 46}, 4},
    {(int[]){255}, 1}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.a != NULL && tf.n > 0) {
        int* reversed = (int*)malloc(tf.n * sizeof(int));
        if (reversed != NULL) {
            for (int i = 0; i < tf.n; i++) {
                reversed[i] = tf.a[tf.n - 1 - i];
            }
            tf.a = reversed;
        } else {
            tf.a = NULL;
        }
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = array_copy(tc.a, tc.n);
    if (Os == NULL) {
        return 1;
    }

    TestCase Tf_case = change(tc);
    int* Of = array_copy(Tf_case.a, Tf_case.n);

    int is_valid = 0;
    if (Of != NULL) {
        is_valid = 1;
        for (int i = 0; i < tc.n; i++) {
            if (Os[i] != Of[tc.n - 1 - i]) {
                is_valid = 0;
                break;
            }
        }
    }

    free(Os);
    free(Of);
    if (Tf_case.a != tc.a) {
        free(Tf_case.a);
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