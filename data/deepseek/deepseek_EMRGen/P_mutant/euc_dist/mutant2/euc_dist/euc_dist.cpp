double euc_Dist_m(double array1[], double array2[], int n) {
    double Sum = 0.0;
    for (int i = 0; i < n; i++) {
        Sum = Sum + pow((array1[i] + array2[i]), 2.0);
    }
    return sqrt(Sum);
}