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


double geometric_mean(int a[], int n) {
    long product = 1;
    for (int i = 0; i < n; i++) {
        product *= a[i];
    }
    return pow(product, (double) 1 / n);
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 4}, 3},
    {(int[]){2, 8}, 2},
    {(int[]){3, 3, 3}, 3},
    {(int[]){1, 1, 1, 1}, 4},
    {(int[]){4, 9}, 2},
    {(int[]){10, 10, 10}, 3},
    {(int[]){5, 20}, 2},
    {(int[]){2, 4, 8}, 3},
    {(int[]){1, 3, 9}, 3},
    {(int[]){6, 6, 6, 6}, 4},
    {(int[]){7, 14}, 2},
    {(int[]){1, 4, 16}, 3},
    {(int[]){9, 16}, 2},
    {(int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){3, 12}, 2},
    {(int[]){1, 5, 25}, 3},
    {(int[]){8, 27}, 2},
    {(int[]){4, 4, 4, 4}, 4},
    {(int[]){6, 24}, 2},
    {(int[]){1, 2, 4, 8}, 4},
    {(int[]){5, 5, 5}, 3},
    {(int[]){9, 9}, 2},
    {(int[]){2, 6, 18}, 3},
    {(int[]){7, 7, 7, 7}, 4},
    {(int[]){3, 6, 12}, 3},
    {(int[]){10, 40}, 2},
    {(int[]){1, 8, 64}, 3},
    {(int[]){4, 12}, 2},
    {(int[]){5, 10, 20}, 3},
    {(int[]){2, 3, 6}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        int idx1 = rand() % tf.n;
        int idx2 = rand() % tf.n;
        while (idx2 == idx1) {
            idx2 = rand() % tf.n;
        }
        int temp = tf.a[idx1];
        tf.a[idx1] = tf.a[idx2];
        tf.a[idx2] = temp;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = geometric_mean(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    double Of = geometric_mean(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (fabs(Os - Of) < 1e-9) {
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