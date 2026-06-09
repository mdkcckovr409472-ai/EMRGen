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


double winsorizedMean(double elements[], int left, int right, int n) {
    qsort(elements, n, sizeof(double), [](const void *a, const void *b) -> int {
        double diff = *(double *)a - *(double *)b;
        if (diff > 0) return 1;
        else if (diff < 0) return -1;
        else return 0;
    });

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += elements[i];
    }

    double mean = sum / n;

    if (n > 0 && left >= 0 && left < n) {
        double leftElement = elements[left];
        for (int i = 0; i < left; ++i) {
            mean += (leftElement - elements[i]) / n;
        }
    }

    if (n > 0 && right >= 0 && right < n && (n - 1 - right) >= 0) {
        double rightElement = elements[n - 1 - right];
        for (int i = 0; i < right; ++i) {
            mean += (rightElement - elements[n - 1 - i]) / n;
        }
    }

    return mean;
}

typedef struct {
    double* elements; int left; int right; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.5, 3.7, 2.1, 8.4, 5.0}, 1, 1, 5},
    {(double[]){-2.3, 0.0, 4.1, -1.2, 7.8, 3.3}, 0, 2, 6},
    {(double[]){10.5, 20.2, 15.8, 30.1, 25.6}, 2, 0, 5},
    {(double[]){0.1, 0.5, 0.3, 0.9, 0.7, 0.2, 0.6}, 1, 3, 7},
    {(double[]){100.0, 200.0, 150.0, 180.0}, 0, 0, 4},
    {(double[]){-5.5, -1.2, -3.7, -8.0, -2.9}, 1, 1, 5},
    {(double[]){12.34, 56.78, 90.12}, 0, 1, 3},
    {(double[]){42.0}, 0, 0, 1},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 2, 2, 6},
    {(double[]){-10.1, 5.5, 0.0, 5.5, 10.1}, 1, 0, 5},
    {(double[]){7.2, 3.8, 9.1, 4.5, 6.0, 1.9, 8.7}, 3, 1, 7},
    {(double[]){0.01, 0.02, 0.05, 0.03}, 0, 1, 4},
    {(double[]){50.5, 30.3, 80.8, 60.6, 40.4, 70.7}, 1, 3, 6},
    {(double[]){-7.3, 2.4, -1.8, 5.9, -3.1, 4.0, -0.5, 1.2}, 2, 2, 8},
    {(double[]){999.9, 888.8, 777.7}, 1, 1, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}, 4, 3, 9},
    {(double[]){-20.2, -15.7, -30.3, -25.1, -10.5}, 0, 4, 5},
    {(double[]){0.25, 0.75, 0.50, 1.00, 0.00}, 2, 0, 5},
    {(double[]){33.33, 66.66, 11.11, 99.99, 22.22}, 1, 2, 5},
    {(double[]){6.4, 2.1, 9.3, 5.7, 8.0, 3.5, 7.2, 4.9}, 0, 5, 8},
    {(double[]){-100.5, 200.2, -50.8, 150.1}, 1, 0, 4},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, 2, 2, 5},
    {(double[]){1.618, 2.718, 3.142, 1.414, 2.236}, 0, 0, 5},
    {(double[]){18.6, 24.9, 12.3, 30.0, 21.7, 15.4}, 3, 1, 6},
    {(double[]){-9.8, -4.3, -12.1, -6.7, -2.2, -8.5}, 1, 2, 6},
    {(double[]){123.456, 789.012, 345.678, 901.234}, 0, 3, 4},
    {(double[]){5.0, 5.0, 5.0, 5.0, 5.0, 5.0}, 1, 4, 6},
    {(double[]){0.3, 0.7, 0.2, 0.9, 0.4, 0.8, 0.1, 0.6}, 2, 3, 8},
    {(double[]){-1.5, 3.0, -2.0, 4.5, -0.5, 2.0}, 0, 0, 6},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0}, 3, 4, 10}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int n = tf.n;
    if (n > 0 && tf.elements != nullptr) {
        std::sort(tf.elements, tf.elements + n, std::greater<double>());
    }
    return tf;
}

int check(TestCase tc) {
    double Os = winsorizedMean(tc.elements, tc.left, tc.right, tc.n);
    TestCase Tf_case = change(tc);
    double Of = winsorizedMean(Tf_case.elements, Tf_case.left, Tf_case.right, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
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