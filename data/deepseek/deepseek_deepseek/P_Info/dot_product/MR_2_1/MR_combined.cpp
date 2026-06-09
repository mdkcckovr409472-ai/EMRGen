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


int dot_product(int a[], int b[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
            sum += a[i] * b[i];
        }
    return sum;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1, 2, 3}, (int[]){4, 5, 6}, 3},
    {(int[]){0, 0, 0}, (int[]){0, 0, 0}, 3},
    {(int[]){1}, (int[]){1}, 1},
    {(int[]){-1, 2}, (int[]){3, -4}, 2},
    {(int[]){10, 20, 30, 40}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){-5, -10}, (int[]){-2, -3}, 2},
    {(int[]){100}, (int[]){-100}, 1},
    {(int[]){1, 0, -1}, (int[]){0, 5, 0}, 3},
    {(int[]){2, 4, 6, 8, 10}, (int[]){1, 1, 1, 1, 1}, 5},
    {(int[]){3, 6, 9}, (int[]){-1, -2, -3}, 3},
    {(int[]){1, 2, 3, 4, 5, 6}, (int[]){6, 5, 4, 3, 2, 1}, 6},
    {(int[]){7}, (int[]){8}, 1},
    {(int[]){0, 100, 200}, (int[]){300, 0, 400}, 3},
    {(int[]){-1, -2, -3, -4}, (int[]){-1, -2, -3, -4}, 4},
    {(int[]){15, 25}, (int[]){4, -6}, 2},
    {(int[]){9, 8, 7}, (int[]){1, 2, 3}, 3},
    {(int[]){1, 1, 1, 1}, (int[]){2, 2, 2, 2}, 4},
    {(int[]){-10, 20, -30}, (int[]){1, -2, 3}, 3},
    {(int[]){5, 10, 15, 20, 25, 30}, (int[]){2, 2, 2, 2, 2, 2}, 6},
    {(int[]){12, 24}, (int[]){0, 0}, 2},
    {(int[]){6, 12, 18, 24}, (int[]){-1, 1, -1, 1}, 4},
    {(int[]){100, 200, 300}, (int[]){1, 0, -1}, 3},
    {(int[]){2, 3, 5, 7}, (int[]){11, 13, 17, 19}, 4},
    {(int[]){-8, -6, -4, -2, 0}, (int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){1, 4, 9, 16}, (int[]){1, 2, 3, 4}, 4},
    {(int[]){50, 60}, (int[]){-10, -20}, 2},
    {(int[]){0, 1, 2, 3, 4, 5, 6}, (int[]){7, 6, 5, 4, 3, 2, 1}, 7},
    {(int[]){-3, 0, 3}, (int[]){5, 10, 15}, 3},
    {(int[]){8, 4, 2, 1}, (int[]){1, 2, 4, 8}, 4},
    {(int[]){11, 22, 33}, (int[]){0, 0, 0}, 3}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int c = 2;
    int* new_a = new int[tf.n];
    for (int i = 0; i < tf.n; i++) {
        new_a[i] = tf.a[i] * c;
    }
    tf.a = new_a;
    return tf;
}

int check(TestCase tc) {
    int Os = dot_product(tc.a, tc.b, tc.n);
    TestCase Tf_case = change(tc);
    int Of = dot_product(Tf_case.a, Tf_case.b, Tf_case.n);
    int c = 2;
    int is_valid = 0;
    if (Of == c * Os) {
        is_valid = 1;
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