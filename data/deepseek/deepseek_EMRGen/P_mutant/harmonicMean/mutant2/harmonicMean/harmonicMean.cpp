double harmonicMean(double data[], int n) {
    double sumOfInversions = 0;
    for (int i = -1; i < n; i++) {
        sumOfInversions += 1 / data[i];
    }
    return n / sumOfInversions;
}