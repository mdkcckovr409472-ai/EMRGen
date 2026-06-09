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
    { (int[]){}, 0 },
    { (int[]){0}, 1 },
    { (int[]){5}, 1 },
    { (int[]){-3}, 1 },
    { (int[]){3, -4}, 2 },
    { (int[]){1, 2, 2}, 3 },
    { (int[]){-1, 0, 1}, 3 },
    { (int[]){5, -2, 7, -1}, 4 },
    { (int[]){2, 2, 2, 2}, 4 },
    { (int[]){-3, 4, -5, 6, -7}, 5 },
    { (int[]){0, -2, 5, -1, 3}, 5 },
    { (int[]){-4, 1, -6, 2, -8, 3}, 6 },
    { (int[]){0, 0, 5, -5, 0, 3}, 6 },
    { (int[]){7, -3, 0, 2, -2, 4, -1}, 7 },
    { (int[]){-5, 9, -2, 8, -6, 1, -3}, 7 },
    { (int[]){3, 3, 3, 3, 3, 3, 3, 3}, 8 },
    { (int[]){-4, -4, -4, -4, -4, -4, -4, -4}, 8 },
    { (int[]){1, -1, 2, -2, 3, -3, 4, -4}, 8 },
    { (int[]){5, -7, 2, -3, 6, -1, 0, 4, -2}, 9 },
    { (int[]){-2, 3, -5, 1, -4, 6, -1, 2, -3, 0}, 10 },
    { (int[]){9, 8, 7, 6, 5}, 5 },
    { (int[]){-9, -8, -7, -6, -5}, 5 },
    { (int[]){0, 5, 0, -5, 0, 3, 0, -3}, 8 },
    { (int[]){1, 2, 3, 2, 1}, 5 },
    { (int[]){4, -2, 4, -2, 0}, 5 },
    { (int[]){-5, -5}, 2 },
    { (int[]){0, 0, 0}, 3 },
    { (int[]){1, -1, 1, -1}, 4 },
    { (int[]){10, -10, 5, -5, 0}, 5 },
    { (int[]){8, -8, 0, 7, -7, 1}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_a[i] = tf.a[i] * 2;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    double Os = find_magnitude(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    double Of = find_magnitude(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    const double EPSILON = 1e-8;
    if (fabs(Of - 2 * Os) < EPSILON) {
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