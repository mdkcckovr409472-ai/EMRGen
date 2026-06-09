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


int* dec_array(int a[], int k, int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,a,n*sizeof(int));
    for (int i = 0; i < n; i++) {
        cp1[i] -= k;
    }
    return cp1;
}


typedef struct {
    int* a; int k; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0, 0 },
    { (int[]){5}, 2, 1 },
    { (int[]){0, 0, 0}, 0, 3 },
    { (int[]){1, 2, 3, 4, 5}, 1, 5 },
    { (int[]){10, -5, 3}, -2, 3 },
    { (int[]){7, 7, 7, 7}, 5, 4 },
    { (int[]){-3, 8, -1, 4}, 3, 4 },
    { (int[]){2, -2, 2, -2}, 0, 4 },
    { (int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 4, 9 },
    { (int[]){15, 10, 5, 0, -5}, 5, 5 },
    { (int[]){100, 50, -50, -100}, 20, 4 },
    { (int[]){1, 1, 2, 3, 5, 8, 13}, 1, 7 },
    { (int[]){-10, -5, 0, 5, 10}, -5, 5 },
    { (int[]){3, 6, 9, 12}, 3, 4 },
    { (int[]){-1, -2, -3, -4}, 2, 4 },
    { (int[]){0}, 10, 1 },
    { (int[]){5, -5, 5, -5, 5}, -5, 5 },
    { (int[]){2, 4, 6, 8, 10}, 1, 5 },
    { (int[]){7}, 0, 1 },
    { (int[]){-8, 0, 8}, 8, 3 },
    { (int[]){1, 3, 5, 7, 9, 11}, 2, 6 },
    { (int[]){12, 6, 0, -6, -12}, -6, 5 },
    { (int[]){4, 4, 4, 4, 4, 4}, 4, 6 },
    { (int[]){-3, -1, 1, 3}, 1, 4 },
    { (int[]){0, 5, 10, 15, 20}, 5, 5 },
    { (int[]){-2, 2, -2, 2, -2, 2}, 0, 6 },
    { (int[]){9, -9, 9, -9}, 9, 4 },
    { (int[]){1, 2}, 3, 2 },
    { (int[]){20}, 20, 1 },
    { (int[]){-5, 0, 5}, -5, 3 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse original test case but reverse the array 'a' in place using allocated memory
    int* reversed = (int*)malloc(tc.n * sizeof(int));
    for (int i = 0; i < tc.n; i++) {
        reversed[i] = tc.a[tc.n - 1 - i];
    }
    TestCase tf = tc;
    tf.a = reversed;
    return tf;
}

int check(TestCase tc) {
    int* Os = dec_array(tc.a, tc.k, tc.n);
    if (!Os) return 0;

    TestCase Tf_case = change(tc);
    if (!Tf_case.a) {
        free(Os);
        return 0;
    }
    int* Of = dec_array(Tf_case.a, Tf_case.k, Tf_case.n);
    if (!Of) {
        free(Os);
        free(Tf_case.a);
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