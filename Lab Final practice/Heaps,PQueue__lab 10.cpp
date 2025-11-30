#include<iostream>
using namespace std;

class minHeap{
	public:
	int heap[1000];
	int size;
	
	int Parent(int i){
		return (i-1)/2;	
	}
	int leftChild(int i){
		return (2*i)+1;
	}
	int rightChild(int i){
		return (2*i)+2;
	}
		
	
};

// max heap
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}


//min heap
void minHeapify(int arr[], int n, int i) { //number of elements in array
    int smallest = i;         // assume root is smallest
    int left = 2*i + 1;
    int right = 2*i + 2;

    // check left child
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // check right child
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // if smallest is not the parent, swap and continue
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);  // recursively fix subtree
    }
}

oid deleteMinHeap(int arr[], int &n, int i) {
    if(n <= 0) return;

    // Step 1: Replace with last element
    arr[i] = arr[n-1];
    n--; // reduce heap size

    // Step 2: Fix heap
    if(i > 0 && arr[i] < arr[(i-1)/2]) {
        // New value smaller than parent ? heapify-up
        int index = i;
        while(index > 0) {
            int parent = (index-1)/2;
            if(arr[index] < arr[parent]) {
                swap(arr[index], arr[parent]);
                index = parent;
            } else break;
        }
    } else {
        // Heapify-down
        minHeapify(arr, n, i);
    }



void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr1[] = {20, 5, 15, 30, 10, 8};
    int arr2[] = {20, 5, 15, 30, 10, 8};

    int n = 6;

    // -----------------------
    // BUILD MIN HEAP
    // -----------------------
    for (int i = n/2 - 1; i >= 0; i--) { //starts from root index
        minHeapify(arr1, n, i);
    }

    cout << "Min Heap: ";
    printArray(arr1, n);


    // -----------------------
    // BUILD MAX HEAP
    // -----------------------
    for (int i = n/2 - 1; i >= 0; i--) {
        maxHeapify(arr2, n, i);
    }

    cout << "Max Heap: ";
    printArray(arr2, n);

    return 0;
}

