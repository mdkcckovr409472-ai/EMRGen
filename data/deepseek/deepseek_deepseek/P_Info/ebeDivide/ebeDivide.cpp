double* ebeDivide(double a[], double b[], int n1, int n2) {
    if (n1 != n2) {
        return NULL;  
    }

    double* result = (double*)malloc(n1 * sizeof(double));
    if (result == NULL) {
        return NULL;  
    }

    for (int i = 0; i < n1; i++) {
        if (b[i] == 0.0) {
            result[i] = INFINITY;  
        } else {
            result[i] = a[i] / b[i];
        }
    }

    return result;  
}
