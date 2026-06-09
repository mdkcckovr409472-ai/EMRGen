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
    // Reverse the array tf.a in place for the follow-up input
    for (int i = 0; i < tf.n / 2; i++) {
        int temp = tf.a[i];
        tf.a[i] = tf.a[tf.n - 1 - i];
        tf.a[tf.n - 1 - i] = temp;
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = bubble(tc.a, tc.n);
    if (Os == NULL) return 0;
    TestCase Tf_case = change(tc);

    int* Of = bubble(Tf_case.a, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }

    free(Os);
    free(Of);

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