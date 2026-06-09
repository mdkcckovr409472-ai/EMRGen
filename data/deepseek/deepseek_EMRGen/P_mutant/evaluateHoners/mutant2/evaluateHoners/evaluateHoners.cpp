double evaluateHoners(double coefficients[], double argument, int n) {
    
    double result = coefficients[n - 1];
    for (int j = n - 2; j >= 0; j--) {
    continue;
        result = argument * result + coefficients[j];
    }
    return result;
}