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


int*  find_diff(int a[], int b[], int na) {
    static int c[1000];
    for (int i = 0; i < na; i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}


typedef struct {
    int* a; int* b; int na;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5, 2, -3}, (int[]){1, 4, -3}, 3},
    {(int[]){0}, (int[]){0}, 1},
    {(int[]){10, -10, 5, -5}, (int[]){5, -5, 5, -5}, 4},
    {(int[]){}, (int[]){}, 0},
    {(int[]){100, 200, 300}, (int[]){300, 200, 100}, 3},
    {(int[]){-1, -2, -3, -4}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){7, 14, 21}, (int[]){3, 6, 9}, 3},
    {(int[]){42, 0, -42}, (int[]){0, 0, 0}, 3},
    {(int[]){1, 1, 1, 1, 1}, (int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){9, 8, 7, 6, 5}, (int[]){5, 6, 7, 8, 9}, 5},
    {(int[]){123, -456, 789}, (int[]){321, -654, 987}, 3},
    {(int[]){0, 1, 0, 1}, (int[]){1, 0, 1, 0}, 4},
    {(int[]){15, 30, 45, 60}, (int[]){5, 10, 15, 20}, 4},
    {(int[]){-100, 50, -25}, (int[]){100, -50, 25}, 3},
    {(int[]){2, 4, 8, 16, 32, 64}, (int[]){1, 2, 4, 8, 16, 32}, 6},
    {(int[]){7}, (int[]){3}, 1},
    {(int[]){3, -3, 3, -3}, (int[]){-3, 3, -3, 3}, 4},
    {(int[]){0, -1, 2, -3, 4}, (int[]){0, 1, -2, 3, -4}, 5},
    {(int[]){5, 10, 15}, (int[]){5, 10, 15}, 3},
    {(int[]){99, 1, 99, 1}, (int[]){1, 99, 1, 99}, 4},
    {(int[]){-5, 0, 5}, (int[]){5, 0, -5}, 3},
    {(int[]){8, 6, 7, 5, 3, 0, 9}, (int[]){0, 1, 2, 3, 4, 5, 6}, 7},
    {(int[]){-10, -20, -30}, (int[]){-30, -20, -10}, 3},
    {(int[]){1000, -1000}, (int[]){-1000, 1000}, 2},
    {(int[]){1, 2, 3, 4, 5}, (int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){-1, 0, 1}, (int[]){1, 0, -1}, 3},
    {(int[]){11, 22, 33, 44}, (int[]){44, 33, 22, 11}, 4},
    {(int[]){0, 0, 0, 0, 0}, (int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){12345, -12345, 0}, (int[]){-12345, 12345, 0}, 3},
    {(int[]){7, 14, 21, 28}, (int[]){28, 21, 14, 7}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if(tf.b != nullptr && tf.na > 0) {
        // Since MR requires setting first element of b to INT_MAX,
        // but must reuse original array, so allocate new b to modify
        int* new_b = new int[tf.na];
        for(int i = 0; i < tf.na; i++) {
            new_b[i] = tf.b[i];
        }
        new_b[0] = INT_MAX;
        tf.b = new_b;
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = find_diff(tc.a, tc.b, tc.na);

    TestCase Tf_case = change(tc);
    int* Of = find_diff(Tf_case.a, Tf_case.b, Tf_case.na);

    int is_valid = 1;
    if(tc.na > 0) {
        if(Of[0] != tc.a[0] - INT_MAX) {
            is_valid = 0;
        }
        for(int i = 1; i < tc.na; i++) {
            if(Of[i] != Os[i]) {
                is_valid = 0;
                break;
            }
        }
    }

    if(Tf_case.b != tc.b) {
        delete[] Tf_case.b;
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