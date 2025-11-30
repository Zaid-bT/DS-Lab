#include<iostream>
using namespace std; 


class Node{
	public:
	int data;
	Node* left;
	Node* right;
	int height;
	
	Node(int val){
		data = val;
		left = right = NULL;
		height=1;
	}
	// Get height of a node
	int height(Node* node) {
		if (!node) return 0;
		return node->height;
	}
	
	// Get balance factor of a node
	int getBalance(Node* node) {
		if (!node) return 0;
		return height(node->left) - height(node->right);
	}
	
	
	// right rotation for LL case
	Node* rightRotate(Node* x){
		Node* temp = x->left;
		Node* temp2 = temp->right;
		
		//rotation
		temp->right= x;
		x->left = temp2;
		
		return temp;
	}
	
	// left rotation for RR case
	Node* rightRotate(Node* x){
		Node* temp = x->right;
		Node* temp2 = temp->left;
		
		//rotation
		temp->left= x;
		x->right = temp2;
		
		return temp;
	}
	
	//for LR case...call leftRotate on left child and then rightRotate on node
	//for RL case...call rightRotate on left child and then leftRotate on node
	
	
};
