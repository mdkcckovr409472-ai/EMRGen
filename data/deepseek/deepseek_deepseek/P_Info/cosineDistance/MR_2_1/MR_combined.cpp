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


double cosineDistance(double p1[], double p2[], int n) {
    double dotProduct = 0.0;
    double lengthSquaredp1 = 0.0;
    double lengthSquaredp2 = 0.0;

    for (int i = 0; i < n; i++) {
        lengthSquaredp1 += p1[i] * p1[i];
        lengthSquaredp2 += p2[i] * p2[i];
        dotProduct += p1[i] * p2[i];
    }
    
    double denominator = sqrt(lengthSquaredp1) * sqrt(lengthSquaredp2);
    if (denominator < dotProduct) {
        denominator = dotProduct;
    }
    if (denominator == 0 && dotProduct == 0) {
        return 0;
    }
    return 1.0 - dotProduct / denominator;
}


typedef struct {
    double* p1; double* p2; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0}, (double[]){4.0, 5.0, 6.0}, 3},
    {(double[]){0.0, 0.0}, (double[]){0.0, 0.0}, 2},
    {(double[]){1.0}, (double[]){1.0}, 1},
    {(double[]){-1.0, -2.0}, (double[]){-3.0, -4.0}, 2},
    {(double[]){1.5, 2.5}, (double[]){3.5, 4.5}, 2},
    {(double[]){0.1, 0.2, 0.3}, (double[]){0.4, 0.5, 0.6}, 3},
    {(double[]){100.0, 200.0}, (double[]){300.0, 400.0}, 2},
    {(double[]){-1.0, 0.0, 1.0}, (double[]){1.0, 0.0, -1.0}, 3},
    {(double[]){2.0, 4.0, 8.0}, (double[]){1.0, 2.0, 4.0}, 3},
    {(double[]){3.0, 4.0}, (double[]){-4.0, 3.0}, 2},
    {(double[]){1.0, 1.0, 1.0, 1.0}, (double[]){1.0, 1.0, 1.0, 1.0}, 4},
    {(double[]){1.0, 0.0}, (double[]){0.0, 1.0}, 2},
    {(double[]){5.0}, (double[]){-5.0}, 1},
    {(double[]){0.5, 1.0, 1.5}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){10.0, 20.0, 30.0}, (double[]){2.0, 4.0, 6.0}, 3},
    {(double[]){-2.0, -4.0, -6.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){0.0, 1.0, 2.0}, (double[]){3.0, 4.0, 5.0}, 3},
    {(double[]){7.0, 8.0, 9.0, 10.0}, (double[]){11.0, 12.0, 13.0, 14.0}, 4},
    {(double[]){1.1, 2.2}, (double[]){3.3, 4.4}, 2},
    {(double[]){0.0, 0.0, 0.0, 0.0, 0.0}, (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){6.0, 7.0}, (double[]){8.0, 9.0}, 2},
    {(double[]){-1.5, -2.5}, (double[]){-3.5, -4.5}, 2},
    {(double[]){9.0, 18.0}, (double[]){2.0, 4.0}, 2},
    {(double[]){0.25, 0.5, 0.75}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){12.0, 24.0, 36.0}, (double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){0.0, 0.0, 1.0}, (double[]){0.0, 1.0, 0.0}, 3},
    {(double[]){15.0, 30.0}, (double[]){3.0, 6.0}, 2},
    {(double[]){-10.0, 20.0, -30.0}, (double[]){40.0, -50.0, 60.0}, 3}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    double c = 2.0;
    double* new_p2 = new double[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_p2[i] = tf.p2[i] * c;
    }
    tf.p2 = new_p2;
    return tf;
}

int check(TestCase tc) {
    double Os = cosineDistance(tc.p1, tc.p2, tc.n);
    TestCase Tf_case = change(tc);
    double Of = cosineDistance(Tf_case.p1, Tf_case.p2, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    delete[] Tf_case.p2;
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