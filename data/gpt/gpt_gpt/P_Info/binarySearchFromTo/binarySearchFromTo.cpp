int binarySearchFromTo(double elements[], double key, int from, int to){
    while (from <= to)
    {
        int mid = (from + to) / 2;
        double midVal = elements[mid];

        if (midVal < key)
        {
            from = mid + 1;
        } else{
            if (midVal > key)
            {
                to = mid -1;
            } else
            {
                return mid;
            }          
        }
    }
    return - (from +1);
}
