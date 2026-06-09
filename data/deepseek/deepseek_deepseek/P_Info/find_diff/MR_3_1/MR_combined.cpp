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
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){10, 20}, (int[]){5, 15}, 2},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){-1, -2, -3}, (int[]){-4, -5, -6}, 3},
    {(int[]){100, 200}, (int[]){50, 150}, 2},
    {(int[]){7}, (int[]){3}, 1},
    {(int[]){15, 25, 35}, (int[]){10, 20, 30}, 3},
    {(int[]){-10, 10}, (int[]){-5, 5}, 2},
    {(int[]){2, 4, 6, 8}, (int[]){1, 3, 5, 7}, 4},
    {(int[]){0}, (int[]){100}, 1},
    {(int[]){50, 60, 70}, (int[]){20, 30, 40}, 3},
    {(int[]){-100, -200}, (int[]){-50, -250}, 2},
    {(int[]){9, 18, 27}, (int[]){6, 12, 18}, 3},
    {(int[]){33, 66}, (int[]){11, 22}, 2},
    {(int[]){1, 3, 5, 7, 9}, (int[]){0, 2, 4, 6, 8}, 5},
    {(int[]){-7, -14, -21}, (int[]){-3, -6, -9}, 3},
    {(int[]){1000, 2000}, (int[]){500, 1500}, 2},
    {(int[]){12, 24, 36, 48}, (int[]){6, 12, 18, 24}, 4},
    {(int[]){-25, 0, 25}, (int[]){-10, 10, 0}, 3},
    {(int[]){8, 16, 24, 32, 40}, (int[]){4, 8, 12, 16, 20}, 5},
    {(int[]){99, 88, 77}, (int[]){66, 55, 44}, 3},
    {(int[]){-1, 0, 1}, (int[]){1, 0, -1}, 3},
    {(int[]){45, 90}, (int[]){15, 30}, 2},
    {(int[]){6, 12, 18, 24, 30, 36}, (int[]){1, 2, 3, 4, 5, 6}, 6},
    {(int[]){-50, 50, -50}, (int[]){-25, 25, -25}, 3},
    {(int[]){19, 38, 57}, (int[]){9, 18, 27}, 3},
    {(int[]){100, 101, 102}, (int[]){1, 2, 3}, 3},
    {(int[]){-99, -88, -77, -66}, (int[]){-33, -22, -11, 0}, 4},
    {(int[]){14, 28, 42, 56, 70}, (int[]){7, 14, 21, 28, 35}, 5},
    {(int[]){0, -10, 10, -20}, (int[]){5, -5, 15, -15}, 4}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int k = 5; // 示例常数 k
    int* new_b = new int[tf.na];
    for (int i = 0; i < tf.na; i++) {
        new_b[i] = tf.b[i] + k;
    }
    tf.b = new_b;
    return tf;
}

int check(TestCase tc) {
    int* Os = find_diff(tc.a, tc.b, tc.na);
    TestCase Tf_case = change(tc);
    int* Of = find_diff(Tf_case.a, Tf_case.b, Tf_case.na);
    int k = 5;
    int is_valid = 1;
    for (int i = 0; i < tc.na; i++) {
        if (Os[i] != Of[i] + k) {
            is_valid = 0;
            break;
        }
    }
    delete[] Tf_case.b;
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