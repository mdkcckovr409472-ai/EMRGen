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
    if (tf.n > 1) {
        int idx1 = 0;
        int idx2 = tf.n - 1;
        double temp = tf.data[idx1];
        tf.data[idx1] = tf.data[idx2];
        tf.data[idx2] = temp;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = harmonicMean(tc.data, tc.n);
    TestCase Tf_case = change(tc);
    double Of = harmonicMean(Tf_case.data, Tf_case.n);
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