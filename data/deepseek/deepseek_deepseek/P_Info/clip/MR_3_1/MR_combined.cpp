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


int* clip(int a[], int lowerLim, int upperLim, int n) {
    static int r[100];
        for (int i = 0; i < n; i++) {
            if (a[i] < lowerLim) {
                r[i] = lowerLim;
            } else {
                if (a[i] > upperLim) {
                    r[i] = upperLim;
                } else {
                    r[i] = a[i];
                }
            }
        }
        return r;
    }
    


typedef struct {
    int* a; int lowerLim; int upperLim; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){10, 20, 30}, 15, 25, 3},
    {(int[]){5, 12, 18, 7}, 10, 15, 4},
    {(int[]){-3, 0, 8, -1, 4}, 0, 5, 5},
    {(int[]){100, 200, 150}, 120, 180, 3},
    {(int[]){22, 33, 44, 55}, 30, 50, 4},
    {(int[]){7}, 5, 10, 1},
    {(int[]){-10, -5, 0, 5, 10}, -7, 7, 5},
    {(int[]){14, 19, 23, 28}, 18, 25, 4},
    {(int[]){50, 60, 70, 80, 90}, 65, 85, 5},
    {(int[]){-20, -15, -10}, -18, -12, 3},
    {(int[]){0, 1, 2, 3, 4, 5}, 1, 4, 6},
    {(int[]){99, 101, 98, 102}, 100, 101, 4},
    {(int[]){45, 67, 89, 23}, 50, 80, 4},
    {(int[]){6, 7, 8, 9, 10}, 6, 10, 5},
    {(int[]){-50, 50, -25, 25}, -30, 30, 4},
    {(int[]){17, 29, 31, 42}, 20, 40, 4},
    {(int[]){123, 456, 789}, 200, 700, 3},
    {(int[]){11, 22, 33, 44, 55, 66}, 25, 60, 6},
    {(int[]){-1, -2, -3, -4}, -3, -1, 4},
    {(int[]){80, 85, 90, 95, 100}, 82, 97, 5},
    {(int[]){37, 52, 48, 61}, 40, 60, 4},
    {(int[]){999, 1001, 998, 1002}, 1000, 1001, 4},
    {(int[]){0, 10, 20, 30, 40}, 5, 35, 5},
    {(int[]){-100, 0, 100}, -50, 50, 3},
    {(int[]){71, 82, 93, 64, 75}, 70, 90, 5},
    {(int[]){19, 27, 35, 43}, 20, 40, 4},
    {(int[]){150, 250, 350}, 200, 300, 3},
    {(int[]){8, 16, 24, 32}, 10, 30, 4},
    {(int[]){-9, 9, -8, 8, -7, 7}, -8, 8, 6},
    {(int[]){55, 66, 77, 88, 99}, 60, 95, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* reversed_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        reversed_a[i] = tc.a[tc.n - 1 - i];
    }
    tf.a = reversed_a;
    return tf;
}

int check(TestCase tc) {
    int* Os = clip(tc.a, tc.lowerLim, tc.upperLim, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = clip(Tf_case.a, Tf_case.lowerLim, Tf_case.upperLim, Tf_case.n);
    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] != Of[tc.n - 1 - i]) {
            is_valid = 0;
            break;
        }
    }
    delete[] Tf_case.a;
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