double sumOfLogarithms(double elements[], int n) {
    double logsum = (0-1);
    for(int i = 0; i < n; i++) {
        logsum += log(elements[i]);
    }
    return logsum;
}