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


int* insertion_sort(int array[], int n) {
    int* cp1 = (int*)malloc(n * sizeof(int));
    memcpy(cp1,array,n*sizeof(int));
    for (int i = 1; i < n; i++) {
        int j = i;
        int B = cp1[i];
        while (j > 0 && cp1[j - 1] > B) {
            cp1[j] = cp1[j - 1];
            j--;
        }
        cp1[j] = B;
        }
    
    return cp1;
}


typedef struct {
    int* array; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){1}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){5, 2, 4, 6, 1, 3}, 6},
    {(int[]){-1, -2, -3}, 3},
    {(int[]){-3, -2, -1}, 3},
    {(int[]){0, 0, 0}, 3},
    {(int[]){100}, 1},
    {(int[]){1, 3, 2}, 3},
    {(int[]){9, 7, 5, 3, 1}, 5},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){4}, 1},
    {(int[]){-5, 10, 0, -10, 5}, 5},
    {(int[]){2, 2, 1, 1, 3, 3}, 6},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1, 3}, 3},
    {(int[]){3, 1, 2}, 3},
    {(int[]){10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10},
    {(int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
    {(int[]){5, 1, 4, 2, 8}, 5},
    {(int[]){0, 1, 0, 1}, 4},
    {(int[]){-100, 100, 0}, 3},
    {(int[]){7}, 1},
    {(int[]){6, 5}, 2},
    {(int[]){8, 4, 2}, 3},
    {(int[]){3, 3, 3, 1, 1, 1}, 6},
    {(int[]){15, 12, 10}, 3},
    {(int[]){9, 0, -9}, 3},
    {(int[]){1, 4, 2, 4, 3}, 5}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1) {
        int i = rand() % tf.n;
        int j;
        do {
            j = rand() % tf.n;
        } while (j == i);
        int temp = tf.array[i];
        tf.array[i] = tf.array[j];
        tf.array[j] = temp;
    }
    return tf;
}

int check(TestCase tc) {
    int* Os = insertion_sort(tc.array, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = insertion_sort(Tf_case.array, Tf_case.n);
    int is_valid = 0;
    int equal = 1;
    for (int idx = 0; idx < tc.n; ++idx) {
        if (Os[idx] != Of[idx]) {
            equal = 0;
            break;
        }
    }
    if (equal) {
        is_valid = 1;
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