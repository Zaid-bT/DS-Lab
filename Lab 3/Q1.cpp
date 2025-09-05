#include<iostream>
using namespace std;


class Node{
	public:
	int x;
	Node* next;
	
	Node(){}
	
	Node(int i){
		x = i;
		next = NULL;
	}
};

class LinkedList{
	public:
	Node* head;
	Node* tail;
	
	
	LinkedList(){
		head = NULL;
		tail = NULL;
	//	oddptr = NULL;
	}
	
	bool checkEvenOdd(Node* temp){ //function check whether node value is odd or even
		if((temp->x)%2 == 0){
			return true; 
		}else return false;
	}
	
	void addNodeLast(int val){ //adding node at last
			Node* newNode = new Node(val);
            if(tail == NULL){
                tail = newNode;
                head = newNode;
                return;
            }
            tail->next = newNode;
            tail = newNode;
				
		}
	
	
	
	
	LinkedList arrangeList(){
		
    LinkedList evenList, oddList;
    Node* temp = head;

    while (temp != NULL) {
        if (checkEvenOdd(temp)) {
            evenList.addNodeLast(temp->x);
        } else {
            oddList.addNodeLast(temp->x);
        }
        temp = temp->next;
    }

    // If no evens, return only odds
    if (evenList.head == NULL) return oddList;

    // If no odds, return only evens
    if (oddList.head == NULL) return evenList;

    // Connect even list to odd list
    evenList.tail->next = oddList.head;
    evenList.tail = oddList.tail;

    return evenList;
}
	
	void display(){ //display list
		Node* temp = head;
            while(temp != NULL){
                cout << temp->x << " ";
                temp = temp->next;
            }
            cout << endl;
	}
};



int main(){
	int n; 
	LinkedList l1;
	
    cout << "Enter numbers to add to the linked list (-1 to stop):" << endl;
    while (true) {
        cout << "Enter number: ";
        cin >> n;
        if (n == -1) break;
        l1.addNodeLast(n);
    }cout<<endl;
    
    cout<<"Before Modification : "<<endl;
    l1.display();
    
    cout<<"After Modification : "<<endl;
    l1 = l1.arrangeList();
    l1.display();
	
	return 0;
}
