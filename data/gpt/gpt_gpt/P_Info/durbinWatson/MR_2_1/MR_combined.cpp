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


double durbinWatson(double elements[], int n) {
    
    double run = 0;
    for (int i = 1; i < n; ++i) {
        double x = elements[i] - elements[i - 1];
        run += x * x;
    }
    return run;
}


typedef struct {
    double* elements; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.0}, 1 },
    { (double[]){5.0, 5.0}, 2 },
    { (double[]){5.0, -5.0}, 2 },
    { (double[]){2.0, 1.0, 3.0}, 3 },
    { (double[]){0.0, -1.0, 1.0}, 3 },
    { (double[]){10.0, -10.0, 10.0, -10.0}, 4 },
    { (double[]){3.5, 3.5, 3.5, 3.5}, 4 },
    { (double[]){7.2, -3.1, 0.0, 4.5, -2.2}, 5 },
    { (double[]){1.0, 1.0, 2.0, 2.0, 1.0}, 5 },
    { (double[]){-5.5, 2.2, -3.3, 4.4, -1.1, 0.0}, 6 },
    { (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 6 },
    { (double[]){9.9, -9.8, 9.7, -9.6, 9.5, -9.4, 9.3}, 7 },
    { (double[]){1.1, -2.2, 3.3, -4.4, 5.5, -6.6, 7.7}, 7 },
    { (double[]){2.0, -5.0, 3.0, -1.0, 4.0, -3.0, 0.0, 1.0}, 8 },
    { (double[]){0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5}, 8 },
    { (double[]){-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0}, 9 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5, -0.6, 0.7, -0.8, 0.9}, 9 },
    { (double[]){10.0, -10.0, 10.0, -10.0, 10.0, -10.0, 10.0, -10.0, 10.0, -10.0}, 10 },
    { (double[]){3.0, -1.0, 4.0, -1.0, 5.0, -9.0, 2.0, 6.0, 5.0, 3.0}, 10 },
    { (double[]){1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}, 11 },
    { (double[]){-2.0, -1.0, 0.0, 1.0, 2.0, -2.0, -1.0, 0.0, 1.0, 2.0, -2.0}, 11 },
    { (double[]){2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9, 0.0, 1.1, -1.2, 2.3}, 12 },
    { (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 12 },
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0}, 13 },
    { (double[]){-5.0, 3.0, -2.0, 6.0, -1.0, 4.0, -3.0, 5.0, -4.0, 2.0, -6.0, 1.0, 0.0}, 13 },
    { (double[]){0.12, -0.34, 0.56, -0.78, 0.90, -0.11, 0.22, -0.33, 0.44, -0.55, 0.66, -0.77, 0.88, -0.99}, 14 },
    { (double[]){-1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5}, 15 },
    { (double[]){5.0, -3.0, 8.0, -2.0, 7.0, -6.0, 4.0, -5.0, 3.0, -1.0, 2.0, -4.0, 1.0, -7.0, 0.0}, 15 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0}, 15 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf;
    tf.n = tc.n;
    if (tc.n > 0) {
        tf.elements = new double[tc.n];
        for (int i = 0; i < tc.n; ++i) {
            tf.elements[i] = tc.elements[i] - 1.0;
        }
    } else {
        tf.elements = nullptr;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = durbinWatson(tc.elements, tc.n);

    TestCase Tf_case = change(tc);
    double Of = durbinWatson(Tf_case.elements, Tf_case.n);

    int is_valid = 0;
    if (Os <= Of) {
        is_valid = 1;
    }

    if (Tf_case.elements != nullptr) {
        delete[] Tf_case.elements;
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