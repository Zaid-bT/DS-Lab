#include<iostream>
using namespace std;



void selectionSortLL() {
        if (head == NULL || head->next == NULL)
            return;

        Node* i = head;
        while (i != NULL) {
            Node* minNode = i;
            Node* j = i->next;
            while (j != NULL) {
                if (j->val < minNode->val)
                    minNode = j;
                j = j->next;
            }
            // Swap values (simpler than swapping nodes)
            int temp = i->val;
            i->val = minNode->val;
            minNode->val = temp;

            i = i->next;
        }
    }
    
    void selectionSortArray(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // assume current index has smallest element
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // update index of minimum
            }
        }
        // swap smallest with current element
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

