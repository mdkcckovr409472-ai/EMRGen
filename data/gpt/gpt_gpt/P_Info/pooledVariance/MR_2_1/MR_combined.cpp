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
    { (double[]){1.0, 2.0}, (double[]){3.0, 4.0}, 2, 2 },
    { (double[]){5.5}, (double[]){-2.2}, 1, 1 },
    { (double[]){-1.0, 4.5, -3.2}, (double[]){2.2, -5.0, 0.0}, 3, 3 },
    { (double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2, 2 },
    { (double[]){7.1, -6.3}, (double[]){-1.5, 8.8}, 2, 2 },
    { (double[]){3.3, 3.3, 3.3}, (double[]){-2.2, -2.2, -2.2}, 3, 3 },
    { (double[]){9.9, -9.9, 0.1, -0.1}, (double[]){5.5, -5.5, 2.2, -2.2}, 4, 4 },
    { (double[]){1.2, -3.4, 5.6}, (double[]){-7.8, 9.0, -0.2}, 3, 3 },
    { (double[]){4.0}, (double[]){4.0, 4.0}, 1, 2 },
    { (double[]){-4.0, 4.0}, (double[]){2.5}, 2, 1 },
    { (double[]){2.5, -2.5, 2.5, -2.5}, (double[]){1.0, -1.0, 1.0, -1.0}, 4, 4 },
    { (double[]){6.6, 7.7}, (double[]){-8.8, -9.9}, 2, 2 },
    { (double[]){0.5, -0.5, 0.5}, (double[]){-0.5, 0.5, -0.5}, 3, 3 },
    { (double[]){3.14, 2.71}, (double[]){1.41, 1.73}, 2, 2 },
    { (double[]){-3.0, 0.0, 3.0}, (double[]){-1.0, 1.0, -1.0}, 3, 3 },
    { (double[]){5.0, -5.0, 5.0, -5.0, 5.0}, (double[]){-5.0, 5.0, -5.0, 5.0, -5.0}, 5, 5 },
    { (double[]){2.0, 8.0}, (double[]){4.0, 6.0}, 2, 2 },
    { (double[]){-2.0, -8.0}, (double[]){-4.0, -6.0}, 2, 2 },
    { (double[]){1.0, 3.0, 5.0}, (double[]){2.0, 4.0, 6.0}, 3, 3 },
    { (double[]){6.0, 4.0, 2.0}, (double[]){5.0, 3.0, 1.0}, 3, 3 },
    { (double[]){-1.1, 2.2, -3.3, 4.4}, (double[]){-4.4, 3.3, -2.2, 1.1}, 4, 4 },
    { (double[]){7.0}, (double[]){-7.0, 7.0, -7.0}, 1, 3 },
    { (double[]){-7.0, 7.0, -7.0}, (double[]){7.0}, 3, 1 },
    { (double[]){0.123, -0.456, 0.789}, (double[]){-0.321, 0.654, -0.987}, 3, 3 },
    { (double[]){9.0, 1.0, 4.0}, (double[]){2.0, 8.0, 5.0}, 3, 3 },
    { (double[]){-9.0, -1.0, -4.0}, (double[]){-2.0, -8.0, -5.0}, 3, 3 },
    { (double[]){3.0, -3.0, 3.0, -3.0, 3.0, -3.0}, (double[]){-3.0, 3.0, -3.0, 3.0, -3.0, 3.0}, 6, 6 },
    { (double[]){0.0, 1.0, -1.0, 2.0, -2.0}, (double[]){3.0, -3.0, 4.0, -4.0, 5.0}, 5, 5 }
};
int num_test_cases = 28;


TestCase change(TestCase tc) {
    TestCase tf = tc; 
    // Allocate new array for data1 to hold sorted values
    double* sorted_data1 = new double[tc.n1];
    for (int i = 0; i < tc.n1; i++) {
        sorted_data1[i] = tc.data1[i];
    }
    // Sort in ascending order
    for (int i = 0; i < tc.n1 - 1; i++) {
        for (int j = i + 1; j < tc.n1; j++) {
            if (sorted_data1[i] > sorted_data1[j]) {
                double temp = sorted_data1[i];
                sorted_data1[i] = sorted_data1[j];
                sorted_data1[j] = temp;
            }
        }
    }
    tf.data1 = sorted_data1;
    return tf;
}

int check(TestCase tc) {
    // Get source output Os
    double Os = pooledVariance(tc.data1, tc.data2, tc.n1, tc.n2);
    // Create follow-up input test case
    TestCase Tf_case = change(tc);
    // Get follow-up output Of
    double Of = pooledVariance(Tf_case.data1, Tf_case.data2, Tf_case.n1, Tf_case.n2);
    // Verify MR condition Os == Of with an epsilon for floating comparison
    int is_valid = 0;
    const double epsilon = 1e-12;
    if (std::abs(Os - Of) < epsilon) {
        is_valid = 1;
    }
    // Free any dynamically allocated memory in Tf_case
    if (Tf_case.data1 != tc.data1) {
        delete[] Tf_case.data1;
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