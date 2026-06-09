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


double* ebeSubtract(double a[], double b[], int n1, int n2) {
    if (n1 != n2 || a == NULL || b == NULL) {
        return NULL;
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (!result) return NULL;

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] - b[i];
    }
    return result;
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){0.5, 1.5, 2.5}, 3, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2},
    {(double[]){-1.0, -2.0}, (double[]){-3.0, -4.0}, 2, 2},
    {(double[]){10.5, 20.25}, (double[]){5.25, 10.125}, 2, 2},
    {(double[]){100.0}, (double[]){50.0}, 1, 1},
    {(double[]){3.14159, 2.71828}, (double[]){1.0, 1.0}, 2, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.3, 0.2, 0.1}, 3, 3},
    {(double[]){-10.0, 0.0, 10.0}, (double[]){5.0, 5.0, 5.0}, 3, 3},
    {(double[]){1.0e-6, 2.0e-6}, (double[]){0.5e-6, 1.5e-6}, 2, 2},
    {(double[]){999.999, 888.888}, (double[]){111.111, 222.222}, 2, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){0.5, 0.5, 0.5, 0.5, 0.5}, 5, 5},
    {(double[]){2.5, 5.0, 7.5}, (double[]){2.5, 5.0, 7.5}, 3, 3},
    {(double[]){-1.5, -3.0, -4.5}, (double[]){-0.5, -1.0, -1.5}, 3, 3},
    {(double[]){1000.0, 2000.0, 3000.0}, (double[]){500.0, 1500.0, 2500.0}, 3, 3},
    {(double[]){0.0, -0.0}, (double[]){0.0, -0.0}, 2, 2},
    {(double[]){1.0, 2.0}, (double[]){2.0, 1.0}, 2, 2},
    {(double[]){12.34, 56.78}, (double[]){9.87, 65.43}, 2, 2},
    {(double[]){0.001, 0.002, 0.003}, (double[]){0.0005, 0.0015, 0.0025}, 3, 3},
    {(double[]){-100.5, 200.75}, (double[]){50.25, -100.375}, 2, 2},
    {(double[]){1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0}, 3, 3},
    {(double[]){9.0, 8.0, 7.0, 6.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4},
    {(double[]){1.5}, (double[]){3.0}, 1, 1},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0, 0.0}, 6, 6},
    {(double[]){2.0, 4.0, 8.0, 16.0}, (double[]){1.0, 2.0, 4.0, 8.0}, 4, 4},
    {(double[]){-1.0, -1.0, -1.0, -1.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4, 4},
    {(double[]){7.7, 8.8, 9.9}, (double[]){0.7, 0.8, 0.9}, 3, 3},
    {(double[]){1.0, 0.0, -1.0}, (double[]){-1.0, 0.0, 1.0}, 3, 3},
    {(double[]){42.0}, (double[]){24.0}, 1, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0; // 任意常数，示例值
    if (tf.a != NULL) {
        for (int i = 0; i < tf.n1; i++) {
            tf.a[i] = tf.a[i] - k;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = ebeSubtract(tc.a, tc.b, tc.n1, tc.n2);
    if (Os == NULL) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    double* Of = ebeSubtract(Tf_case.a, Tf_case.b, Tf_case.n1, Tf_case.n2);
    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    double k = 5.0;
    for (int i = 0; i < tc.n1; i++) {
        if (Os[i] != Of[i] + k) {
            is_valid = 0;
            break;
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