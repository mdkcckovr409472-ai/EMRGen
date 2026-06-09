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


int* selection_sort(int list[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,list,n*sizeof(int));
    int i;
    int j;
    int min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (cp1[j] < cp1[min]) {
                min = j;
            }
        }
        int tmp = cp1[i];
        cp1[i] = cp1[min];
        cp1[min] = tmp;
    }
    return cp1;
}


typedef struct {
    int* list; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0 },
    { (int[]){5}, 1 },
    { (int[]){1, 2}, 2 },
    { (int[]){2, 1}, 2 },
    { (int[]){3, 1, 2}, 3 },
    { (int[]){1, 2, 3}, 3 },
    { (int[]){3, 2, 1}, 3 },
    { (int[]){2, 2, 1, 3}, 4 },
    { (int[]){7, 7, 7, 7}, 4 },
    { (int[]){-3, -1, -2}, 3 },
    { (int[]){0, -5, 5, 2, -1}, 5 },
    { (int[]){0, 0, 1, -1}, 4 },
    { (int[]){8, 3, 5, 2, 9, 1}, 6 },
    { (int[]){4, 2, 4, 2, 5}, 5 },
    { (int[]){1, 2, 3, 4, 5, 6, 7}, 7 },
    { (int[]){7, 6, 5, 4, 3, 2, 1}, 7 },
    { (int[]){10, -2, 8, -5, 3}, 5 },
    { (int[]){15, 3, 12, 7, 9, 0}, 6 },
    { (int[]){100, 20, 50, -30}, 4 },
    { (int[]){-100, 0, 50, -20}, 4 },
    { (int[]){5, -1, 3, 8, -2, 0, 7, 2}, 8 },
    { (int[]){1, 3, 3, 2, 5, 5, 4, 2, 1}, 9 },
    { (int[]){10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10 },
    { (int[]){3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, 10 },
    { (int[]){0, 5, 0, 5, 0}, 5 },
    { (int[]){-5, -4, -3, -2, -1}, 5 },
    { (int[]){-50, 20, -30, 40, -10}, 5 },
    { (int[]){12, -1, 6, -7, 3, 0, 9, -2, 8, 5, -3, 4}, 12 },
    { (int[]){0, 0, 0, 0, 0, 0}, 6 },
    { (int[]){-7}, 1 }
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    for (int i = 0; i < tf.n; i++) {
        tf.list[i] = tf.list[i] + 1;
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = selection_sort(tc.list, tc.n);
    if (Os == NULL) return 0;

    TestCase Tf_case = change(tc);
    int* Of = selection_sort(Tf_case.list, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        return 0;
    }

    int is_valid = 1;
    for (int i = 0; i < tc.n; i++) {
        if (Os[i] + 1 != Of[i]) {
            is_valid = 0;
            break;
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