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


double harmonicMean(double data[], int n) {
    double sumOfInversions = 0;
    for (int i = 0; i < n; i++) {
        sumOfInversions += 1 / data[i];
    }
    return n / sumOfInversions;
}


typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){2.5, 3.5, 4.5}, 3},
    {(double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){2.0, 2.0}, 2},
    {(double[]){3.0}, 1},
    {(double[]){1.5, 2.5, 3.5, 4.5}, 4},
    {(double[]){0.1, 0.2, 0.3}, 3},
    {(double[]){5.0, 10.0, 15.0, 20.0}, 4},
    {(double[]){8.0, 12.0}, 2},
    {(double[]){6.0, 6.0, 6.0}, 3},
    {(double[]){2.2, 3.3, 4.4}, 3},
    {(double[]){7.0, 14.0, 21.0}, 3},
    {(double[]){0.25, 0.5, 0.75}, 3},
    {(double[]){9.0, 18.0, 27.0, 36.0}, 4},
    {(double[]){1.2, 2.4, 3.6}, 3},
    {(double[]){4.0, 8.0, 12.0, 16.0}, 4},
    {(double[]){11.0, 22.0}, 2},
    {(double[]){0.8, 1.6, 2.4, 3.2}, 4},
    {(double[]){15.0, 30.0, 45.0}, 3},
    {(double[]){1.75, 3.5, 5.25}, 3},
    {(double[]){2.1, 4.2, 6.3, 8.4}, 4},
    {(double[]){13.0, 26.0, 39.0}, 3},
    {(double[]){0.3, 0.6, 0.9, 1.2}, 4},
    {(double[]){17.0, 34.0}, 2},
    {(double[]){1.9, 3.8, 5.7}, 3},
    {(double[]){2.8, 5.6, 8.4, 11.2}, 4},
    {(double[]){19.0, 38.0, 57.0}, 3},
    {(double[]){0.4, 0.8, 1.2, 1.6, 2.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 为排序操作分配新的数组，避免修改原始数据
    tf.data = new double[tf.n];
    for (int i = 0; i < tf.n; i++) {
        tf.data[i] = tc.data[i];
    }
    // 对数组进行升序排序
    std::sort(tf.data, tf.data + tf.n);
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts)
    double* Ts_data = tc.data;
    int Ts_n = tc.n;

    // (2) 调用待测函数，获取初始输出 (Os)
    double Os = harmonicMean(Ts_data, Ts_n);

    // (3) 调用 change 函数，构造衍生用例对象
    TestCase Tf_case = change(tc);

    // (4) 提取衍生输入并获取衍生输出 (Of)
    double* Tf_data = Tf_case.data;
    int Tf_n = Tf_case.n;
    double Of = harmonicMean(Tf_data, Tf_n);

    // (5) 根据蜕变关系验证 Os 和 Of 是否相等
    int is_valid = 0;
    const double EPSILON = 1e-9;
    if (std::abs(Os - Of) < EPSILON) {
        is_valid = 1;
    }

    // (6) 释放 Tf_case 中分配的动态内存
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