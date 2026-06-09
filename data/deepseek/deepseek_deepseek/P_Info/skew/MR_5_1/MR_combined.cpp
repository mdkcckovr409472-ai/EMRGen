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


double skew(double data[], int n) {
    double sum = 0;
    double sumPD = 0;
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
        sumSq += data[i] * data[i];
    }
    double mean = sum / n;
    double standardDeviation = sqrt((sumSq - mean * sum) / n);
    for (int i = 0; i < n; i++) {
        sumPD += pow(data[i] - mean, 3);
    }
    double moment3 = sumPD / n;
    
    return moment3 / (standardDeviation * standardDeviation * standardDeviation);
}



typedef struct {
    double* data; int n;
} TestCase;

TestCase test_cases[] = {
    {(double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 5},
    {(double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 5},
    {(double[]){1.0, 1.0, 1.0, 1.0, 1.0}, 5},
    {(double[]){-2.0, -1.0, 0.0, 1.0, 2.0}, 5},
    {(double[]){0.0, 0.0, 0.0, 0.0}, 4},
    {(double[]){10.5, 20.3, 15.7}, 3},
    {(double[]){-10.5, -20.3, -15.7}, 3},
    {(double[]){1.0, 2.0, 3.0}, 3},
    {(double[]){3.0, 2.0, 1.0}, 3},
    {(double[]){100.0, 200.0, 300.0}, 3},
    {(double[]){-100.0, -200.0, -300.0}, 3},
    {(double[]){0.1, 0.2, 0.3, 0.4}, 4},
    {(double[]){-0.1, -0.2, -0.3, -0.4}, 4},
    {(double[]){2.5, 7.5, 12.5, 17.5, 22.5}, 5},
    {(double[]){22.5, 17.5, 12.5, 7.5, 2.5}, 5},
    {(double[]){1.0, 4.0, 9.0, 16.0}, 4},
    {(double[]){16.0, 9.0, 4.0, 1.0}, 4},
    {(double[]){-5.0, 0.0, 5.0}, 3},
    {(double[]){5.0, 0.0, -5.0}, 3},
    {(double[]){1.5, 2.5, 3.5, 4.5, 5.5, 6.5}, 6},
    {(double[]){6.5, 5.5, 4.5, 3.5, 2.5, 1.5}, 6},
    {(double[]){8.0}, 1},
    {(double[]){-8.0}, 1},
    {(double[]){0.0}, 1},
    {(double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0}, 6},
    {(double[]){2.0, 1.0, 2.0, 1.0, 2.0, 1.0}, 6},
    {(double[]){10.0, 20.0, 30.0, 40.0, 50.0}, 5},
    {(double[]){50.0, 40.0, 30.0, 20.0, 10.0}, 5},
    {(double[]){-1.0, -2.0, -3.0, -4.0, -5.0}, 5},
    {(double[]){-5.0, -4.0, -3.0, -2.0, -1.0}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    std::sort(tf.data, tf.data + tf.n, std::greater<double>());
    return tf;
}

int check(TestCase tc) {
    double Os = skew(tc.data, tc.n);
    TestCase Tf_case = change(tc);
    double Of = skew(Tf_case.data, Tf_case.n);
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