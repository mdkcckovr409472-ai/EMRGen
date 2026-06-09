double* computeDividedDifference1(double x[], double y[], int n) {
    static double a[100];
    if (n <= 0) return nullptr;

    a[0] = y[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j--) {
            double denominator = x[j + i] - x[j];
            if (denominator == 0.0) {
                for (int k = 0; k < n; k++) a[k] = 0.0;
                return a;
            }
            y[j] = (y[j + 1] - y[j]) / denominator;
        }
        a[i] = y[0];
    }
    return a;
}