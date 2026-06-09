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


int count_non_zeroes(int a[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            cnt++;
        }
    }
    return cnt;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){ }, 0 },
    { (int[]){0, 0, 0, 0, 0}, 5 },
    { (int[]){1, 2, 3, 4}, 4 },
    { (int[]){-1, -2, -3}, 3 },
    { (int[]){0, 5, 0, -2, 7, 0}, 6 },
    { (int[]){0}, 1 },
    { (int[]){9}, 1 },
    { (int[]){0, 1, 0, 2, 0, 3, 0, 4}, 8 },
    { (int[]){3, -1, 0, 5, -5}, 5 },
    { (int[]){2, 2, 2, 2}, 4 },
    { (int[]){0, 0, 0}, 3 },
    { (int[]){0, 4, 5, 6, 7, 8, 0}, 7 },
    { (int[]){5, 0, 6, 0, 7, 0, 8}, 7 },
    { (int[]){-3, 0, -1, 0, -2, 0}, 6 },
    { (int[]){1, 0, -1, 2, 0, -2, 3, 0, -3}, 9 },
    { (int[]){4, 4, 0, 4, 0}, 5 },
    { (int[]){7, 7, 7, 7, 7}, 5 },
    { (int[]){1, -1, 2, -2}, 4 },
    { (int[]){0, 0, 5}, 3 },
    { (int[]){1, 2, 0, 3, 4}, 5 },
    { (int[]){-4, -5, -6, -7, -8}, 5 },
    { (int[]){10, -10, 0, 5, -5, 0}, 6 },
    { (int[]){3, 0, -2, 7, 0, -1, 4, 0}, 8 },
    { (int[]){0, 1, 0, 1, 0}, 5 },
    { (int[]){2, 3, 2, 3, 2, 3}, 6 },
    { (int[]){5, 0, 5, 0, 5}, 5 },
    { (int[]){-5, 0, -5, 0, -5}, 5 },
    { (int[]){0, 2, 3, 4}, 4 },
    { (int[]){1, 2, 3, 0}, 4 },
    { (int[]){1, -2, 3, -4, 5, -6}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0) {
        int mid = tf.n / 2;
        tf.a[mid] = 1;
    }
    return tf;
}

int check(TestCase tc) {
    int Os = count_non_zeroes(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = count_non_zeroes(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Of >= Os) {
        is_valid = 1;
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