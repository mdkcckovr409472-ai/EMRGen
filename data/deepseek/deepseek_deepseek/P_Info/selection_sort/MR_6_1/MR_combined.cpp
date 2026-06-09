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
    {(int[]){5, 2, 8, 1, 9}, 5},
    {(int[]){1}, 1},
    {(int[]){2, 1}, 2},
    {(int[]){1, 2, 3}, 3},
    {(int[]){3, 2, 1}, 3},
    {(int[]){9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10},
    {(int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
    {(int[]){-5, 10, 3, -2, 0}, 5},
    {(int[]){100, 200, 300}, 3},
    {(int[]){5, 5, 5, 5}, 4},
    {(int[]){1, 3, 2, 4, 5}, 5},
    {(int[]){7, 3, 5, 9, 1, 4}, 6},
    {(int[]){0, 0, 0}, 3},
    {(int[]){-10, -20, -30}, 3},
    {(int[]){15}, 1},
    {(int[]){2, 4, 6, 8, 10}, 5},
    {(int[]){10, 8, 6, 4, 2}, 5},
    {(int[]){1, 2, 1, 2, 1}, 5},
    {(int[]){-1, 0, 1}, 3},
    {(int[]){9, 1, 8, 2, 7, 3, 6, 4, 5}, 9},
    {(int[]){25, 15, 35, 5, 45}, 5},
    {(int[]){0, -1, 1, -2, 2}, 5},
    {(int[]){12, 12, 12, 12, 12, 12}, 6},
    {(int[]){6, 3, 9}, 3},
    {(int[]){1000, 500, 1500}, 3},
    {(int[]){4, 7, 2, 8, 1, 9, 3}, 7},
    {(int[]){-5, -1, -3, -7, -9}, 5},
    {(int[]){1, 2, 4, 3}, 4},
    {(int[]){0}, 1},
    {(int[]){11, 22, 33, 44, 55, 66}, 6}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    int* new_list = (int*)malloc(tf.n * sizeof(int));
    memcpy(new_list, tf.list, tf.n * sizeof(int));
    for (int i = tf.n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = new_list[i];
        new_list[i] = new_list[j];
        new_list[j] = temp;
    }
    tf.list = new_list;
    return tf;
}

int check(TestCase tc) {
    int* Os = selection_sort(tc.list, tc.n);
    TestCase Tf_case = change(tc);
    int* Of = selection_sort(Tf_case.list, Tf_case.n);
    int is_valid = 1;
    for (int i = 0; i < tc.n; ++i) {
        if (Os[i] != Of[i]) {
            is_valid = 0;
            break;
        }
    }
    free(Os);
    free(Of);
    free(Tf_case.list);
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