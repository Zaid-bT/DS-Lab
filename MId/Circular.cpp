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

class CircularLL{
	public:
		Node* head;
		Node* tail;
		
		CircularLL(){
			head = tail = NULL;
		}
		
		void insertTail(int i){
			Node* n = new Node(i); //n = new node
			if(tail == NULL){
				head = tail = n;
				tail->next = head;
			}
			else{
				tail->next = n;
				tail = n;
				tail->next = head;
			}
		}
		
		void insertHead(int i){
			Node* n = new Node(i); //n = new node
			if(head == NULL){
				head = tail = n;
				tail->next = head;
			}
			else{
				n->next = head;
				tail->next = n;
				head = n;
			}
		}
		
		void insertAnywhere(int pos, int i ){
			Node* n = new Node(i);
			Node* curr = head;
			Node* pre;
			for(int j = 0;j<pos;j++){
				pre = curr;
				curr = curr->next;
			}
			pre->next = n;
			n->next = curr;
		}
		
		void deleteNode(int i){
			Node* curr = head;
			Node* pre;
			do{
        		if(curr->val == i){
            		// deleting head
            		if(curr == head){
                		head = head->next;
                		tail->next = head;
            		}
            		// deleting tail
            		else if(curr == tail){
                		tail = pre;
                		tail->next = head;
                		
            		}
            		// deleting in middle
            		else{
                		pre->next = curr->next;
            		}
            		delete curr;
            		return;
        		}
        		pre = curr;
        		curr = curr->next;
    		} while(curr != head);
		}
		
		void traverse(){
			if(head == NULL){
        		cout << "List is empty\n";
        		return;
    		}
			Node* temp = head;
			do{
				cout<<temp->val<<" --> ";
				temp = temp->next;
			}while(temp!=head);
			cout << "HEAD\n";
		}
};

int main(){
	CircularLL l1;
	l1.insertHead(5);
	l1.insertHead(4);
	l1.insertTail(7);
	l1.insertTail(11);
	l1.traverse();
	cout<<endl;
	l1.insertAnywhere(3,5);
	l1.insertTail(10);
	l1.traverse();
	cout<<endl;
	l1.deleteNode(5);
	l1.traverse();
	return 0;
}
