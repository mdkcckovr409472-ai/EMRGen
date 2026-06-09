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


double find_magnitude(int a[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * a[i];
    }
    double result = sqrt(sum);
    return result;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){0}, 1},
    {(int[]){1}, 1},
    {(int[]){-1}, 1},
    {(int[]){3, 4}, 2},
    {(int[]){-3, 4}, 2},
    {(int[]){3, -4}, 2},
    {(int[]){-3, -4}, 2},
    {(int[]){1, 2, 2}, 3},
    {(int[]){-1, -2, -2}, 3},
    {(int[]){1, 0, -1}, 3},
    {(int[]){5, 12}, 2},
    {(int[]){8, 15}, 2},
    {(int[]){7, 24}, 2},
    {(int[]){1, 1, 1, 1}, 4},
    {(int[]){2, 4, 4, 3, 2}, 5},
    {(int[]){-2, 4, -4, 3, -2}, 5},
    {(int[]){10}, 1},
    {(int[]){-10}, 1},
    {(int[]){6, 8, 10}, 3},
    {(int[]){-6, 8, -10}, 3},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){-1, 2, -3, 4, -5}, 5},
    {(int[]){9, 12, 15}, 3},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){1, -1, 1, -1, 1}, 5},
    {(int[]){2, 3, 6}, 3},
    {(int[]){-2, -3, -6}, 3},
    {(int[]){20, 21}, 2},
    {(int[]){-20, 21}, 2},
    {(int[]){11, 60, 61}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* sorted_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        sorted_a[i] = tc.a[i];
    }
    std::sort(sorted_a, sorted_a + tc.n);
    tf.a = sorted_a;
    return tf;
}

int check(TestCase tc) {
    double Os = find_magnitude(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    double Of = find_magnitude(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (std::abs(Os - Of) < 1e-9) {
        is_valid = 1;
    }
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