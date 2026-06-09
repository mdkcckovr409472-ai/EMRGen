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


double weightedRMS(double data[], double weights[], int n) {
    double sumOfProducts = 0;
    double sumOfSquaredProducts = 0;
    for(int i = 0; i < n; i++) {
        sumOfProducts += data[i] * weights[i];
        sumOfSquaredProducts += data[i] * data[i] * weights[i];
    }
    return sumOfProducts / sumOfSquaredProducts;
}


typedef struct {
    double* data; double* weights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){1.0, 2.0}, (double[]){0.5, 0.5}, 2},
    {(double[]){2.0, 3.0}, (double[]){1.0, 1.0}, 2},
    {(double[]){-1.0, 1.0}, (double[]){1.0, 1.0}, 2},
    {(double[]){0.0, 0.0}, (double[]){1.0, 2.0}, 2},
    {(double[]){3.0, 4.0, 5.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){1.5, 2.5, 3.5}, (double[]){2.0, 1.0, 0.5}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){-2.0, -1.0, 0.0, 1.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){100.0, 200.0}, (double[]){0.01, 0.02}, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){1.5, 2.5, 1.5}, 3},
    {(double[]){2.0, 4.0, 6.0, 8.0}, (double[]){0.25, 0.25, 0.25, 0.25}, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, (double[]){0.2, 0.2, 0.2, 0.2, 0.2}, 5},
    {(double[]){3.14159, 2.71828}, (double[]){1.0, 1.0}, 2},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 0.5, 0.333, 0.25}, 4},
    {(double[]){-10.0, -5.0, 5.0, 10.0}, (double[]){1.0, 2.0, 2.0, 1.0}, 4},
    {(double[]){0.0, 1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, 6},
    {(double[]){2.5, 5.0, 7.5}, (double[]){4.0, 2.0, 1.0}, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){12.0, 24.0, 36.0}, (double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){0.01, 0.02, 0.03}, (double[]){100.0, 50.0, 33.333}, 3},
    {(double[]){7.0, 14.0, 21.0}, (double[]){1.0, 0.5, 0.333}, 3},
    {(double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, 7},
    {(double[]){9.0, 18.0, 27.0}, (double[]){2.0, 1.0, 0.666}, 3},
    {(double[]){1.2, 2.4, 3.6, 4.8}, (double[]){5.0, 2.5, 1.666, 1.25}, 4},
    {(double[]){15.0, 30.0, 45.0}, (double[]){0.2, 0.4, 0.6}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, (double[]){0.5, 1.0, 1.5, 2.0}, 4},
    {(double[]){0.25, 0.5, 0.75, 1.0, 1.25}, (double[]){4.0, 2.0, 1.333, 1.0, 0.8}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 2.0; // 选择一个非零常数，例如 2.0
    if (tf.weights != nullptr && tf.n > 0) {
        // 为衍生用例的权重数组分配新内存
        tf.weights = new double[tf.n];
        for (int i = 0; i < tf.n; i++) {
            tf.weights[i] = tc.weights[i] / k;
        }
    }
    return tf;
}

int check(TestCase tc) {
    // 获取初始输出 Os
    double Os = weightedRMS(tc.data, tc.weights, tc.n);
    
    // 构造衍生用例
    TestCase Tf_case = change(tc);
    
    // 获取衍生输出 Of
    double Of = weightedRMS(Tf_case.data, Tf_case.weights, Tf_case.n);
    
    int is_valid = 0;
    // 验证 Os 和 Of 是否相等（考虑浮点数精度）
    const double epsilon = 1e-9;
    if (fabs(Os - Of) < epsilon) {
        is_valid = 1;
    }
    
    // 释放 change 函数中为衍生用例权重数组分配的内存
    if (Tf_case.weights != nullptr && Tf_case.weights != tc.weights) {
        delete[] Tf_case.weights;
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