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
    { (double[]){0.0}, 1 },
    { (double[]){1.0, 2.0, 3.0, 2.0, 1.0}, 5 },
    { (double[]){-1.5, -0.5, 0.0, 0.5, 1.5}, 5 },
    { (double[]){2.0, 2.0, 2.0, 2.0}, 4 },
    { (double[]){-3.0, -1.0, 0.0, 4.0, 5.0}, 5 },
    { (double[]){0.2, -0.4, 0.6, -0.8, 1.0}, 5 },
    { (double[]){5.0, 1.0, 4.0, 2.0, 3.0}, 5 },
    { (double[]){-2.0, -2.0, -1.0, 0.0, 1.0, 2.0}, 6 },
    { (double[]){0.0, 0.0, 0.0}, 3 },
    { (double[]){1.0, -1.0, 1.0, -1.0, 1.0}, 5 },
    { (double[]){3.5, 2.1, -4.2, 0.0, 1.7, -2.3}, 6 },
    { (double[]){-0.1, 0.2, -0.3, 0.4, -0.5}, 5 },
    { (double[]){10.0, -10.0, 10.0, -10.0}, 4 },
    { (double[]){0.5, 0.5, -0.5, -0.5}, 4 },
    { (double[]){1.2, 3.4, 5.6, 7.8}, 4 },
    { (double[]){-5.0, -3.0, -1.0, 1.0, 3.0, 5.0}, 6 },
    { (double[]){4.0, 1.0, 0.0, -1.0, -4.0}, 5 },
    { (double[]){2.5, -2.5, 2.5, -2.5, 0.0}, 5 },
    { (double[]){0.0, 1.0, 0.0, -1.0, 0.0}, 5 },
    { (double[]){-2.2, 3.3, -4.4, 5.5, -6.6}, 5 },
    { (double[]){1.0, 2.0, 1.0, 2.0, 1.0, 2.0}, 6 },
    { (double[]){-1.0, -2.0, -3.0, -2.0, -1.0}, 5 },
    { (double[]){0.9, 0.7, 0.5, 0.3, 0.1}, 5 },
    { (double[]){-0.9, -0.7, -0.5, -0.3, -0.1}, 5 },
    { (double[]){3.0, 3.0, -3.0, -3.0, 0.0}, 5 },
    { (double[]){1.0, 1.0, 1.0, 2.0, 2.0, 2.0}, 6 },
    { (double[]){-0.2, 0.0, 0.2, 0.4, -0.4}, 5 },
    { (double[]){5.5, -5.5, 5.5, -5.5, 5.5}, 5 },
    { (double[]){0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0}, 7 },
    { (double[]){1.1, -1.1, 2.2, -2.2, 3.3, -3.3}, 6 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;

    // Create a new array for tf.data to avoid modifying original data
    if (tc.n > 0) {
        double* newData = new double[tc.n];
        for(int i = 0; i < tc.n; i++) {
            newData[i] = tc.data[i];
        }
        // Sort newData in descending order
        for(int i = 0; i < tc.n - 1; i++) {
            for(int j = 0; j < tc.n - 1 - i; j++) {
                if(newData[j] < newData[j+1]) {
                    double tmp = newData[j];
                    newData[j] = newData[j+1];
                    newData[j+1] = tmp;
                }
            }
        }
        tf.data = newData;
    } else {
        tf.data = nullptr;
    }
    return tf;
}

int check(TestCase tc) {
    // (1) Extract source input
    double* Ts = tc.data;
    int n = tc.n;

    // (2) Call function under test for source output Os
    double Os = skew(Ts, n);

    // (3) Construct follow-up test case Tf
    TestCase Tf = change(tc);

    // (4) Call function under test for follow-up output Of
    double Of = 0.0;
    if (Tf.data != nullptr) {
        Of = skew(Tf.data, Tf.n);
    }

    // (5) Verify metamorphic relation Os == Of (allow small epsilon for floating comparison)
    int is_valid = 0;
    double epsilon = 1e-12;
    if (std::abs(Os - Of) < epsilon) {
        is_valid = 1;
    }

    // (6) Free any dynamic memory allocated in change()
    if (Tf.data != tc.data && Tf.data != nullptr) {
        delete[] Tf.data;
    }

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