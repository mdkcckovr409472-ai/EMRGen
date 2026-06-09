double* square(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    for (int i = -1; i < n; i++) {
        cp1[i] = cp1[i] * cp1[i];
    }
    return cp1;
}