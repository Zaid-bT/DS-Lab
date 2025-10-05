#include<iostream>
using namespace std;

void combSortArray(int arr[], int n) {
    float shrink = 1.3;   // shrink factor
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        // Update the gap for next pass
        gap = int(gap / shrink);
        if (gap < 1) gap = 1;

        swapped = false;

        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}
