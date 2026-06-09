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


double* calculateAbsoluteDifferences(double z[], int n){
    if (n == 0)
    {
        return NULL;
    }
    
    double* zAbs = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        zAbs[i] = fabs(z[i]);
    }
    return zAbs;
}


typedef struct {
    double* z; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){}, 0 },
    { (double[]){0.5, 2.3, 4.1}, 3 },
    { (double[]){-1.0, -3.14, -0.001}, 3 },
    { (double[]){-2.5, 0.0, 3.7}, 3 },
    { (double[]){5.5, -5.5, 5.5, -5.5}, 4 },
    { (double[]){0.0}, 1 },
    { (double[]){7.89}, 1 },
    { (double[]){-9.99}, 1 },
    { (double[]){-1.2, 1.2, -1.2, 1.2, 0.0}, 5 },
    { (double[]){3.3, -2.2, 0.0, -4.4, 5.5}, 5 },
    { (double[]){0.001, -0.002, 0.003, -0.004}, 4 },
    { (double[]){-1000.0, 500.0, -250.0}, 3 },
    { (double[]){999.9, -999.9}, 2 },
    { (double[]){-10, 0.5, 20.75, -30.125}, 4 },
    { (double[]){0.0, 0.0, -0.0, 0.0}, 4 },
    { (double[]){1.0, -1.0, 2.0, -2.0, 3.0, -3.0}, 6 },
    { (double[]){-0.75, -2.5, -3.125}, 3 },
    { (double[]){0.25, 1.125, 2.875}, 3 },
    { (double[]){-5.5, 4.4, -3.3, 2.2, -1.1, 0.0, 1.1, -2.2, 3.3, -4.4}, 10 },
    { (double[]){8.8, -1.1, 3.3, -7.7, 5.5}, 5 },
    { (double[]){-6.0, 6.0, -6.0, 6.0}, 4 },
    { (double[]){1e-06, -2e-06, 3e-06}, 3 },
    { (double[]){-15.5, 20.0, -25.5, 30.0}, 4 },
    { (double[]){0.0, -12.34, 0.0, 56.78, -0.0}, 5 },
    { (double[]){-1, -2, -3, -4, -5}, 5 },
    { (double[]){1, 2, 3, 4, 5}, 5 },
    { (double[]){-7, 8.0, -9.5, 10}, 4 },
    { (double[]){-999.0}, 1 },
    { (double[]){999.0}, 1 },
    { (double[]){-0.5, 1, -1.5, 2, -2.5, 3}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Create a new array by reusing the original one to fulfill the MR requirement
    // but since we must overwrite the first element, allocate a new array, copy and overwrite
    if (tf.n > 0) {
        double* new_z = (double*)malloc(tf.n * sizeof(double));
        if (new_z != NULL) {
            for (int i = 0; i < tf.n; i++) {
                new_z[i] = tf.z[i];
            }
            new_z[0] = -std::numeric_limits<double>::max();
            tf.z = new_z;
        }
    }
    return tf;
}

int check(TestCase tc) {
    double* Os = NULL;
    double* Of = NULL;
    int n = tc.n;
    if (n == 0) {
        // For empty input, no meaningful MR check needed
        return 1;
    }

    Os = calculateAbsoluteDifferences(tc.z, n);
    if (!Os) {
        return 0;
    }

    TestCase Tf_case = change(tc);
    if (Tf_case.n != n || Tf_case.z == NULL) {
        free(Os);
        return 0;
    }

    Of = calculateAbsoluteDifferences(Tf_case.z, n);
    if (!Of) {
        free(Os);
        if (Tf_case.z != tc.z) free(Tf_case.z);
        return 0;
    }

    // Check MR:
    // Of[0] >= 0 and Of[i] == Os[i] for i > 0
    int is_valid = 1;
    if (Of[0] < 0) {
        is_valid = 0;
    } else {
        for (int i = 1; i < n; i++) {
            if (Of[i] != Os[i]) {
                is_valid = 0;
                break;
            }
        }
    }

    free(Os);
    free(Of);
    if (Tf_case.z != tc.z) {
        free(Tf_case.z);
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