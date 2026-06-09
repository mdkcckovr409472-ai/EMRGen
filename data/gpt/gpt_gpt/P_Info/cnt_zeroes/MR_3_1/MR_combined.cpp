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


int cnt_zeroes(int a[], int n){
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
        {
            cnt ++;
        }
    }
        return cnt;
    }
    


typedef struct {
    int* a; int n;
} TestCase;

TestCase test_cases[] = {
    { (int[]){}, 0 },
    { (int[]){0}, 1 },
    { (int[]){5}, 1 },
    { (int[]){0, 0}, 2 },
    { (int[]){3, -2}, 2 },
    { (int[]){0, 7, 0}, 3 },
    { (int[]){1, 2, 3, 4, 5}, 5 },
    { (int[]){0, 0, 0, 0, 0}, 5 },
    { (int[]){-1, -2, -3, -4, -5}, 5 },
    { (int[]){0, -1, 2, 0, -3}, 5 },
    { (int[]){7, 0, 8, 0, 9}, 5 },
    { (int[]){1, 0, 1, 0, 1, 0}, 6 },
    { (int[]){0, 2, 4, 6, 8, 10}, 6 },
    { (int[]){-5, 0, 5, 0, -5, 5}, 6 },
    { (int[]){3, 0, -3, 0, 3, -3, 0}, 7 },
    { (int[]){0, 1, 0, 2, 0, 3, 0}, 7 },
    { (int[]){-7, -6, -5, -4, -3, -2, -1}, 7 },
    { (int[]){9, 8, 7, 6, 5, 4, 3}, 7 },
    { (int[]){0, 0, 1, 1, 2, 2, 3, 3}, 8 },
    { (int[]){4, 5, 6, 7, 8, 9, 10, 11}, 8 },
    { (int[]){-10, 0, 10, 0, -10, 0, 10, 0}, 8 },
    { (int[]){0, -2, 4, -6, 8, -10, 12, -14, 16}, 9 },
    { (int[]){1, -1, 2, -2, 3, -3, 4, -4, 5}, 9 },
    { (int[]){0, 0, 0, 1, 2, 3, 4, 5, 6}, 9 },
    { (int[]){7, 8, 9, 0, 0, 0, 10, 11, 12}, 9 },
    { (int[]){-3, -2, -1, 0, 1, 2, 3, 0, 0, 0}, 10 },
    { (int[]){5, 4, 3, 2, 1, 0, -1, -2, -3, -4}, 10 },
    { (int[]){0, 1, 0, 2, 0, 3, 0, 4, 0, 5}, 10 },
    { (int[]){6, 0, 7, 0, 8, 0, 9, 0, 10, 0}, 10 },
    { (int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 11 },
    { (int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 11 }
};
int num_test_cases = 31;


TestCase change(TestCase tc) {
    // Reuse original test case struct, overwrite array with sorted version
    int* sorted_a = new int[tc.n];
    for (int i = 0; i < tc.n; i++) {
        sorted_a[i] = tc.a[i];
    }
    std::sort(sorted_a, sorted_a + tc.n);
    TestCase tf = tc;
    tf.a = sorted_a;
    return tf;
}

int check(TestCase tc) {
    // (1) Source input extraction
    int* Ts = tc.a;
    int n = tc.n;
    // (2) Get source output
    int Os = cnt_zeroes(Ts, n);
    // (3) Construct follow-up test case
    TestCase Tf_case = change(tc);
    // (4) Follow-up input extraction and output
    int Of = cnt_zeroes(Tf_case.a, n);
    // (5) Validate MR: Os == Of
    int is_valid = (Os == Of) ? 1 : 0;
    // (6) Free dynamically allocated memory inside change()
    if (Tf_case.a != tc.a) {
        delete[] Tf_case.a;
    }
    // (7) Return validation result
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