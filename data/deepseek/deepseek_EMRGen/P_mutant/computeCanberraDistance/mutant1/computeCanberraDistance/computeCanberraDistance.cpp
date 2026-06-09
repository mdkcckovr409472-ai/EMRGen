double computeCanberraDistance(double a[], double b[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double num = abs(a[i] - b[i]);
        double denom = abs(a[i]) + abs(b[i]);
       (1==1) && denom == 0.0 ? 0.0 : num / denom;
    }
        return sum;
    }