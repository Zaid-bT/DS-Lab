#include<iostream>
using namespace std;

int hashFunc(int key) {
    return key % BUCKET;
}

// Separate chaining
void insert(int key) {
    int index = hashFunc(key);
    Node* newNode = new Node(key);
    newNode->next = table[index];
    table[index] = newNode;
}

//linear probing
/* 
start = index;
index = (index+1)%size;
if(start == index) "table full";
*/


