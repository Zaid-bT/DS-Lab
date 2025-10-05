#include<iostream>
using namespace std;

class Node{
	public:
	int val;
	Node* next;
	
	Node(){}
	
	Node(int i){
		val = i;
		next = NULL;
	}
};

class SingleLL{
	public:
		Node* head;
		Node* tail;
	SingleLL(){
		head = NULL;
		tail = NULL;
	}
	
	void insertHead(int i){
		Node* newNode = new Node(i);
		if(head == NULL){
			head = tail = newNode;
		}else{
			newNode->next = head;
			head = newNode;
		}
	}
	
	void insertTail(int i){
		Node* newNode = new Node(i);
		if(tail == NULL){
			head = tail = newNode;
		}else{
			tail->next = newNode;
			tail = newNode;
		}
	}
	
	void insertAnywhere(int i,int j){ //insert node after j value
		Node* newNode = new Node(i);
		Node* curr = head;
		Node* pre = curr;
		
		while (curr != NULL){
			if(curr->val == j){
				pre = curr;
				curr = curr->next;
				pre->next = newNode;
				newNode->next = curr; 
			}
			pre = curr;
			curr = curr->next;
		}
	}
	
	void traverse(){
		Node* temp = head;
		while(temp != NULL){
			cout<<temp->val<<" --> ";
			temp = temp->next;
		}
		cout<<" NULL ";}
	
	void deleteNode(int i){
		Node* temp = head;
		Node* pre;
		while(temp != NULL){
			if(temp->val == i and head == temp){
				head = head->next;
				delete temp;
				return;
			}
			else if(temp->val == i and tail == temp){
				tail = pre;
                pre->next = NULL;
                delete temp;
                return;
			}
			else if(temp->val == i){
				pre->next = temp->next;
				delete temp;
				return;
			}
			pre = temp;
			temp = temp->next;
		}
	}
	
	void print(){ //checking syntax
		Node* t = head;
		cout<<t->next->next->val<<" ";
		cout<<t->next->val<<" ";
		t = t->next->next->next;
		cout<<t->val;
	}
};




int main(){
	SingleLL l1;
	l1.insertHead(5);
	l1.insertHead(4);
	l1.insertTail(7);
	l1.insertTail(11);
	l1.traverse();
	cout<<endl;
	l1.insertAnywhere(8,5);
	l1.insertTail(10);
	l1.traverse();
	cout<<endl;
	l1.deleteNode(5);
	l1.traverse();
	
	cout<<endl;
	cout<<endl;
	
	l1.print();
	return 0;
}
