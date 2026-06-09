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


int* elementwise_min(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }

    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n; i++) {
        result[i] = (a[i] < b[i]) ? a[i] : b[i];  }

    return result;
}


typedef struct {
    int* a; int* b; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5, 3, 9, 1}, (int[]){4, 8, 2, 7}, 4},
    {(int[]){100, 50, -30, 200}, (int[]){-20, 60, 0, 150}, 4},
    {(int[]){7, 14, 21, 28, 35}, (int[]){10, 5, 25, 15, 30}, 5},
    {(int[]){0, 500, 1000, -1000, 250}, (int[]){-500, 600, 900, 1100, 300}, 5},
    {(int[]){1234, 2345, 3456, 4567}, (int[]){4321, 3210, 2109, 1098}, 4},
    {(int[]){3, 3, 3, 3, 3}, (int[]){2, 2, 2, 2, 2}, 5},
    {(int[]){-1, -100, 50, 1000}, (int[]){0, -50, 100, 900}, 4},
    {(int[]){999, 888, 777, 666, 555}, (int[]){555, 666, 777, 888, 999}, 5},
    {(int[]){20, 10, 30, 60, 0}, (int[]){15, 25, 20, 40, 5}, 5},
    {(int[]){1500, -1500, 3000, -3000}, (int[]){-1000, 1000, -2000, 2000}, 4},
    {(int[]){7, 1, 5, 3}, (int[]){4, 6, 2, 8}, 4},
    {(int[]){15, 25, 35}, (int[]){10, 30, 25}, 3},
    {(int[]){100, 200, 300, 400}, (int[]){50, 250, 250, 350}, 4},
    {(int[]){-10, -20, -30, -40, -50}, (int[]){-15, -25, -20, -35, -55}, 5},
    {(int[]){1, 4, 9, 16, 25}, (int[]){2, 3, 8, 15, 24}, 5},
    {(int[]){5000, 10000, 15000}, (int[]){5500, 9000, 16000}, 3},
    {(int[]){60, 70, 80, 90}, (int[]){65, 75, 70, 95}, 4},
    {(int[]){200, 400, 600, 800, 1000}, (int[]){150, 450, 550, 750, 1100}, 5},
    {(int[]){5, 15, 25, 35}, (int[]){10, 10, 30, 30}, 4},
    {(int[]){8, 6, 4, 2, 0}, (int[]){7, 5, 3, 1, -1}, 5},
    {(int[]){123, 234, 345}, (int[]){321, 432, 543}, 3},
    {(int[]){-999, 999, 0}, (int[]){-1000, 1000, 1}, 3},
    {(int[]){42, 84, 168}, (int[]){21, 63, 126}, 3},
    {(int[]){3, 1, 4, 1, 5}, (int[]){9, 2, 6, 5, 3}, 5},
    {(int[]){11, 22, 33, 44}, (int[]){44, 33, 22, 11}, 4},
    {(int[]){1000, 2000, 3000}, (int[]){500, 2500, 3500}, 3},
    {(int[]){-5, -15, -25}, (int[]){0, -20, -10}, 3},
    {(int[]){7, 14, 21}, (int[]){8, 13, 22}, 3},
    {(int[]){60, 55, 50, 45}, (int[]){65, 50, 55, 40}, 4}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;

    if (tf.b != NULL && tf.n > 0) {
        int* new_b = (int*)malloc(tf.n * sizeof(int));
        if (new_b != NULL) {
            for (int i = 0; i < tf.n; i++) {
                new_b[i] = tf.b[i] + 1;
            }
            tf.b = new_b;
        }
    }

    return tf;
}

int check(TestCase tc) {
    if (tc.a == NULL || tc.b == NULL || tc.n <= 0) {
        return 0;
    }

    int* Os = elementwise_min(tc.a, tc.b, tc.n);
    if (Os == NULL) {
        return 0;
    }

    TestCase Tf_case = change(tc);

    if (Tf_case.b == NULL || Tf_case.n <= 0) {
        free(Os);
        return 0;
    }

    int* Of = elementwise_min(Tf_case.a, Tf_case.b, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        if (Tf_case.b != tc.b) free(Tf_case.b);
        return 0;
    }

    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (!(Os[i] <= Of[i])) {
            is_valid = 0;
            break;
        }
    }

    free(Os);
    free(Of);
    if (Tf_case.b != tc.b) {
        free(Tf_case.b);
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