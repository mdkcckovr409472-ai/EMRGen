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


double* power(double data[], int k, int n) {
    for (int i = 0; i < n; i++) {
        data[i] = pow(data[i], k);
    }
    return data;
}


typedef struct {
    double* data; int k; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, 2, 3 },
    { (double[]){0.0, -1.0, 4.5}, 3, 3 },
    { (double[]){2.5}, 0, 1 },
    { (double[]){}, 5, 0 },
    { (double[]){-2.0, 0.5}, -1, 2 },
    { (double[]){-3.0, -4.0, 2.0}, 1, 3 },
    { (double[]){1.5, -1.5, 0.0, 2.0}, -2, 4 },
    { (double[]){0.1, 0.2, 0.3}, 4, 3 },
    { (double[]){-0.5, 0.5}, 2, 2 },
    { (double[]){10.0, -10.0}, -3, 2 },
    { (double[]){3.1415, 2.718}, 2, 2 },
    { (double[]){-1.0, 1.0, -1.0}, 3, 3 },
    { (double[]){0.0}, 5, 1 },
    { (double[]){5.0, -5.0, 0.0, 1.0}, -1, 4 },
    { (double[]){2.0, 3.0, 4.0, 5.0}, 0, 4 },
    { (double[]){-2.2, 2.2}, 2, 2 },
    { (double[]){0.25, 4.0}, -2, 2 },
    { (double[]){-3.5, 3.5, -3.5}, 1, 3 },
    { (double[]){1.0, 0.0, -1.0}, -1, 3 },
    { (double[]){7.0}, 2, 1 },
    { (double[]){-0.75, 0.75}, 3, 2 },
    { (double[]){0.0, 0.0, 0.0}, 2, 3 },
    { (double[]){9.0, -9.0, 9.0}, -2, 3 },
    { (double[]){1.2, -1.2, 2.4}, 2, 3 },
    { (double[]){-4.0, 4.0}, 0, 2 },
    { (double[]){0.5, -0.5, 0.25}, -1, 3 },
    { (double[]){6.0, 2.0, -2.0}, 3, 3 },
    { (double[]){-1.5, 1.5, -3.0, 3.0}, -3, 4 },
    { (double[]){0.33, -0.33}, 2, 2 },
    { (double[]){8.0, 0.0, -8.0}, 1, 3 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new memory for the divided data to avoid modifying the original input data
    double* new_data = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_data[i] = tc.data[i] / 2.0;
    }
    tf.data = new_data;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input
    double* Ts_data = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        Ts_data[i] = tc.data[i];
    }
    int k = tc.k;
    int n = tc.n;

    // (2) Call the function under test
    double* Os = power(Ts_data, k, n);

    // (3) Construct follow-up test case
    TestCase Tf_case = change(tc);
    double* Tf_data = Tf_case.data;

    // (4) Call function under test on follow-up input
    double* Of = power(Tf_data, k, n);

    // (5) Verify MR: Of[i] == Os[i] / pow(2, k) for all i
    int is_valid = 1;
    double divisor = pow(2.0, k);
    const double eps = 1e-9;  // tolerance for floating point comparison
    for (int i = 0; i < n; i++) {
        double expected = Os[i] / divisor;
        if (fabs(Of[i] - expected) > eps) {
            is_valid = 0;
            break;
        }
    }

    // (6) Free dynamically allocated memory
    delete[] Ts_data;
    delete[] Os;  // Os and Of point to Ts_data and Tf_data respectively (modified in place), so no separate delete needed here.
    delete[] Tf_data;

    // (7) Return verification result
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