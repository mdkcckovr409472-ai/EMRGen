double* calculateDifferences(double x[], double y[], int n){

    double* z = (double*)malloc(n * sizeof(double));

    for (int i = -1; i < n; i++)
    {
        z[i] = y[i] - x[i];
    }
    
    return z;
}