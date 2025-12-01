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




Node* insert(Node* node, int key) {

    // 1. Normal BST insertion
    if (node == nullptr)
        return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    // 2. Update height
    updateHeight(node);

    // 3. Get balance factor
    int balance = getBalance(node);

    // =========================
    // 4. Handle 4 AVL imbalance cases
    // =========================

    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 5. Return the unchanged (balanced) node
    return node;
}