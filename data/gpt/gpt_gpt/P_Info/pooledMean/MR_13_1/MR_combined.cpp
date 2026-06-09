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


double pooledMean(double data1[], double data2[], int n1, int n2) {
    double sum1 = 0;
    for (int i = 0; i < n1; i++) {
        sum1 += data1[i];
    }
    double mean1 = sum1 / n1;
    double sum2 = 0;
    for (int i = 0; i < n2; i++) {
        sum2 += data2[i];
    }
    double mean2 = sum2 / n2;
    return (n1 * mean1 + n2 * mean2) / (n1 + n2);
}


typedef struct {
    double* data1; double* data2; int n1; int n2;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0}, (double[]){2.0}, 1, 1 },
    { (double[]){0.5, -0.5}, (double[]){1.0, 1.0}, 2, 2 },
    { (double[]){3.0, 4.0, 5.0}, (double[]){10.0}, 3, 1 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){5.0, -5.0}, 3, 2 },
    { (double[]){-2.5, 2.5, -2.5, 2.5}, (double[]){-1.0, 1.0, -1.0}, 4, 3 },
    { (double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5}, 3, 2 },
    { (double[]){100.0, 200.0}, (double[]){300.0, 400.0, 500.0}, 2, 3 },
    { (double[]){-100.0, -200.0, -300.0}, (double[]){-400.0}, 3, 1 },
    { (double[]){0.0, 10.0, -10.0}, (double[]){5.0, -5.0, 0.0}, 3, 3 },
    { (double[]){-3.14}, (double[]){2.71}, 1, 1 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){10.0, 20.0}, 5, 2 },
    { (double[]){-1.0, -2.0}, (double[]){-3.0, -4.0, -5.0, -6.0, -7.0}, 2, 5 },
    { (double[]){7.0, 7.0, 7.0}, (double[]){3.0, 3.0}, 3, 2 },
    { (double[]){0.123, -0.456, 0.789}, (double[]){-0.321, 0.654}, 3, 2 },
    { (double[]){-10.0, 0.0, 10.0, 20.0}, (double[]){5.0, -5.0, 15.0, -15.0}, 4, 4 },
    { (double[]){42.0}, (double[]){-42.0, 0.0, 42.0}, 1, 3 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, (double[]){-1.1, -2.2, -3.3}, 6, 3 },
    { (double[]){-1.1, -2.2, -3.3}, (double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 3, 6 },
    { (double[]){0.0001, -0.0002}, (double[]){0.0003, -0.0004, 0.0005}, 2, 3 },
    { (double[]){1000.0, -0.5}, (double[]){-1000.0, 0.5}, 2, 2 },
    { (double[]){8.0, 8.0, 8.0, 8.0}, (double[]){8.0, 8.0, 8.0}, 4, 3 },
    { (double[]){1.0, -1.0, 1.0, -1.0}, (double[]){-1.0, 1.0, -1.0, 1.0}, 4, 4 },
    { (double[]){2.0, 3.0, 5.0, 7.0}, (double[]){11.0, 13.0}, 4, 2 },
    { (double[]){1.0, 1.0, 2.0, 3.0, 5.0}, (double[]){8.0, 13.0}, 5, 2 },
    { (double[]){-5.0, 10.0, -15.0, 20.0}, (double[]){-25.0, 30.0}, 4, 2 },
    { (double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4, 4 },
    { (double[]){9.0, 8.0, 7.0}, (double[]){6.0, 5.0, 4.0}, 3, 3 },
    { (double[]){3.3, -2.2, 5.5, -1.1}, (double[]){0.0, 4.4, -3.3}, 4, 3 },
    { (double[]){0.0, 0.0, 5.0}, (double[]){0.0, 10.0, 0.0}, 3, 3 },
    { (double[]){1.0, 2.5, 3.75}, (double[]){4.125, 5.5}, 3, 2 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Create a new array for data2 to sort in descending order to avoid modifying original data2
    double* new_data2 = new double[tc.n2];
    for (int i = 0; i < tc.n2; i++) {
        new_data2[i] = tc.data2[i];
    }
    // Sort new_data2 in descending order
    for (int i = 0; i < tc.n2 - 1; i++) {
        for (int j = 0; j < tc.n2 - i - 1; j++) {
            if (new_data2[j] < new_data2[j + 1]) {
                double temp = new_data2[j];
                new_data2[j] = new_data2[j + 1];
                new_data2[j + 1] = temp;
            }
        }
    }
    tf.data2 = new_data2;
    return tf;
}

int check(TestCase tc) {
    // Extract source inputs
    double* data1 = tc.data1;
    double* data2 = tc.data2;
    int n1 = tc.n1;
    int n2 = tc.n2;
    // Compute source output Os
    double Os = pooledMean(data1, data2, n1, n2);
    // Construct follow-up test case input Tf
    TestCase Tf_case = change(tc);
    double* data2_tf = Tf_case.data2;
    // Compute follow-up output Of
    double Of = pooledMean(Tf_case.data1, data2_tf, Tf_case.n1, Tf_case.n2);
    // Verify MR: Os == Of with tolerance for floating-point comparison
    int is_valid = 0;
    const double EPSILON = 1e-12;
    if (std::abs(Os - Of) < EPSILON) {
        is_valid = 1;
    }
    // Free dynamically allocated memory in Tf_case if any
    if (Tf_case.data2 != tc.data2) {
        delete[] Tf_case.data2;
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