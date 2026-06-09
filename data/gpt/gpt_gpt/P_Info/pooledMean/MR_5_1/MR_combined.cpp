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

    // Allocate new memory for data1 copy since we modify it (descending sort)
    double* new_data1 = new double[tc.n1];
    for (int i = 0; i < tc.n1; i++) {
        new_data1[i] = tc.data1[i];
    }

    // Sort descending
    for (int i = 0; i < tc.n1 - 1; i++) {
        for (int j = i + 1; j < tc.n1; j++) {
            if (new_data1[i] < new_data1[j]) {
                double temp = new_data1[i];
                new_data1[i] = new_data1[j];
                new_data1[j] = temp;
            }
        }
    }

    tf.data1 = new_data1;

    return tf;
}

int check(TestCase tc) {
    // Compute source output Os
    double Os = pooledMean(tc.data1, tc.data2, tc.n1, tc.n2);

    // Generate follow-up test case Tf
    TestCase Tf = change(tc);

    // Compute follow-up output Of
    double Of = pooledMean(Tf.data1, Tf.data2, Tf.n1, Tf.n2);

    // Check MR: Os == Of
    int is_valid = (Os == Of) ? 1 : 0;

    // Free allocated memory in Tf
    if (Tf.data1 != tc.data1) {
        delete[] Tf.data1;
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