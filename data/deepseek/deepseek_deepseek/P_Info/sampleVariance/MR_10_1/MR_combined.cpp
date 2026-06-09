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


double sampleVariance(double elements[], double mean, int n) {
    int size = n;
    double sum = 0;
    for (int i = size; --i >= 0; ) {
        double delta = elements[i] - mean;
        sum += delta * delta;
    }
    return sum / (size - 1);
}


typedef struct {
    double* elements; double mean; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 3.0, 5},
    {(double[]){2.5, 3.5, 4.5}, 3.5, 3},
    {(double[]){10.0, 20.0, 30.0, 40.0}, 25.0, 4},
    {(double[]){-1.0, 0.0, 1.0}, 0.0, 3},
    {(double[]){100.0, 200.0, 300.0}, 200.0, 3},
    {(double[]){0.1, 0.2, 0.3, 0.4}, 0.25, 4},
    {(double[]){-5.0, -3.0, -1.0, 1.0, 3.0}, -1.0, 5},
    {(double[]){7.0}, 7.0, 1},
    {(double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5}, 4.0, 6},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 0.0, 4},
    {(double[]){2.0, 4.0, 6.0, 8.0}, 5.0, 4},
    {(double[]){-10.0, 0.0, 10.0}, 0.0, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 3.3, 5},
    {(double[]){15.0, 25.0, 35.0, 45.0}, 30.0, 4},
    {(double[]){0.5, 1.5, 2.5}, 1.5, 3},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 0.0, 5},
    {(double[]){8.0, 9.0, 10.0, 11.0, 12.0}, 10.0, 5},
    {(double[]){1000.0, 2000.0, 3000.0}, 2000.0, 3},
    {(double[]){0.01, 0.02, 0.03}, 0.02, 3},
    {(double[]){-100.0, -50.0, 0.0, 50.0, 100.0}, 0.0, 5},
    {(double[]){6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0}, 9.0, 7},
    {(double[]){1.0, 1.0, 1.0, 1.0}, 1.0, 4},
    {(double[]){3.14, 6.28, 9.42}, 6.28, 3},
    {(double[]){-0.5, 0.0, 0.5}, 0.0, 3},
    {(double[]){12.0, 24.0, 36.0}, 24.0, 3},
    {(double[]){0.2, 0.4, 0.6, 0.8, 1.0}, 0.6, 5},
    {(double[]){-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0}, 0.0, 7},
    {(double[]){50.0, 60.0, 70.0, 80.0, 90.0}, 70.0, 5},
    {(double[]){0.001, 0.002, 0.003, 0.004}, 0.0025, 4},
    {(double[]){9.0, 18.0, 27.0, 36.0}, 22.5, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // 随机打乱数组元素的顺序
    // 使用 Fisher-Yates shuffle 算法
    for (int i = tf.n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        double temp = tf.elements[i];
        tf.elements[i] = tf.elements[j];
        tf.elements[j] = temp;
    }
    return tf;
}

int check(TestCase tc) {
    // 获取初始输出 Os
    double Os = sampleVariance(tc.elements, tc.mean, tc.n);
    
    // 构造衍生用例
    TestCase Tf_case = change(tc);
    
    // 获取衍生输出 Of
    double Of = sampleVariance(Tf_case.elements, Tf_case.mean, Tf_case.n);
    
    int is_valid = 0;
    // 验证 Os 和 Of 是否相等（考虑浮点数精度）
    const double epsilon = 1e-10;
    if (fabs(Os - Of) < epsilon) {
        is_valid = 1;
    }
    
    // 清理资源：如果 change 中分配了新数组，需要释放
    // 但根据 change 的实现，它复用了原数组指针并打乱顺序，没有分配新内存。
    // 因此，这里不需要额外的释放操作。
    // 注意：调用者负责管理原始 tc.elements 的内存。
    
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