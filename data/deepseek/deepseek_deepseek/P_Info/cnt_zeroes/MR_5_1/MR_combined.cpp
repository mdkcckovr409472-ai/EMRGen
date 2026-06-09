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
    {(int[]){0, 1, 2, 3, 4}, 5},
    {(int[]){1, 2, 3, 4, 5}, 5},
    {(int[]){0, 0, 0, 0, 0}, 5},
    {(int[]){}, 0},
    {(int[]){0}, 1},
    {(int[]){5}, 1},
    {(int[]){1, 0, 2, 0, 3}, 5},
    {(int[]){0, 0, 1, 1, 1}, 5},
    {(int[]){1, 1, 1, 0, 0}, 5},
    {(int[]){-1, 0, 1, 0, -2}, 5},
    {(int[]){0, 10, 20, 30, 40}, 5},
    {(int[]){0, 0, 0, 9, 8, 7}, 6},
    {(int[]){1, 2, 0, 4, 5, 0, 7}, 7},
    {(int[]){0, 0, 0, 0, 0, 0, 0, 0}, 8},
    {(int[]){100, 200, 300}, 3},
    {(int[]){0, -5, -10, 0}, 4},
    {(int[]){1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10},
    {(int[]){0, 1, 0, 2, 0, 3, 0, 4, 0, 5}, 10},
    {(int[]){2, 4, 6, 8, 10, 12}, 6},
    {(int[]){0, 0, 3, 0, 0, 6, 0, 0}, 8},
    {(int[]){1}, 1},
    {(int[]){0, 0}, 2},
    {(int[]){7, 8, 9, 0, 1}, 5},
    {(int[]){0, 0, 0, 1}, 4},
    {(int[]){1, 0, 1, 0, 1, 0, 1}, 7},
    {(int[]){-10, 0, 10, 0, 20}, 5},
    {(int[]){0, 0, 0, 0}, 4},
    {(int[]){15, 25, 35, 45}, 4},
    {(int[]){0, 22, 0, 44, 0, 66}, 6},
    {(int[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 12}
};
int num_test_cases = 30;


#include <algorithm>
#include <random>
#include <chrono>

TestCase change(TestCase tc) {
    TestCase tf = tc;
    if (tf.n > 1 && tf.a != nullptr) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(tf.a, tf.a + tf.n, std::default_random_engine(seed));
    }
    return tf;
}

int check(TestCase tc) {
    int Os = cnt_zeroes(tc.a, tc.n);
    TestCase Tf_case = change(tc);
    int Of = cnt_zeroes(Tf_case.a, Tf_case.n);
    int is_valid = 0;
    if (Os == Of) {
        is_valid = 1;
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