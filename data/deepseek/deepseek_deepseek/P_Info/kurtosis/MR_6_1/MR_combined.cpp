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


double kurtosis(double data[], int n) {
    double sum = 0;
    double sumPD = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
        sumSq += data[i] * data[i];
    }
    double mean = sum / n;
    double standardDeviation = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        sumPD += pow(data[i] - mean, 4);
    }
    double moment4 = sumPD / n;
    return -3 + moment4 / (standardDeviation * standardDeviation * standardDeviation * standardDeviation);
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){2.5, 3.5, 4.5, 5.5, 6.5}, 5},
    {(double[]){-1.0, 0.0, 1.0}, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 4},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5, 0.6}, 6},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){-5.0, -4.0, -3.0, -2.0, -1.0}, 5},
    {(double[]){1.5}, 1},
    {(double[]){2.0, 2.0, 2.0, 2.0}, 4},
    {(double[]){1.0, 1.0, 2.0, 2.0}, 4},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}, 8},
    {(double[]){-10.0, 0.0, 10.0}, 3},
    {(double[]){3.14, 6.28, 9.42}, 3},
    {(double[]){0.5, 1.5, 2.5, 3.5, 4.5, 5.5}, 6},
    {(double[]){7.0, 7.0, 7.0, 7.0, 7.0}, 5},
    {(double[]){1.1, 2.2, 3.3, 4.4}, 4},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 5},
    {(double[]){15.0, 25.0, 35.0, 45.0, 55.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {(double[]){8.0, 6.0, 7.0, 5.0, 3.0, 0.0, 9.0}, 7},
    {(double[]){1.0, 4.0, 9.0, 16.0, 25.0}, 5},
    {(double[]){-3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5}, 7},
    {(double[]){12.34, 56.78}, 2},
    {(double[]){0.01, 0.02, 0.03}, 3},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0, 100.0}, 6},
    {(double[]){-100.0, -50.0, 0.0, 50.0, 100.0}, 5},
    {(double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, 6},
    {(double[]){9.0, 10.0, 11.0, 12.0, 13.0}, 5},
    {(double[]){0.25, 0.5, 0.75, 1.0}, 4},
    {(double[]){6.0, 12.0, 18.0, 24.0, 30.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 分配新数组用于降序排序，以复用原结构体指针
    double* sorted_data = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        sorted_data[i] = tc.data[i];
    }
    // 降序排序
    std::sort(sorted_data, sorted_data + tc.n, std::greater<double>());
    tf.data = sorted_data;
    // 注意：tf.n 保持不变
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts)
    double* Ts_data = tc.data;
    int Ts_n = tc.n;

    // (2) 获取初始输出 (Os)
    double Os = kurtosis(Ts_data, Ts_n);

    // (3) 构造衍生用例对象
    TestCase Tf_case = change(tc);

    // (4) 获取衍生输出 (Of)
    double Of = kurtosis(Tf_case.data, Tf_case.n);

    // (5) 验证蜕变关系 Os == Of
    int is_valid = 0;
    const double epsilon = 1e-12; // 浮点数比较容差
    if (std::abs(Os - Of) < epsilon) {
        is_valid = 1;
    }

    // (6) 释放 Tf_case 中动态分配的内存
    delete[] Tf_case.data;

    // (7) 返回验证结果
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