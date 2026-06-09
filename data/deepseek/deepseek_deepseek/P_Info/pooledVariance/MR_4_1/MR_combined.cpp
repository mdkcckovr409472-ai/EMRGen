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


double pooledVariance(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    double sumSq1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
        sumSq1 += data1[i] * data1[i];
    }
    double mean1 = sum1 / n1;
    double var1 = (sumSq1 - mean1 * sum1) / n1;
    double sum2 = 0;
    double sumSq2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
        sumSq2 += data2[i] * data2[i];
    }
    double mean2 = sum2 / n2;
    double var2 = (sumSq2 - mean2 * sum2) / n2;
    return (n1 * var1 + n2 * var2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){0.0, 0.0, 0.0}, (double[]){0.0, 0.0, 0.0}, 3, 3},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){-2.0, 0.0, 2.0}, 3, 3},
    {(double[]){10.5, 20.5, 30.5}, (double[]){15.5, 25.5, 35.5}, 3, 3},
    {(double[]){1.0}, (double[]){2.0}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){6.0, 7.0, 8.0, 9.0, 10.0}, 5, 5},
    {(double[]){2.5, 3.5}, (double[]){4.5, 5.5, 6.5}, 2, 3},
    {(double[]){100.0, 200.0}, (double[]){150.0}, 2, 1},
    {(double[]){-10.0, -20.0, -30.0}, (double[]){-5.0, -15.0}, 3, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6, 0.7}, 3, 4},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){2.0, 2.0, 2.0}, 4, 3},
    {(double[]){3.14, 6.28}, (double[]){1.57, 3.14, 4.71}, 2, 3},
    {(double[]){7.0}, (double[]){8.0, 9.0, 10.0}, 1, 3},
    {(double[]){-1.5, 1.5}, (double[]){-3.0, 0.0, 3.0}, 2, 3},
    {(double[]){12.0, 24.0, 36.0, 48.0}, (double[]){6.0, 18.0}, 4, 2},
    {(double[]){5.0, 10.0, 15.0}, (double[]){5.0, 10.0, 15.0}, 3, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 3.0, 9.0, 27.0}, 3, 4},
    {(double[]){0.0}, (double[]){1.0}, 1, 1},
    {(double[]){-100.0, 100.0}, (double[]){-50.0, 50.0}, 2, 2},
    {(double[]){9.9, 8.8, 7.7}, (double[]){6.6, 5.5, 4.4, 3.3}, 3, 4},
    {(double[]){20.0, 40.0}, (double[]){10.0, 30.0, 50.0, 70.0}, 2, 4},
    {(double[]){1.1, 2.2}, (double[]){3.3, 4.4, 5.5}, 2, 3},
    {(double[]){0.5, 1.0, 1.5, 2.0, 2.5}, (double[]){3.0, 3.5}, 5, 2},
    {(double[]){6.0, 12.0, 18.0}, (double[]){24.0, 30.0, 36.0, 42.0, 48.0}, 3, 5},
    {(double[]){-0.1, -0.2, -0.3}, (double[]){-0.4, -0.5}, 3, 2},
    {(double[]){15.0, 25.0, 35.0, 45.0}, (double[]){10.0, 20.0, 30.0, 40.0, 50.0}, 4, 5},
    {(double[]){2.0, 2.0}, (double[]){4.0, 4.0, 4.0}, 2, 3},
    {(double[]){11.0, 22.0, 33.0}, (double[]){44.0, 55.0}, 3, 2},
    {(double[]){0.25, 0.75}, (double[]){1.25, 1.75, 2.25}, 2, 3},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){9.0, 7.0, 5.0, 3.0, 1.0}, 4, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 为 data1 数组创建一份新的拷贝用于排序，避免修改原始数据
    double* sorted_data1 = new double[tc.n1];
    for (int i = 0; i < tc.n1; ++i) {
        sorted_data1[i] = tc.data1[i];
    }
    // 对拷贝的数组进行降序排序
    std::sort(sorted_data1, sorted_data1 + tc.n1, std::greater<double>());
    tf.data1 = sorted_data1;
    // 注意：tf.data2, tf.n1, tf.n2 保持不变，直接复用 tc 的值
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts) 并计算初始输出 (Os)
    double Os = pooledVariance(tc.data1, tc.data2, tc.n1, tc.n2);
    
    // (2) 构造衍生用例对象
    TestCase Tf_case = change(tc);
    
    // (3) 提取衍生输入并计算衍生输出 (Of)
    double Of = pooledVariance(Tf_case.data1, Tf_case.data2, Tf_case.n1, Tf_case.n2);
    
    // (4) 验证 Os 和 Of 是否满足蜕变关系 (Os == Of)
    int is_valid = 0;
    // 使用容差比较来处理浮点数的精度问题
    const double epsilon = 1e-10;
    if (std::fabs(Os - Of) < epsilon) {
        is_valid = 1;
    }
    
    // (5) 释放 change 函数中为衍生用例分配的动态内存
    if (Tf_case.data1 != tc.data1) {
        delete[] Tf_case.data1;
    }
    
    // (6) 返回验证结果
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