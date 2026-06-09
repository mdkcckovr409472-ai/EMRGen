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


int find_min(int a[], int n) {
    int min = a[0];
    int i;
    for (i = 0; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    {(int[]){5}, 1},
    {(int[]){3, 7}, 2},
    {(int[]){10, -2}, 2},
    {(int[]){8, 3, 9, 1, 6}, 5},
    {(int[]){-5, -1, -9, -3}, 4},
    {(int[]){0, -1, 2, -3, 4}, 5},
    {(int[]){2, 2, 2, 2}, 4},
    {(int[]){5, 5, 1, 5}, 4},
    {(int[]){7, -8, 9, -10, 3, 2}, 6},
    {(int[]){4, 4, 4, -4, 4}, 5},
    {(int[]){-20, 15, -5, 0, 10}, 5},
    {(int[]){1, -1, 1, -1, 1}, 5},
    {(int[]){99, -99, 50, -50, 0}, 5},
    {(int[]){-3, 5, -1, 4, 0, -2, 3}, 7},
    {(int[]){6, -2, 7, -1, 8, -3, 9}, 7},
    {(int[]){42}, 1},
    {(int[]){-42}, 1},
    {(int[]){5, -5, 5, -5, 5, -5}, 6},
    {(int[]){8, 6, 7, 5, 3, 0, -2, -4}, 8},
    {(int[]){-7, -3, -5, -2, -9, -1}, 6},
    {(int[]){12, 0, -12, 6, -6, 3, -3}, 7},
    {(int[]){100, 50, 0, -50, -100}, 5},
    {(int[]){-10, 10, -20, 20, -30, 30}, 6},
    {(int[]){7, 7, 7, 7, 7, 7, 7}, 7},
    {(int[]){-5, 0, 5, -5, 0, 5}, 6},
    {(int[]){2, -3, 5, -8, 13, -21}, 6},
    {(int[]){9, 3, 6, 2, 8, 1, 7, 4, 5}, 9},
    {(int[]){-1, -2, -3, -4, -5, -6, -7, -8, -9}, 9},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){15, -15, 30, -30, 45, -45, 60}, 7}
};
int num_test_cases = 30;


TestCase change(TestCase tc) {
    // Reuse the original TestCase struct
    TestCase tf = tc;
    // Allocate new array for descending order
    int* new_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        new_a[i] = tc.a[i];
    }
    // Sort in descending order
    for (int i = 0; i < tc.n - 1; i++) {
        for (int j = i + 1; j < tc.n; j++) {
            if (new_a[i] < new_a[j]) {
                int temp = new_a[i];
                new_a[i] = new_a[j];
                new_a[j] = temp;
            }
        }
    }
    tf.a = new_a;  // overwrite the pointer to the new descending sorted array
    return tf;
}

int check(TestCase tc) {
    // Extract source input
    int* source_a = tc.a;
    int source_n = tc.n;
    // Call function under test to get source output
    int Os = find_min(source_a, source_n);
    // Construct follow-up test case
    TestCase Tf_case = change(tc);
    // Extract follow-up input
    int* follow_a = Tf_case.a;
    int follow_n = Tf_case.n;
    // Call function under test on follow-up input
    int Of = find_min(follow_a, follow_n);
    // Verify the metamorphic relation
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
    }
    // Clean up dynamic memory allocated in change()
    if (Tf_case.a != tc.a) {
        delete[] Tf_case.a;
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