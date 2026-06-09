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


double min(double elements[], int n) {
    int size = n;
    double min = elements[size - 1];
    for (int i = size - 1; --i >= 0; ) {
        if (elements[i] < min) {
            min = elements[i];
        }
    }
    return min;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, 1},
    {(double[]){1.0, 2.0}, 2},
    {(double[]){2.0, 1.0}, 2},
    {(double[]){5.0, 3.0, 9.0}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){0.0, 0.0, 0.0}, 3},
    {(double[]){1.5, 2.7, 3.1}, 3},
    {(double[]){3.1, 1.5, 2.7}, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 4},
    {(double[]){40.0, 30.0, 20.0, 10.0}, 4},
    {(double[]){-5.5, 10.2, 0.0, -3.3}, 4},
    {(double[]){1.1, 1.1, 1.1}, 3},
    {(double[]){2.0}, 1},
    {(double[]){-100.0, 50.0}, 2},
    {(double[]){3.14, 2.71, 1.41}, 3},
    {(double[]){1.41, 3.14, 2.71}, 3},
    {(double[]){0.001, 0.002, 0.003}, 3},
    {(double[]){0.003, 0.001, 0.002}, 3},
    {(double[]){1000000.0, 2000000.0}, 2},
    {(double[]){-2000000.0, -1000000.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){2.5, -1.2, 0.0, 4.8, -3.1}, 5},
    {(double[]){10.5}, 1},
    {(double[]){-7.3, -7.3}, 2},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 6},
    {(double[]){0.6, 0.5, 0.4, 0.3, 0.2, 0.1}, 6},
    {(double[]){1.0, -1.0, 2.0, -2.0}, 4},
    {(double[]){9.9, 8.8, 7.7}, 3},
    {(double[]){7.7, 9.9, 8.8}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 2.0; // 正常数k，示例值，可根据需要调整
    int n = tf.n;
    double* new_elements = new double[n];
    for (int i = 0; i < n; ++i) {
        new_elements[i] = tf.elements[i] * k;
    }
    tf.elements = new_elements;
    return tf;
}

int check(TestCase tc) {
    double Os = min(tc.elements, tc.n);
    TestCase Tf_case = change(tc);
    double Of = min(Tf_case.elements, Tf_case.n);
    int is_valid = 0;
    double k = 2.0; // 必须与change函数中使用的k值一致
    if (Os * k == Of) {
        is_valid = 1;
    }
    delete[] Tf_case.elements;
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