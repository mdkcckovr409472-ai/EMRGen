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
    double c = 5.0; // 示例常数，可根据需要调整或参数化
    if (tf.n > 0 && tf.elements != nullptr) {
        for (int i = 0; i < tf.n; ++i) {
            tf.elements[i] = tc.elements[i] + c;
        }
    }
    return tf;
}

int check(TestCase tc) {
    if (tc.n <= 0 || tc.elements == nullptr) {
        return 0;
    }
    
    double Os = min(tc.elements, tc.n);
    
    TestCase Tf_case = change(tc);
    
    double Of = min(Tf_case.elements, Tf_case.n);
    
    double c = 5.0; // 必须与 change 函数中使用的常数一致
    int is_valid = 0;
    if (fabs((Os + c) - Of) < 1e-9) {
        is_valid = 1;
    }
    
    // 清理 change 函数中修改的数组内存（原始数组由调用者管理）
    // 由于 change 函数直接修改了传入数组的副本指针指向的数据，
    // 这里需要将数组恢复原状，以便不影响后续可能的测试。
    // 注意：这里假设 tc.elements 和 Tf_case.elements 指向同一块内存。
    // 根据 change 的实现，确实如此，因此恢复数据。
    if (Tf_case.n > 0 && Tf_case.elements != nullptr) {
        for (int i = 0; i < Tf_case.n; ++i) {
            Tf_case.elements[i] = tc.elements[i];
        }
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