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


int* array_copy(int a[], int n) {
    if (a == NULL || n <= 0) {
        return NULL;
    }


    int* copy = (int*)malloc(n * sizeof(int));
    if (copy == NULL) {
        return NULL;  
    }


    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }

    return copy;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){7, -3, 42, 150, -60}, 5},
    {(int[]){300, -1000, 45, 78, -22, 13}, 6},
    {(int[]){99, -150, 23, 42, 107}, 5},
    {(int[]){1, -1, 3, -3, 5, -5, 7}, 7},
    {(int[]){22, 0, 51, -250, 130}, 5},
    {(int[]){-444, 222, 333, -555, 0, 1234}, 6},
    {(int[]){150, -150, 300, -300, 600, -600}, 6},
    {(int[]){12, 1300, -500, 220, -10}, 5},
    {(int[]){4000, 100, 0, -100, 50, -500}, 6},
    {(int[]){-900, 435, -870, 220, 180, -60, 70}, 7},
    {(int[]){130, 42, -17, 88, 255}, 5},
    {(int[]){75, 33, 12, -25, 150, -77}, 6},
    {(int[]){5, 200, -200, 1000, -1000}, 5},
    {(int[]){39, -300, 400, -500, 600}, 5},
    {(int[]){1300, 1400, 1500, -1250, -1300}, 5},
    {(int[]){80, -70, 60, -50, 40, -30}, 6},
    {(int[]){123, 234, 345, 456, 567, 678, 789}, 7},
    {(int[]){0, 5, -5, 10, -10, 15, -15}, 7},
    {(int[]){250, -125, 375, -375, 500}, 5},
    {(int[]){-100, 200, -300, 400, -500, 600}, 6},
    {(int[]){3, 6, 2, 8, 7, 9, 1, 4}, 8},
    {(int[]){11, -20, 33, -44, 55}, 5},
    {(int[]){100, 200, 300, -400, -500}, 5},
    {(int[]){9, -18, 27, -36, 45, -54}, 6},
    {(int[]){13, 26, -39, 52, -65}, 5},
    {(int[]){210, -420, 630, -840, 1050}, 5},
    {(int[]){140, 280, -420, 560, -700, 840}, 6},
    {(int[]){7, 14, 21, 28, 35}, 5},
    {(int[]){-123, 234, -345, 456, -567, 678}, 6},
    {(int[]){15, -30, 45, -60, 75}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;

    if (tc.a == NULL || tc.n <= 0) {
        tf.a = NULL;
        tf.n = 0;
        return tf;
    }

    int* new_array = (int*)malloc(tc.n * sizeof(int));
    if (new_array == NULL) {
        tf.a = NULL;
        tf.n = 0;
        return tf;
    }

    for (int i = 0; i < tc.n; i++) {
        new_array[i] = tc.a[i] - 1;
    }

    tf.a = new_array;
    tf.n = tc.n;

    return tf;
}

int check(TestCase tc) {
    if (tc.a == NULL || tc.n <= 0) return 1;

    int* Os = array_copy(tc.a, tc.n);
    if (Os == NULL) return 0;

    TestCase Tf_case = change(tc);
    if (Tf_case.a == NULL || Tf_case.n <= 0) {
        free(Os);
        return 0;
    }

    int* Of = array_copy(Tf_case.a, Tf_case.n);
    free(Tf_case.a);

    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 0;
    if (Os != NULL && Of != NULL) {
        int equal = 1;
        for (int i = 0; i < tc.n; i++) {
            if (Os[i] != Of[i]) {
                equal = 0;
                break;
            }
        }
        if (!equal) {
            is_valid = 1;
        }
    }

    free(Os);
    free(Of);

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