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


int* array_calc1(int a[], int k, int n) {
    int* b = (int*)malloc(n * sizeof(int));
    if (b == NULL) return NULL;

    for (int i = 0; i < n; i++) {
        double val = (double)a[i] / k;
        b[i] = (int)round(val); 
    }
    return b;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){10, 20, 30}, 5, 3},
    {(int[]){7, 14, 21}, 7, 3},
    {(int[]){0, 0, 0}, 1, 3},
    {(int[]){-10, -20, -30}, 5, 3},
    {(int[]){1, 2, 3, 4, 5}, 2, 5},
    {(int[]){15}, 3, 1},
    {(int[]){100, 200}, 100, 2},
    {(int[]){33, 66, 99}, 33, 3},
    {(int[]){-5, 5, -5, 5}, 1, 4},
    {(int[]){8, 9, 10}, 2, 3},
    {(int[]){25, 50, 75, 100}, 25, 4},
    {(int[]){12, 24, 36, 48, 60}, 12, 5},
    {(int[]){-1, -2, -3}, 1, 3},
    {(int[]){49, 50, 51}, 10, 3},
    {(int[]){17, 34, 51, 68}, 17, 4},
    {(int[]){999, 1000, 1001}, 1000, 3},
    {(int[]){6, 7, 8, 9, 10, 11}, 3, 6},
    {(int[]){0, 10, 20, 30}, 10, 4},
    {(int[]){-100, 0, 100}, 50, 3},
    {(int[]){22, 44, 66, 88}, 11, 4},
    {(int[]){3, 6, 9, 12, 15}, 3, 5},
    {(int[]){45, 90, 135}, 45, 3},
    {(int[]){13, 26, 39, 52}, 13, 4},
    {(int[]){77, 154, 231}, 77, 3},
    {(int[]){2, 4, 6, 8, 10, 12, 14}, 2, 7},
    {(int[]){-8, -16, -24}, 8, 3},
    {(int[]){19, 38, 57, 76}, 19, 4},
    {(int[]){123, 456, 789}, 123, 3},
    {(int[]){1, 3, 5, 7, 9}, 1, 5},
    {(int[]){-15, 30, -45, 60}, 15, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_a = (int*)malloc(tc.n * sizeof(int));
    if (new_a == NULL) {
        tf.a = NULL;
        return tf;
    }
    for (int i = 0; i < tc.n; i++) {
        new_a[i] = tc.a[i] + tc.k;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    int* Os = array_calc1(tc.a, tc.k, tc.n);
    if (Os == NULL) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    if (Tf_case.a == NULL) {
        free(Os);
        return 0;
    }

    int* Of = array_calc1(Tf_case.a, Tf_case.k, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        free(Tf_case.a);
        return 0;
    }

    int is_valid = 1;
    for (int i = 0; i <= tc.n; i++) {
        if (Os[i] != Of[i] - 1) {
            is_valid = 0;
            break;
        }
    }

    free(Os);
    free(Of);
    free(Tf_case.a);
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