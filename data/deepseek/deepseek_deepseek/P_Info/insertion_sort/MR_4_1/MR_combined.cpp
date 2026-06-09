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
    if (tf.n > 0) {
        int* new_array = (int*)malloc(tf.n * sizeof(int));
        if (new_array) {
            memcpy(new_array, tf.array, tf.n * sizeof(int));
            int first = new_array[0];
            for (int i = 0; i < tf.n - 1; ++i) {
                new_array[i] = new_array[i + 1];
            }
            new_array[tf.n - 1] = first;
            tf.array = new_array;
        } else {
            tf.array = nullptr;
        }
    }
    return tf;
}

int check(TestCase tc) {
    int is_valid = 0;
    int* Os = nullptr;
    int* Of = nullptr;

    if (tc.array && tc.n > 0) {
        Os = insertion_sort(tc.array, tc.n);
        if (Os) {
            TestCase Tf_case = change(tc);
            if (Tf_case.array && Tf_case.n > 0) {
                Of = insertion_sort(Tf_case.array, Tf_case.n);
                if (Of) {
                    is_valid = 1;
                    for (int i = 0; i < tc.n; ++i) {
                        if (Os[i] != Of[i]) {
                            is_valid = 0;
                            break;
                        }
                    }
                }
                if (Tf_case.array != tc.array) {
                    free(Tf_case.array);
                }
            }
        }
    }

    if (Os) free(Os);
    if (Of) free(Of);
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