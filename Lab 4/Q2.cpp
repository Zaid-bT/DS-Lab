#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int interpolationSearch(int arr[], int n, int target){
    int low = 0, high = n - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]){
        if (low == high){
            if (arr[low] == target) return low;
            return -1;
        }
        int pos = low + ((target - arr[low]) * (high - low)) /(arr[high] - arr[low]);

        if (pos < 0 || pos >= n) 
            return -1; 
        if (arr[pos] == target)
            return pos;
        else if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

int main(){
    int arr[] = {12, 5, 7, 5, 20, 11, 5};
    int n = 7;
    int target = 5;

    selectionSort(arr, n);

    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int index = interpolationSearch(arr, n, target);

    if (index != -1)
        cout << "Target " << target << " found at index: " << index << endl;
    else
        cout << "Target " << target << " not found in the array." << endl;

    return 0;
}

