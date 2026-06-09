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


double weighted_average(double a[], double b[], int n) {
    double sum1 = 0;
    double sum2 = 0;
    for(int i = 0; i < n; i++) {
        sum1 += a[i] * b[i];
        sum2 += b[i];
    }
    return sum1 / sum2;
}


typedef struct {
    double* a; double* b; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3 },
    { (double[]){-1.5, 0.0, 2.5}, (double[]){3.0, -2.0, 1.0}, 3 },
    { (double[]){0.0}, (double[]){5.0}, 1 },
    { (double[]){10.0, -10.0}, (double[]){-5.0, 5.0}, 2 },
    { (double[]){2.2, 2.2, 2.2}, (double[]){1.0, 1.0, 1.0}, 3 },
    { (double[]){-3.3, 4.4, -5.5, 6.6}, (double[]){7.7, -8.8, 9.9, -10.0}, 4 },
    { (double[]){9.9, -9.9}, (double[]){0.1, 0.2}, 2 },
    { (double[]){5.5, 5.5, 5.5, 5.5, 5.5}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5 },
    { (double[]){-0.1, -0.2, -0.3}, (double[]){0.3, 0.2, 0.1}, 3 },
    { (double[]){3.14, 2.71}, (double[]){1.41, 1.73}, 2 },
    { (double[]){-7.0, 8.0, 9.0}, (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){0.5, -0.5, 0.5}, (double[]){2.0, 2.0, 2.0}, 3 },
    { (double[]){1.0, 2.0, 3.0, 4.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4 },
    { (double[]){-2.0, -4.0, -6.0}, (double[]){-1.0, -2.0, -3.0}, 3 },
    { (double[]){7.0, 8.0, 9.0}, (double[]){1.0, 0.0, 1.0}, 3 },
    { (double[]){0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0}, 3 },
    { (double[]){-5.0, 5.0, -5.0, 5.0}, (double[]){1.0, -1.0, 1.0, 2.0}, 4 },
    { (double[]){3.0}, (double[]){-3.0}, 1 },
    { (double[]){2.5, -2.5}, (double[]){-2.5, 2.5}, 2 },
    { (double[]){1.1, 2.2, 3.3, 4.4, 5.5}, (double[]){5.5, 4.4, 3.3, 2.2, 1.1}, 5 },
    { (double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, 1.0}, 3 },
    { (double[]){9.0, 8.0, 7.0}, (double[]){0.1, 0.2, 0.3}, 3 },
    { (double[]){-9.0, -8.0, -7.0}, (double[]){0.3, 0.2, 0.1}, 3 },
    { (double[]){0.123, 0.456}, (double[]){0.789, 0.012}, 2 },
    { (double[]){-0.5, 0.5, -0.5, 0.5}, (double[]){2.0, 2.0, 2.0, 2.0}, 4 },
    { (double[]){6.0, -6.0, 6.0}, (double[]){-2.0, 2.0, -2.0}, 3 },
    { (double[]){3.33, 6.66}, (double[]){1.11, 2.22}, 2 },
    { (double[]){-3.33, -6.66}, (double[]){-1.11, -2.22}, 2 },
    { (double[]){0.0, 1.0, -1.0, 2.0, -2.0}, (double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5 },
    { (double[]){5.0, 5.0, 5.0}, (double[]){0.5, 0.5, 0.5}, 3 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for divided elements by 2, fulfilling Test Case reuse principle for other fields
    tf.a = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        tf.a[i] = tc.a[i] / 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = weighted_average(tc.a, tc.b, tc.n);
    TestCase Tf_case = change(tc);
    double Of = weighted_average(Tf_case.a, Tf_case.b, Tf_case.n);
    // Verify Os == 2 * Of, allow minor floating point tolerance
    int is_valid = 0;
    double diff = Os - 2.0 * Of;
    if (diff < 1e-9 && diff > -1e-9) {
        is_valid = 1;
    }
    // Clean up allocated memory for Tf_case.a
    delete[] Tf_case.a;
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