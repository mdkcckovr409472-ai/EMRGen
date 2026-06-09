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


int* set_min_val(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        if (cp1[i] < k) {
            cp1[i] = k;
        }
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 5, 0 },
    { (int[]){1}, 5, 1 },
    { (int[]){5}, 5, 1 },
    { (int[]){10}, 5, 1 },
    { (int[]){2, 3}, 5, 2 },
    { (int[]){7, 2}, 5, 2 },
    { (int[]){8, 9}, 5, 2 },
    { (int[]){0, -1, 4}, 3, 3 },
    { (int[]){5, 2, 6}, 4, 3 },
    { (int[]){7, 8, 9}, 5, 3 },
    { (int[]){-5, -3, 0, 2}, -2, 4 },
    { (int[]){-1, -4, 3}, -2, 3 },
    { (int[]){-5, -1, 0, 2}, 0, 4 },
    { (int[]){1, 2, 3}, 0, 3 },
    { (int[]){3, 7, 1, 9, 2}, 5, 5 },
    { (int[]){0, 1, 2, 3, 4}, 6, 5 },
    { (int[]){10, 11, 12, 13, 14}, 5, 5 },
    { (int[]){5, 5, 5, 5}, 3, 4 },
    { (int[]){2, 2, 2, 2}, 5, 4 },
    { (int[]){2, 5, 2, 5, 2}, 4, 5 },
    { (int[]){10, 15, 20, 5}, 15, 4 },
    { (int[]){-10, -6, -4, 0}, -5, 4 },
    { (int[]){8, -2, 5, 1, 9, -3}, 4, 6 },
    { (int[]){-1, 0, 1, 2, 3, 4}, 5, 6 },
    { (int[]){6, 7, 8, 9, 10, 11}, 5, 6 },
    { (int[]){10, 1, 10, 1, 10, 1}, 5, 6 },
    { (int[]){0, 0, 0, 0}, 3, 4 },
    { (int[]){7, 7, 7}, 7, 3 },
    { (int[]){-3, 4, -1, 5}, 2, 4 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, 10 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    int* new_a = (int*)malloc(tc.n * sizeof(int));
    memcpy(new_a, tc.a, tc.n * sizeof(int));
    int half_start = tc.n / 2;
    for (int i = half_start; i < tc.n; i++) {
        new_a[i] = new_a[i] - 1;
    }
    TestCase tf = tc;
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    int* Os = set_min_val(tc.a, tc.k, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = set_min_val(Tf_case.a, Tf_case.k, Tf_case.n);
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] < Of[i]) {
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