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
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){1}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){0, 0, 0}, 3},
    {(int[]){10, 5, 8, 2, 7}, 5},
    {(int[]){1, 3, 2}, 3},
    {(int[]){100, 50, 75}, 3},
    {(int[]){-5, 0, 5}, 3},
    {(int[]){9, 8, 7, 6}, 4},
    {(int[]){1, 2, 1, 2}, 4},
    {(int[]){3, 1, 4, 1, 5}, 5},
    {(int[]){-10, 10, -20, 20}, 4},
    {(int[]){15}, 1},
    {(int[]){4, 3, 2, 1, 0, -1}, 6},
    {(int[]){6, 5, 4, 3, 2, 1, 0}, 7},
    {(int[]){1, 2, 3, 2, 1}, 5},
    {(int[]){7, 3, 9, 1, 6}, 5},
    {(int[]){-3, -1, -4, -2}, 4},
    {(int[]){0, 1, 0, 1, 0}, 5},
    {(int[]){12, 11, 13}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){8, 2, 5, 1, 9, 3}, 6},
    {(int[]){-7, 7, -8, 8}, 4},
    {(int[]){1, 4, 2, 5, 3}, 5},
    {(int[]){10, 20, 30}, 3},
    {(int[]){30, 20, 10}, 3},
    {(int[]){6, 1, 8, 4, 2}, 5},
    {(int[]){0, -5, 5, -10, 10}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        int idx1 = rand() % tf.n;
        int idx2 = rand() % tf.n;
        while (idx1 == idx2 || tf.a[idx1] == tf.a[idx2]) {
            idx2 = rand() % tf.n;
        }
        int temp = tf.a[idx1];
        tf.a[idx1] = tf.a[idx2];
        tf.a[idx2] = temp;
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = bubble(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = bubble(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    bool equal = true;
    for (int i = 0; i < tc.n; ++i) {
        if (Os[i] != Of[i]) {
            equal = false;
            break;
        }
    }
    if (equal) {
        is_valid = 1;
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