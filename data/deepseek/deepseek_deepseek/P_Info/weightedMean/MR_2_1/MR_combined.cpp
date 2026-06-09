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


double weightedMean(double elements[], double theWeights[], int n) {
    int size = n;
    double sum = 0.0;
    double weightsSum = 0.0;
    for(int i = size; --i >= 0; ) {
        double w = theWeights[i];
        sum += elements[i] * w;
        weightsSum += w;
    }
    return sum / weightsSum;
}


typedef struct {
    double* elements; double* theWeights; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){1.0, 1.0, 1.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){0.5, 1.5, 2.0}, 3},
    {(double[]){-2.0, 0.0, 2.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){1.5, 2.5, 3.5}, (double[]){2.0, 3.0, 4.0}, 3},
    {(double[]){100.0, 200.0}, (double[]){0.1, 0.9}, 2},
    {(double[]){0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){5.0}, (double[]){10.0}, 1},
    {(double[]){-1.0, -2.0, -3.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){2.2, 4.4, 6.6}, (double[]){1.1, 2.2, 3.3}, 3},
    {(double[]){1.0, 3.0, 5.0, 7.0, 9.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){3.14, 6.28}, (double[]){0.5, 0.5}, 2},
    {(double[]){10.0, 20.0, 30.0, 40.0}, (double[]){0.25, 0.25, 0.25, 0.25}, 4},
    {(double[]){0.5, 1.5}, (double[]){2.0, 6.0}, 2},
    {(double[]){-10.0, 10.0}, (double[]){1.0, 1.0}, 2},
    {(double[]){1.0, 2.0, 3.0, 4.0}, (double[]){0.0, 1.0, 0.0, 1.0}, 4},
    {(double[]){7.0, 8.0, 9.0}, (double[]){1.0, 0.5, 1.5}, 3},
    {(double[]){15.0, 25.0, 35.0}, (double[]){3.0, 4.0, 5.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){1.1, 2.2, 3.3, 4.4}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){0.1, 0.2, 0.3}, (double[]){10.0, 20.0, 30.0}, 3},
    {(double[]){50.0, 60.0, 70.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){-5.0, 0.0, 5.0}, (double[]){2.0, 3.0, 2.0}, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){0.5, 1.0, 1.5}, 3},
    {(double[]){9.0, 18.0, 27.0}, (double[]){1.0, 2.0, 1.0}, 3},
    {(double[]){6.0, 12.0, 18.0, 24.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 4.0, 9.0, 16.0}, (double[]){1.0, 2.0, 3.0, 4.0}, 4},
    {(double[]){20.0, 40.0}, (double[]){0.3, 0.7}, 2},
    {(double[]){8.0, 6.0, 4.0, 2.0}, (double[]){4.0, 3.0, 2.0, 1.0}, 4},
    {(double[]){11.0, 22.0, 33.0}, (double[]){2.0, 3.0, 5.0}, 3}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    tf.elements = new double[tf.n];
    for (int i = 0; i < tf.n; ++i) {
        tf.elements[i] = tc.elements[i] * 2.0;
    }
    return tf;
}

int check(TestCase tc) {
    double Os = weightedMean(tc.elements, tc.theWeights, tc.n);
    TestCase Tf_case = change(tc);
    double Of = weightedMean(Tf_case.elements, Tf_case.theWeights, Tf_case.n);
    int is_valid = 0;
    if (fabs(2.0 * Os - Of) < 1e-9) {
        is_valid = 1;
    }
    delete[] Tf_case.elements;
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