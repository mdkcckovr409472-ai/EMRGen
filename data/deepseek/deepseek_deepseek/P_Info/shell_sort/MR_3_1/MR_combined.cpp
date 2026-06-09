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


int* shell_sort(int a[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    int j;
    int i;
    int k;
    int m;
    int mid;
        
    for (m = n/2; m > 0; m /= 2) {
        for (j = m; j < n; j++) {
            for (i = j - m; i >= 0; i -= m) {
                if (cp1[i + m] >= cp1[i]) {
                    break;
                } else {
                    mid = cp1[i];
                    cp1[i] = cp1[i + m];
                    cp1[i + m] = mid;
                }
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
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6}, 8},
    {(int[]){-5, -1, -3, -2, -4}, 5},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){100}, 1},
    {(int[]){42, 9, 17, 4, 23}, 5},
    {(int[]){1, 3, 5, 7, 9, 2, 4, 6, 8}, 9},
    {(int[]){10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10},
    {(int[]){2, 2, 2, 1, 1, 1}, 6},
    {(int[]){-10, 5, 0, -3, 8}, 5},
    {(int[]){15, 22, 8, 19, 11, 6}, 6},
    {(int[]){7, 3, 9, 1, 5}, 5},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1}, 2},
    {(int[]){6, 5, 4, 3, 2, 1, 0, -1, -2}, 9},
    {(int[]){13, 7, 21, 4, 18, 2}, 6},
    {(int[]){9, 4, 2, 7, 1, 8, 3, 6, 5}, 9},
    {(int[]){25, 14, 36, 8, 19}, 5},
    {(int[]){0, 5, -2, 10, -5}, 5},
    {(int[]){12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 12},
    {(int[]){1, 4, 3, 2, 5}, 5},
    {(int[]){-7, -3, -9, -1, -5}, 5},
    {(int[]){30, 20, 10, 40, 50}, 5},
    {(int[]){6, 2, 9, 1, 5, 3}, 6},
    {(int[]){17, 5, 23, 11, 2, 19}, 6},
    {(int[]){4, 7, 2, 8, 5, 1, 3, 6}, 8},
    {(int[]){-1, 0, 1, -2, 2}, 5},
    {(int[]){14, 33, 27, 10, 35, 19, 42, 44}, 8},
    {(int[]){8, 3, 6, 1, 7, 2, 5, 4}, 8}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* sorted_a = (int*)malloc(tc.n * sizeof(int));
    memcpy(sorted_a, tc.a, tc.n * sizeof(int));
    for (int m = tc.n/2; m > 0; m /= 2) {
        for (int j = m; j < tc.n; j++) {
            for (int i = j - m; i >= 0; i -= m) {
                if (sorted_a[i + m] >= sorted_a[i]) {
                    break;
                } else {
                    int mid = sorted_a[i];
                    sorted_a[i] = sorted_a[i + m];
                    sorted_a[i + m] = mid;
                }
            }
        }
    }
    tf.a = sorted_a;
    return tf;
}

int check(TestCase tc) {
    int* Os = shell_sort(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = shell_sort(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    int arrays_equal = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] != Of[i]) {
            arrays_equal = 0;
            break;
        }
    }
    if (arrays_equal) {
        is_valid = 1;
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