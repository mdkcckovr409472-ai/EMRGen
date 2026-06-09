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
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){5, 4, 3, 2, 1}, 5},
    {(int[]){-10, -5, 0, 5, 10}, 5},
    {(int[]){42}, 1},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){1, 3, 5, 7, 9, 2, 4, 6, 8}, 9},
    {(int[]){100, 200, 150}, 3},
    {(int[]){-1, -2, -3, -100}, 4},
    {(int[]){7, 7, 7, 7, 7}, 5},
    {(int[]){-5, 10, -5, 20, -5}, 5},
    {(int[]){1, 2}, 2},
    {(int[]){999, 998, 997}, 3},
    {(int[]){0, -1, 1, -2, 2}, 5},
    {(int[]){15, 30, 45, 60, 75, 90}, 6},
    {(int[]){-1000, -500, -750}, 3},
    {(int[]){2, 4, 8, 16, 32, 64}, 6},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10},
    {(int[]){1, 100, 50, 100, 1}, 5},
    {(int[]){-3, -2, -1, 0, 1, 2, 3}, 7},
    {(int[]){25}, 1},
    {(int[]){10, 20, 30, 20, 10}, 5},
    {(int[]){-8, -4, -12, -1}, 4},
    {(int[]){6, 2, 9, 1, 8}, 5},
    {(int[]){0, 1000, 500}, 3},
    {(int[]){-99, 0, 99}, 3},
    {(int[]){11, 22, 33, 44, 55, 66}, 6},
    {(int[]){1, 2, 1, 2, 1, 2}, 6},
    {(int[]){-20, -10, -30}, 3},
    {(int[]){50, 60, 70, 80, 90, 100}, 6},
    {(int[]){4, 3, 2, 1, 5}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        for (int i = 0; i < tf.n - 1; ++i) {
            int j = i + rand() % (tf.n - i);
            int temp = tf.a[i];
            tf.a[i] = tf.a[j];
            tf.a[j] = temp;
        }
    }
    return tf;
}

int check(TestCase tc) {
    int Os = find_max(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = find_max(Tf_case.a, Tf_case.n);
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