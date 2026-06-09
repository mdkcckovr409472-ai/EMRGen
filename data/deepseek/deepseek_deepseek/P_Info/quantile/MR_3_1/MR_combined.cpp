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


double quantile(double sortedElements[], double phi, int n) {      
    double index = phi * (n - 1);
    int lhs = (int) index;
    double delta = index - lhs;
    double result;
    if (n == 0) {
        return 0.0;
    }
    if (lhs == n - 1) {
        result = sortedElements[lhs];
    } else {
        result = (1 - delta) * sortedElements[lhs] + delta * sortedElements[lhs + 1];
    }
    return result;
}


typedef struct {
    double* sortedElements; double phi; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 0.0, 1},
    {(double[]){1.0}, 0.5, 1},
    {(double[]){1.0}, 1.0, 1},
    {(double[]){1.0, 2.0}, 0.0, 2},
    {(double[]){1.0, 2.0}, 0.25, 2},
    {(double[]){1.0, 2.0}, 0.5, 2},
    {(double[]){1.0, 2.0}, 0.75, 2},
    {(double[]){1.0, 2.0}, 1.0, 2},
    {(double[]){1.0, 2.0, 3.0}, 0.0, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.2, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.4, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.5, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.6, 3},
    {(double[]){1.0, 2.0, 3.0}, 0.8, 3},
    {(double[]){1.0, 2.0, 3.0}, 1.0, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.0, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.33, 3},
    {(double[]){-5.0, 0.0, 5.0}, 0.66, 3},
    {(double[]){-5.0, 0.0, 5.0}, 1.0, 3},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.1, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.333, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.5, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.667, 4},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 0.9, 4},
    {(double[]){10.0}, 0.001, 1},
    {(double[]){10.0}, 0.999, 1},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.125, 5},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.375, 5},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.625, 5},
    {(double[]){0.0, 10.0, 20.0, 30.0, 40.0}, 0.875, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 1.0; // 示例值，k > 0。也可以根据策略选择其他非零值，例如 -1.0。
    if (tf.sortedElements != nullptr && tf.n > 0) {
        for (int i = 0; i < tf.n; ++i) {
            tf.sortedElements[i] += k;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double Os = quantile(tc.sortedElements, tc.phi, tc.n);
    TestCase Tf_case = change(tc);
    double Of = quantile(Tf_case.sortedElements, Tf_case.phi, Tf_case.n);
    int is_valid = 0;
    double k = 1.0; // 必须与 change 函数中使用的 k 值一致
    if (k > 0) {
        if (Os < Of) {
            is_valid = 1;
        }
    } else if (k < 0) {
        if (Os > Of) {
            is_valid = 1;
        }
    }
    if (Tf_case.sortedElements != nullptr && Tf_case.sortedElements != tc.sortedElements) {
        delete[] Tf_case.sortedElements;
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