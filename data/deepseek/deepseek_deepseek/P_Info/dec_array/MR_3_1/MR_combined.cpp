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
    {(int[]){1, 2, 3}, 1, 3},
    {(int[]){5, 10, 15}, 5, 3},
    {(int[]){0, 0, 0}, 3, 3},
    {(int[]){-1, -2, -3}, 1, 3},
    {(int[]){100, 200}, 50, 2},
    {(int[]){7}, 7, 1},
    {(int[]){-5, 0, 5}, 2, 3},
    {(int[]){1, 1, 1, 1}, 0, 4},
    {(int[]){10, 20, 30, 40, 50}, 10, 5},
    {(int[]){-10, -20, -30}, -5, 3},
    {(int[]){2, 4, 6, 8}, 1, 4},
    {(int[]){15, 25, 35}, 20, 3},
    {(int[]){0}, 100, 1},
    {(int[]){-100, -200, -300}, -100, 3},
    {(int[]){3, 6, 9, 12, 15, 18}, 3, 6},
    {(int[]){1, 3, 5, 7, 9}, 2, 5},
    {(int[]){50, 60, 70, 80}, 25, 4},
    {(int[]){-2, -4, -6, -8, -10}, -1, 5},
    {(int[]){999, 1000}, 1, 2},
    {(int[]){0, 10, 20, 30}, 5, 4},
    {(int[]){-7, 7, -14, 14}, 7, 4},
    {(int[]){12, 24, 36}, 12, 3},
    {(int[]){1, 2, 3, 4, 5, 6, 7}, 0, 7},
    {(int[]){-50, 0, 50}, 10, 3},
    {(int[]){8, 16, 24, 32}, 8, 4},
    {(int[]){11, 22, 33, 44, 55}, 11, 5},
    {(int[]){-1, -1, -1}, -1, 3},
    {(int[]){9, 18, 27}, 9, 3},
    {(int[]){4, 8, 12, 16, 20, 24}, 4, 6},
    {(int[]){-3, 3, -9, 9, -15}, 6, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0 && tf.a != nullptr) {
        std::sort(tf.a, tf.a + tf.n, std::greater<int>());
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = dec_array(tc.a, tc.k, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = dec_array(Tf_case.a, Tf_case.k, Tf_case.n);
    int is_valid = 0;
    bool equal = true;
    if (Os != nullptr && Of != nullptr) {
        for (int i = 0; i < tc.n; ++i) {
            if (Os[i] != Of[i]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            is_valid = 1;
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