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


int add_values(int a[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0 },
    { (int[]){0}, 1 },
    { (int[]){5}, 1 },
    { (int[]){-3}, 1 },
    { (int[]){1, 2}, 2 },
    { (int[]){-1, -2}, 2 },
    { (int[]){4, -3}, 2 },
    { (int[]){1, -1, 2}, 3 },
    { (int[]){0, 0, 0}, 3 },
    { (int[]){3, -2, 5, -1}, 4 },
    { (int[]){2, 2, 2, 2, 2}, 5 },
    { (int[]){-5, 4, -3, 2, -1}, 5 },
    { (int[]){1, -1, 1, -1, 1, -1}, 6 },
    { (int[]){-2, 3, 0, -1, 4, -3, 2}, 7 },
    { (int[]){10, -10, 5, -5, 0, 1, -1, 2}, 8 },
    { (int[]){0, 0, 1, 2, 3, 0, -1, -2, 0}, 9 },
    { (int[]){-4, 6, -2, 3, -1, 5, -3, 2, -6, 4}, 10 },
    { (int[]){-7, -7, -7, -7}, 4 },
    { (int[]){7, 7, 7, 7, 7}, 5 },
    { (int[]){9, 8, 7, 6, 5}, 5 },
    { (int[]){-9, -8, -7, -6, -5}, 5 },
    { (int[]){0, 1, 0, 2, 0, 3}, 6 },
    { (int[]){0, -1, 0, -2, 0, -3}, 6 },
    { (int[]){-3, -2, -1, 0, 1, 2, 3}, 7 },
    { (int[]){5, -2, 5, -2, 5, -2}, 6 },
    { (int[]){2, 3, 5, 7, 11}, 5 },
    { (int[]){0, 1, 1, 2, 3, 5, 8}, 7 },
    { (int[]){0, -1, -1, -2, -3, -5, -8}, 7 },
    { (int[]){-4, 0, 4, -4, 0, 4}, 6 },
    { (int[]){-3, 7, -2, 6, -1, 5}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse input array by creating a new shifted array
    int* shifted = new int[tc.n];
    if (tc.n > 0) {
        shifted[0] = tc.a[tc.n - 1];
        for (int i = 1; i < tc.n; i++) {
            shifted[i] = tc.a[i - 1];
        }
    }
    TestCase tf = tc;
    tf.a = shifted;
    return tf;
}

int check(TestCase tc) {
    int Os = add_values(tc.a, tc.n);

    TestCase Tf_case = change(tc);
    int Of = add_values(Tf_case.a, Tf_case.n);

    int is_valid = (Os == Of) ? 1 : 0;

    delete[] Tf_case.a;

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