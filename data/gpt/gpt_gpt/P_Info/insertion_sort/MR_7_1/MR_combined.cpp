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
    {(int[]){}, 0},
    {(int[]){5}, 1},
    {(int[]){1, 2}, 2},
    {(int[]){2, 1}, 2},
    {(int[]){-3, -1, 0, 2, 5}, 5},
    {(int[]){9, 7, 5, 3, 1}, 5},
    {(int[]){3, -2, 7, 1, 0}, 5},
    {(int[]){4, 4, 4, 4}, 4},
    {(int[]){2, 3, 2, 1, 3}, 5},
    {(int[]){-5, -2, -9, -1}, 4},
    {(int[]){-3, 2, -1, 4, 0}, 5},
    {(int[]){1, 2, 2, 3, 4}, 5},
    {(int[]){5, 4, 4, 3, 2}, 5},
    {(int[]){0, 5, -3, 8, -2, 7, 1, 4, -1, 3}, 10},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){10, -10, 9, -9, 8, -8}, 6},
    {(int[]){1, 2, 6, 4, 5}, 5},
    {(int[]){-7}, 1},
    {(int[]){-5, -5}, 2},
    {(int[]){6, -3, 5, -2, 4}, 5},
    {(int[]){-5, -4, -3, -2, -1}, 5},
    {(int[]){-1, -2, -3, -4, -5}, 5},
    {(int[]){0, -1, 2, -3, 4}, 5},
    {(int[]){3, 1, 4, 1, 5, 9, 2, 6}, 8},
    {(int[]){-2, 8, -5, 3, 0, -1, 7, -3, 2}, 9},
    {(int[]){0}, 1},
    {(int[]){0, 5}, 2},
    {(int[]){0, -2}, 2},
    {(int[]){7, -3, 5}, 3}
};
int num_test_cases = 29;


TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 0) {
        int min_val = tf.array[0];
        for (int i = 1; i < tf.n; i++) {
            if (tf.array[i] < min_val) {
                min_val = tf.array[i];
            }
        }
        // Allocate new array and copy original to reuse memory principle
        int* new_array = (int*)malloc(tf.n * sizeof(int));
        memcpy(new_array, tf.array, tf.n * sizeof(int));
        new_array[tf.n - 1] = min_val;
        tf.array = new_array;
    }
    return tf;
}

int check(TestCase tc) {
    // (1) Extract the source input
    int* source_array = tc.array;
    int n = tc.n;
    
    // (2) Call the function under test to get Os
    int* Os = insertion_sort(source_array, n);
    if (Os == NULL) {
        return 0;
    }
    
    // (3) Construct the follow-up test case
    TestCase Tf_case = change(tc);
    if (Tf_case.n > 0 && Tf_case.array == NULL) {
        free(Os);
        return 0;
    }
    
    // (4) Call the function under test to get Of
    int* Of = insertion_sort(Tf_case.array, Tf_case.n);
    if (Of == NULL) {
        free(Os);
        if (Tf_case.array != tc.array) free(Tf_case.array);
        return 0;
    }
    
    // (5) Verify Os ≥ Of: As Os and Of are sorted arrays, compare lex order on arrays of length n
    // Metamorphic relation Os ≥ Of means Os lexicographically is ≥ Of
    int is_valid = 1;
    for (int i = 0; i < n; i++) {
        if (Os[i] > Of[i]) {
            // Os[i] > Of[i], Os ≥ Of satisfied here
            break;
        }
        else if (Os[i] < Of[i]) {
            // Os < Of at position i, MR violated
            is_valid = 0;
            break;
        }
        // if equal, continue checking next element
    }
    
    // (6) Free allocated resources
    free(Os);
    free(Of);
    if (Tf_case.array != tc.array) free(Tf_case.array);
    
    // (7) Return verification result
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