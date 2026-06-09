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


int partition(double work[], int begin, int end, int pivot) {
    double value = work[pivot];
    work[pivot] = work[begin];
    int i = begin + 1;
    int j = end - 1;
    while (i < j) {
        while (i < j && work[j] > value) {
            --j;
        }
        while (i < j && work[i] < value) {
            ++i;
        }
        if (i < j) {
            double tmp = work[i];
            work[i++] = work[j];
            work[j--] = tmp;
        }
    }
    if (i >= end || work[i] > value) {
        --i;
    }
    work[begin] = work[i];
    work[i] = value;
    return i;
}


typedef struct {
    double* work; int begin; int end; int pivot;
} TestCase;

TestCase test_cases[] = {
    { (double[]){5.0, 2.0, 8.0, 6.0, 3.0}, 0, 5, 2 },
    { (double[]){1.0, 4.0, 3.0, 2.0, 5.0}, 0, 5, 1 },
    { (double[]){10.0, -1.0, 7.0, 3.0, 0.0, 2.0}, 1, 5, 3 },
    { (double[]){0.0, 0.0, 0.0, 0.0}, 0, 4, 2 },
    { (double[]){9.5, -3.2, 4.1, 6.6, -2.0, 7.7}, 0, 6, 5 },
    { (double[]){2.5, 3.5, 1.5, 4.5, 0.5}, 0, 5, 0 },
    { (double[]){8.0, 6.0, 7.0, 5.0, 9.0, 1.0, 2.0}, 2, 7, 4 },
    { (double[]){3.3, 2.2, 1.1, 4.4, 5.5}, 1, 5, 3 },
    { (double[]){100.0, -50.0, 25.0, -75.0, 0.0}, 0, 5, 4 },
    { (double[]){1.0, 2.0, 3.0, 4.0, 5.0}, 0, 5, 2 },
    { (double[]){5.0, 4.0, 3.0, 2.0, 1.0}, 0, 5, 2 },
    { (double[]){7.0, 7.0, 2.0, 7.0, 5.0, 7.0}, 0, 6, 3 },
    { (double[]){-10.0, 20.0, -30.0, 40.0, -50.0, 60.0}, 0, 6, 1 },
    { (double[]){0.1, -0.2, 0.3, -0.4, 0.5}, 0, 5, 2 },
    { (double[]){3.14, 2.71, 1.41, 1.73, 2.58}, 0, 5, 0 },
    { (double[]){9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}, 0, 9, 8 },
    { (double[]){1.5, 2.5, 1.5, 2.5, 1.5}, 0, 5, 1 },
    { (double[]){-5.0, -10.0, -3.0, -8.0, -1.0}, 0, 5, 3 },
    { (double[]){0.0, 100.0, -100.0, 50.0, -50.0}, 0, 5, 2 },
    { (double[]){2.0, 2.0, 2.0, 2.0, 2.0}, 0, 5, 4 },
    { (double[]){-1.0, 1.0, -1.0, 1.0, -1.0, 1.0}, 0, 6, 5 },
    { (double[]){10.0, 20.0, 30.0, 40.0, 5.0, 35.0}, 2, 6, 4 },
    { (double[]){3.0, 1.0, 4.0, 1.5, 2.5, 0.5}, 1, 5, 2 },
    { (double[]){6.0, 2.0, 8.0, 3.0, 7.0, 4.0, 5.0}, 0, 7, 6 },
    { (double[]){-2.0, -3.0, -1.0, -4.0, -5.0}, 0, 5, 2 },
    { (double[]){0.0, 1.0, 0.0, 1.0, 0.0}, 0, 5, 1 },
    { (double[]){12.0, 6.0, 18.0, 3.0, 9.0, 15.0}, 0, 6, 3 },
    { (double[]){4.0, 5.0, 6.0, 7.0, 8.0}, 0, 5, 4 },
    { (double[]){8.0, 7.0, 6.0, 5.0, 4.0}, 0, 5, 1 },
    { (double[]){1.0, 3.0, 2.0, 4.0, 0.0, 5.0}, 0, 6, 0 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Add 1.0 to each element in work array to form follow-up input
    for(int i = tf.begin; i < tf.end; ++i) {
        tf.work[i] += 1.0;
    }
    return tf;
}

int check(TestCase tc) {
    // Extract source input
    double* work_s = tc.work;
    int begin = tc.begin;
    int end = tc.end;
    int pivot = tc.pivot;

    // Allocate and copy source input array since partition modifies it
    int length = end - begin;
    double* work_copy1 = new double[length];
    for(int i = 0; i < length; ++i) {
        work_copy1[i] = work_s[begin + i];
    }

    // Call partition on source input (Os)
    int Os = partition(work_copy1, 0, length, pivot - begin);

    // Create follow-up test case Tf
    TestCase Tf_case = change(tc);

    // Allocate and copy Tf_case.work array for partition since partition modifies its array
    double* work_copy2 = new double[length];
    for(int i = 0; i < length; ++i) {
        work_copy2[i] = Tf_case.work[begin + i];
    }

    // Call partition on follow-up input (Of)
    int Of = partition(work_copy2, 0, length, pivot - begin);

    // Free allocated memory for copies
    delete[] work_copy1;
    delete[] work_copy2;

    // Before returning, revert changes done in change() by subtracting 1.0 to restore original tc.work
    for(int i = tf.begin; i < tf.end; ++i) {
        tc.work[i] -= 1.0;
    }

    // Verify if Os and Of satisfy the MR: Os == Of
    int is_valid = (Os == Of) ? 1 : 0;

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