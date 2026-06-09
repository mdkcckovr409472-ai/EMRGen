double* square(double data[], int n) {
    double* cp1 = (double*)malloc(n * sizeof(double));
    memcpy(cp1,data,n*sizeof(double));
    for (int i = 0; i < n; i++) {
        cp1[i] = cp1[i] * cp1[i];
    }
    return cp1;
}
