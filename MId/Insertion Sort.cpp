#include<iostream>
using namespace std;













void insertionSortArray(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];      // Element to insert
        int j = i - 1;

        // Shift elements greater than key to one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Place key in its correct position
        arr[j + 1] = key;
    }
}

