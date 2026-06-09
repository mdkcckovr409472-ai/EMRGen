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


double winsorizedMean(double elements[], int left, int right, int n) {
    qsort(elements, n, sizeof(double), [](const void *a, const void *b) -> int {
        double diff = *(double *)a - *(double *)b;
        if (diff > 0) return 1;
        else if (diff < 0) return -1;
        else return 0;
    });

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += elements[i];
    }

    double mean = sum / n;

    if (n > 0 && left >= 0 && left < n) {
        double leftElement = elements[left];
        for (int i = 0; i < left; ++i) {
            mean += (leftElement - elements[i]) / n;
        }
    }

    if (n > 0 && right >= 0 && right < n && (n - 1 - right) >= 0) {
        double rightElement = elements[n - 1 - right];
        for (int i = 0; i < right; ++i) {
            mean += (rightElement - elements[n - 1 - i]) / n;
        }
    }

    return mean;
}

typedef struct {
    double* elements; int left; int right; int n;
} TestCase;

TestCase test_cases[] = {
    { (double[]){3.0, 1.0, 2.0}, 0, 0, 3 },
    { (double[]){3.0, 1.0, 2.0}, 1, 0, 3 },
    { (double[]){3.0, 1.0, 2.0}, 0, 1, 3 },
    { (double[]){3.0, 1.0, 2.0}, 1, 1, 3 },
    { (double[]){5.0, 5.0, 2.0, 8.0, 5.0}, 2, 1, 5 },
    { (double[]){-3.5, 2.2, 0.0, -1.1, 4.4, 3.3}, 2, 2, 6 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 0, 0, 5 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 2, 0, 5 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 0, 2, 5 },
    { (double[]){10.0, -5.0, 3.0, 7.0, 2.0}, 2, 2, 5 },
    { (double[]){1.0, 9.0, -4.0, 6.0, 2.0, 8.0}, 3, 1, 6 },
    { (double[]){1.0, 9.0, -4.0, 6.0, 2.0, 8.0}, 1, 3, 6 },
    { (double[]){4.0, -2.0, 7.0, 1.0, 5.0, 3.0, 6.0}, 3, 3, 7 },
    { (double[]){0.5, 2.5, -1.5, 4.0}, 3, 0, 4 },
    { (double[]){0.5, 2.5, -1.5, 4.0}, 0, 3, 4 },
    { (double[]){0.0, -2.0, 3.0, 0.0, 5.0}, 2, 2, 5 },
    { (double[]){7.0, 7.0, 7.0, 7.0}, 1, 1, 4 },
    { (double[]){12.0, 8.0, 15.0, 9.0, 11.0, 10.0}, 2, 1, 6 },
    { (double[]){0.1, 0.2, 0.3, 0.4, 0.5}, 1, 2, 5 },
    { (double[]){5.0, -5.0}, 0, 0, 2 },
    { (double[]){5.0, -5.0}, 1, 0, 2 },
    { (double[]){5.0, -5.0}, 0, 1, 2 },
    { (double[]){9.0, 1.0, 5.0}, 2, 2, 3 },
    { (double[]){3.3, -1.2, 4.5, 0.0, 2.2, -3.3, 5.5, 1.1}, 3, 2, 8 },
    { (double[]){6.6, -2.2, 3.3, 8.8, 0.0, -5.5, 7.7, 2.2, 4.4}, 4, 4, 9 },
    { (double[]){5.0, 1.0, 8.0, 3.0, 10.0, 2.0, 9.0, 4.0, 7.0, 6.0}, 5, 5, 10 },
    { (double[]){-1.0, -3.0, -2.0}, 1, 1, 3 },
    { (double[]){0.0, -1.0, 2.0, -2.0, 3.0}, 2, 1, 5 },
    { (double[]){4.0, 1.0, 5.0, 2.0, 6.0, 3.0}, 2, 2, 6 },
    { (double[]){7.0, 2.0, 9.0, 4.0, 1.0}, 0, 0, 5 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Sort the elements array in ascending order to construct Tf
    // Since elements points to externally allocated array,
    // allocate new array for sorted elements and assign to tf.elements

    double* sortedElements = new double[tc.n];
    for (int i = 0; i < tc.n; i++) {
        sortedElements[i] = tc.elements[i];
    }

    // Using std::sort since we can't use lambda qsort comparator easily here
    std::sort(sortedElements, sortedElements + tc.n);

    tf.elements = sortedElements;

    // left, right, n remain unchanged
    return tf;
}

int check(TestCase tc) {
    // Source input
    double* Ts = tc.elements;
    int left = tc.left;
    int right = tc.right;
    int n = tc.n;

    // Source output
    double Os = winsorizedMean(Ts, left, right, n);

    // Construct follow-up test case
    TestCase Tf_case = change(tc);
    double* Tf = Tf_case.elements;

    // Follow-up output
    double Of = winsorizedMean(Tf, Tf_case.left, Tf_case.right, Tf_case.n);

    // Verify MR: Os == Of (allowing epsilon tolerance for floating point)
    const double epsilon = 1e-12;
    int is_valid = (std::abs(Os - Of) <= epsilon) ? 1 : 0;

    // Free dynamically allocated memory from change()
    if (Tf != Ts) {
        delete[] Tf;
        Tf_case.elements = nullptr;
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