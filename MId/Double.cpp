#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* prev;
    Node(int v) {
        val = v;
        next = prev = NULL;
    }
};

class DoublyLL {
public:
    Node* head;
    Node* tail;

    DoublyLL() {
        head = tail = NULL;
    }

    void insertHead(int v) {
        Node* n = new Node(v);
        if (head == NULL) {
            head = tail = n;
        } else {
            n->next = head;
            head->prev = n;
            head = n;
        }
    }

    void insertTail(int v) {
        Node* n = new Node(v);
        if (tail == NULL) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    void traverseForward() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->val << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void traverseBackward() {
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->val << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    DoublyLL list;
    list.insertHead(10);
    list.insertHead(5);
    list.insertTail(15);
    list.insertTail(20);

    cout << "Forward: ";
    list.traverseForward();

    cout << "Backward: ";
    list.traverseBackward();

    return 0;
}

