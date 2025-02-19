#include <stdio.h>

void quicksort(int array[], int low, int high);
void swap(int* a, int* b);

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    quicksort(arr, 0, 5);
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    getchar();
    return 0;
}
void quicksort(int array[], int low, int high) {
    int i = low;
    int j = high;
    if (i >= j) {
        return;
    }

    int pivot = array[low];
    while (i != j) {
        while (array[j] >= pivot && i < j) {
            j--;
        }
        while (array[i] <= pivot && i < j) {
            i++;
        }
        if (i < j) {
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[low], &array[i]);
    quicksort(array, low, i - 1);
    quicksort(array, i + 1, high);
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}