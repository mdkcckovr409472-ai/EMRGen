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


double* ebeAdd(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL; 
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        result[i] = a[i] + b[i];  
    }

    return result; 
}


typedef struct {
    double* a; double* b; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2},
    {(double[]){-1.5, 2.7}, (double[]){3.2, -4.1}, 2, 2},
    {(double[]){10.0}, (double[]){-10.0}, 1, 1},
    {(double[]){1.1, 2.2}, (double[]){-1.1, -2.2}, 2, 2},
    {(double[]){3.14159}, (double[]){2.71828}, 1, 1},
    {(double[]){100.5, 200.75, 300.9}, (double[]){50.25, 75.5, 90.1}, 3, 3},
    {(double[]){-0.001, 0.001}, (double[]){0.001, -0.001}, 2, 2},
    {(double[]){1.0e-6, 2.0e-6}, (double[]){3.0e-6, 4.0e-6}, 2, 2},
    {(double[]){999.999}, (double[]){0.001}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){5.0, 6.0, 7.0, 8.0}, 4, 4},
    {(double[]){-100.0, -200.0}, (double[]){100.0, 200.0}, 2, 2},
    {(double[]){12.34, 56.78}, (double[]){98.76, 43.21}, 2, 2},
    {(double[]){0.5, 1.5, 2.5}, (double[]){-0.5, -1.5, -2.5}, 3, 3},
    {(double[]){1.0}, (double[]){1.0}, 1, 1},
    {(double[]){2.2, 3.3, 4.4, 5.5, 6.6}, (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, 5, 5},
    {(double[]){-3.14, 0.0, 3.14}, (double[]){1.0, 2.0, 3.0}, 3, 3},
    {(double[]){1.0, 0.0, -1.0}, (double[]){0.0, 1.0, 0.0}, 3, 3},
    {(double[]){10.1, 20.2}, (double[]){30.3, 40.4}, 2, 2},
    {(double[]){7.0, 8.0, 9.0, 10.0, 11.0, 12.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 6, 6},
    {(double[]){0.25, 0.5, 0.75}, (double[]){0.25, 0.5, 0.75}, 3, 3},
    {(double[]){-999.9, 0.0, 999.9}, (double[]){0.1, 0.0, -0.1}, 3, 3},
    {(double[]){1.5}, (double[]){2.5}, 1, 1},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}, (double[]){7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 7, 7},
    {(double[]){0.0}, (double[]){0.0}, 1, 1},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){-4.0, -5.0, -6.0}, 3, 3},
    {(double[]){1000.0, 2000.0}, (double[]){-500.0, -1500.0}, 2, 2},
    {(double[]){9.876, 5.432}, (double[]){1.234, 4.568}, 2, 2},
    {(double[]){0.1, 0.2, 0.3, 0.4}, (double[]){0.9, 0.8, 0.7, 0.6}, 4, 4},
    {(double[]){15.0, 25.0, 35.0}, (double[]){10.0, 20.0, 30.0}, 3, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double k = 5.0; // 任意常数，此处示例为5.0
    int n = tf.n1;
    double* new_b = (double*)malloc(n * sizeof(double));
    if (new_b == NULL) {
        // 如果分配失败，保持原样返回，check函数会处理NULL
        return tf;
    }
    for (int i = 0; i < n; i++) {
        new_b[i] = tf.b[i] + k;
    }
    // 注意：这里我们创建了一个新的数组，但tf.b可能指向原始用例的内存。
    // 根据约束，我们需要复用tc的数据。但为了构造衍生输入，我们必须修改b。
    // 我们选择分配新内存给tf.b，并覆盖指针。原始tc.b的内存将在check中释放。
    tf.b = new_b;
    // 注意：tf.a 和 tc.a 指向相同的内存，我们不会修改它。
    return tf;
}

int check(TestCase tc) {
    // (1) 提取初始输入 (Ts)
    // Ts 就是 tc 本身
    // (2) 获取初始输出 (Os)
    double* Os = ebeAdd(tc.a, tc.b, tc.n1, tc.n2);
    if (Os == NULL) {
        // 初始调用失败，测试无效或失败。根据框架，我们可能希望返回0。
        // 但为了资源清理，我们仍需处理change产生的内存。
        // 由于Os为NULL，我们无法进行验证，直接清理并返回0。
        // 注意：此时尚未调用change，所以没有Tf_case需要清理。
        // 但tc.b可能是动态分配的？根据上下文，TestCase由外部创建和管理。
        // 我们假设传入的tc其内部指针a和b由外部管理，check函数不释放它们。
        // 因此这里直接返回。
        return 0;
    }

    // (3) 构造衍生用例
    TestCase Tf_case = change(tc);

    // (4) 获取衍生输出 (Of)
    double* Of = ebeAdd(Tf_case.a, Tf_case.b, Tf_case.n1, Tf_case.n2);
    if (Of == NULL) {
        // 衍生调用失败，验证失败。释放Os和Tf_case.b（如果是新分配的）。
        free(Os);
        if (Tf_case.b != tc.b) { // 检查b是否被change重新分配
            free(Tf_case.b);
        }
        return 0;
    }

    // (5) 验证蜕变关系
    int is_valid = 1;
    double k = 5.0; // 必须与change函数中使用的k一致
    int n = tc.n1;
    for (int i = 0; i < n; i++) {
        // 验证 Os[i] + k == Of[i]
        if (fabs((Os[i] + k) - Of[i]) > 1e-9) { // 使用容差比较浮点数
            is_valid = 0;
            break;
        }
    }

    // (6) 释放动态内存
    free(Os);
    free(Of);
    // 释放Tf_case.b（如果是新分配的）
    if (Tf_case.b != tc.b) {
        free(Tf_case.b);
    }
    // 注意：我们不释放Tf_case.a，因为它与tc.a相同，由外部管理。
    // 同样，我们不释放tc.a和tc.b。

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