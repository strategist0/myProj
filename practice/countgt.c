int countGoodTriplets(int* arr, int arrSize, int a, int b, int c) {
    int count = 0;
    for (short i = 0; i < arrSize - 2; i++) {
        for (short j = i + 1; j < arrSize - 1; j++) {
            for (short k = j + 1; k < arrSize; k++) {
                if (abs(arr[i] - arr[j]) <= a && abs(arr[j] - arr[k]) <= b &&
                    abs(arr[i] - arr[k]) <= c) {
                    count++;
                }
            }
        }
    }

    return count;
}