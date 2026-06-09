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
    {(double[]){1.0}, 1},
    {(double[]){2.0, 4.0}, 2},
    {(double[]){0.5, 2.0, 1.5}, 3},
    {(double[]){-1.0, -2.0, -3.0}, 3},
    {(double[]){5.0, 1.0, 3.0, 2.0}, 4},
    {(double[]){10.0, 0.2, 0.5}, 3},
    {(double[]){3.3, 3.3, 3.3}, 3},
    {(double[]){7.5, 2.5, 5.0, 1.0, 4.0}, 5},
    {(double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 5},
    {(double[]){-0.5, 1.5, -2.5, 3.5}, 4},
    {(double[]){100.0, 50.0}, 2},
    {(double[]){1.1, 2.2, 3.3, 4.4, 5.5, 6.6}, 6},
    {(double[]){9.9, 8.8, 7.7}, 3},
    {(double[]){0.75, 1.25, 2.75}, 3},
    {(double[]){-10.0, 5.0}, 2},
    {(double[]){0.33, 0.66, 0.99}, 3},
    {(double[]){2.0, -2.0, 2.0, -2.0}, 4},
    {(double[]){4.0}, 1},
    {(double[]){3.0, 6.0, 9.0, 12.0}, 4},
    {(double[]){0.9, 1.1, 1.3, 1.5}, 4},
    {(double[]){-3.5, 2.5, -1.5, 0.5}, 4},
    {(double[]){5.5, 5.5, 5.5, 5.5, 5.5}, 5},
    {(double[]){0.25, 0.75, 1.25, 1.75}, 4},
    {(double[]){6.0, 3.0, 2.0}, 3},
    {(double[]){-0.1, -0.2, -0.3}, 3},
    {(double[]){8.0, 4.0, 2.0, 1.0}, 4},
    {(double[]){1.0, 1.0, 2.0, 2.0, 3.0}, 5},
    {(double[]){0.6, 0.8, 1.2, 1.4}, 4},
    {(double[]){-5.0, 5.0, -5.0, 5.0}, 4},
    {(double[]){2.5, 3.5, 4.5, 5.5, 6.5}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Sort the array in descending order in-place reusing the original data pointer
    std::sort(tf.data, tf.data + tf.n, std::greater<double>());
    return tf;
}

int check(TestCase tc) {
    // Source input Ts
    double* Ts = tc.data;
    int n = tc.n;
    // Execute function under test to get Os
    double Os = harmonicMean(Ts, n);

    // Construct follow-up test case Tf
    TestCase Tf_case = change(tc);
    double* Tf = Tf_case.data;

    // Execute function under test to get Of
    double Of = harmonicMean(Tf, n);

    // Verify metamorphic relation Os == Of
    int is_valid = 0;
    constexpr double EPS = 1e-12;
    if (std::abs(Os - Of) < EPS) {
        is_valid = 1;
    }

    // No dynamic memory allocated inside change(), so no free needed here

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