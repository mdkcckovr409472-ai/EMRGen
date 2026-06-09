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


int* bubble(int a[], int n){
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1, a, n * sizeof(int));
    int t;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (cp1[j] > cp1[j + 1])
            {
                t = cp1[j];
                cp1[j] = cp1[j + 1];
                cp1[j + 1] = t;
            }
        }
    }
    return cp1;
}

typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){}, 0},
    {(int[]){5}, 1},
    {(int[]){-3, 2}, 2},
    {(int[]){9, -1}, 2},
    {(int[]){4, -2, 7}, 3},
    {(int[]){-5, 0, 3}, 3},
    {(int[]){8, 6, 4}, 3},
    {(int[]){2, 2, 5, 5}, 4},
    {(int[]){7, 7, 7, 7}, 4},
    {(int[]){-4, 0, 3, -1, 5}, 5},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){3, -2, 8, 1, -5, 4}, 6},
    {(int[]){-6, -3, -1, 0, 2, 5}, 6},
    {(int[]){9, 7, 5, 3, 1, -1}, 6},
    {(int[]){-10, -5, -2, -2, 0, 3}, 6},
    {(int[]){12, -8, 15, -3, 7, -1, 4}, 7},
    {(int[]){-12, -9, -6, -3, 0, 3, 6}, 7},
    {(int[]){5, 1, 4, 2, 3, 0, -1, -4}, 8},
    {(int[]){-7, -3, -5, -2, -6, -1, -4, -8}, 8},
    {(int[]){1, 3, 2, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){-2, -2, -1, 0, 1, 1}, 6},
    {(int[]){10, -10, 9, -9, 8, -8, 7, -7}, 8},
    {(int[]){3, 3, -1, -1, 2, 2, 0, 0}, 8},
    {(int[]){4, 1, 3, 2}, 4},
    {(int[]){2, 4, 1, 3}, 4},
    {(int[]){-3, 2, -1, 4, -2, 5}, 6},
    {(int[]){7, 2, 5, 3, 8, 1, 6, 4}, 8},
    {(int[]){0, -1, 1, -2, 2, -3, 3, -4}, 8},
    {(int[]){-5, 0, 5, -5, 0, 5}, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for tf.a to add 1 to all elements
    tf.a = (int*)malloc(tc.n * sizeof(int));
    for (int i = 0; i < tc.n; i++) {
        tf.a[i] = tc.a[i] + 1;
    }
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input Ts
    int* Ts = tc.a;
    int n = tc.n;

    // (2) Call bubble on Ts to get Os
    int* Os = bubble(Ts, n);
    if (Os == NULL) {
        return 0;
    }

    // (3) Call change to get Tf
    TestCase Tf_case = change(tc);
    if (Tf_case.a == NULL) {
        free(Os);
        return 0;
    }

    // (4) Call bubble on Tf to get Of
    int* Of = bubble(Tf_case.a, n);
    if (Of == NULL) {
        free(Os);
        free(Tf_case.a);
        return 0;
    }

    // (5) Verify the MR: Os < Of means each element in Os less than corresponding in Of
    int is_valid = 1;
    for (int i = 0; i < n; i++) {
        if (!(Os[i] < Of[i])) {
            is_valid = 0;
            break;
        }
    }

    // (6) Free dynamic memory of Os, Of and Tf_case.a
    free(Os);
    free(Of);
    free(Tf_case.a);

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