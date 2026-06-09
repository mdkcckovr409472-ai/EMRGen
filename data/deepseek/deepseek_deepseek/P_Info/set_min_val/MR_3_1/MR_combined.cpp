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
    {(int[]){1, 2, 3, 4, 5}, 3, 5},
    {(int[]){5, 4, 3, 2, 1}, 2, 5},
    {(int[]){10, 20, 30}, 25, 3},
    {(int[]){-10, -5, 0, 5, 10}, 0, 5},
    {(int[]){7, 7, 7, 7}, 7, 4},
    {(int[]){100}, 50, 1},
    {(int[]){15, 25, 35, 45}, 30, 4},
    {(int[]){0, 1, 2, 3, 4, 5}, 3, 6},
    {(int[]){-3, -2, -1}, -1, 3},
    {(int[]){8, 6, 4, 2}, 5, 4},
    {(int[]){12, 24, 36, 48, 60}, 40, 5},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1}, 5, 9},
    {(int[]){-20, -10, 0, 10, 20}, -5, 5},
    {(int[]){2, 4, 6, 8, 10, 12}, 7, 6},
    {(int[]){99, 101}, 100, 2},
    {(int[]){50, 60, 70, 80, 90}, 65, 5},
    {(int[]){-1, -1, -1, -1}, -2, 4},
    {(int[]){3, 1, 4, 1, 5, 9}, 2, 6},
    {(int[]){11, 22, 33, 44, 55, 66, 77}, 40, 7},
    {(int[]){6, 7, 8, 9, 10}, 8, 5},
    {(int[]){-50, -25, 0, 25, 50}, 10, 5},
    {(int[]){19, 28, 37, 46}, 30, 4},
    {(int[]){13, 26, 39, 52}, 35, 4},
    {(int[]){0, 0, 0, 0, 0}, 1, 5},
    {(int[]){100, 200, 300, 400}, 250, 4},
    {(int[]){5, 10, 15, 20, 25, 30}, 12, 6},
    {(int[]){-8, -4, 0, 4, 8}, 0, 5},
    {(int[]){14, 21, 28, 35, 42}, 25, 5},
    {(int[]){17, 34, 51, 68}, 40, 4},
    {(int[]){9, 18, 27, 36, 45, 54}, 20, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_a = (int*)malloc(tf.n * sizeof(int));
    memcpy(new_a, tf.a, tf.n * sizeof(int));
    for (int i = 0; i < tf.n; i++) {
        if (new_a[i] < tf.k) {
            new_a[i] = tf.k + 1;
        }
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    int* Os = set_min_val(tc.a, tc.k, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = set_min_val(Tf_case.a, Tf_case.k, Tf_case.n);
    int is_valid = 0;
    int all_less_equal = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] > Of[i]) {
            all_less_equal = 0;
            break;
        }
    }
    if (all_less_equal) {
        is_valid = 1;
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