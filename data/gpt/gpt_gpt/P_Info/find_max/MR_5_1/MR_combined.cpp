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


int find_max(int a[], int n) {
    int max = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1},
    {(int[]){-3, 7, 2}, 3},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){10, -5, 10, -5}, 4},
    {(int[]){3, 3, 3}, 3},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){8, 1, 6, 3, 7, 9, 2, 5, 4}, 9},
    {(int[]){2, 2, 5, 1, 5, 3}, 6},
    {(int[]){-10, 0, 10}, 3},
    {(int[]){4, -2, 4, -2, 4}, 5},
    {(int[]){7, 7, 6, 6, 5, 5}, 6},
    {(int[]){1, 2, 3, 2, 1}, 5},
    {(int[]){9, -9, 9, -9, 0}, 5},
    {(int[]){5, 1, 4, 2, 3, 0}, 6},
    {(int[]){0, 5, 0, 5, 0, 5}, 6},
    {(int[]){-3, -3, -2, -2, -1}, 5},
    {(int[]){12, 12, 12, 12}, 4},
    {(int[]){-7, 3, -7, 3, -7}, 5},
    {(int[]){6, 1, 6, 1, 6, 1}, 6},
    {(int[]){-4, 0, 4, -4, 0, 4}, 6},
    {(int[]){2, 8, 5, 3, 9, 1, 7}, 7},
    {(int[]){-5, -10, -3, -8, -2}, 5},
    {(int[]){15, 5, 15, 5, 15, 5, 15}, 7},
    {(int[]){0}, 1},
    {(int[]){-1, 1, -1, 1, -1, 1}, 6},
    {(int[]){3, -3, 3, -3, 3}, 5},
    {(int[]){8, 8, 8, 7, 9}, 5},
    {(int[]){-6, -6, -6, -6, -5}, 5},
    {(int[]){4, 2, 4, 2, 4, 2, 4, 2}, 8},
    {(int[]){5, -2, 5, -2, 5, -2, 5}, 7}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    // Allocate new array for sorted data
    int* sorted_array = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        sorted_array[i] = tf.a[i];
    }
    // Sort the array in ascending order
    for (int i = 0; i < tf.n - 1; i++) {
        for (int j = i + 1; j < tf.n; j++) {
            if (sorted_array[i] > sorted_array[j]) {
                int temp = sorted_array[i];
                sorted_array[i] = sorted_array[j];
                sorted_array[j] = temp;
            }
        }
    }
    tf.a = sorted_array;
    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input (Ts)
    int* Ts = tc.a;
    int n = tc.n;
    // (2) Call the function under test from [Information 1] to get the source output (Os)
    int Os = find_max(Ts, n);
    // (3) Call the change function to construct the follow-up test case object
    TestCase Tf_case = change(tc);
    // (4) Extract the follow-up input and get the follow-up output (Of)
    int Of = find_max(Tf_case.a, Tf_case.n);
    // (5) Verify whether Os and Of satisfy the metamorphic relation based on [Information 2]
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    // (6) Free Tf_case or any dynamic memory generated during the process
    if (Tf_case.a != tc.a) {
        delete[] Tf_case.a;
    }
    // (7) Return the verification result
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