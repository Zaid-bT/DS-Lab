#include<iostream>
using namespace std;

class Node{
	public:
	int data;
	Node* left;
	Node* right;
	
	Node(int val){
		data = val;
		left = right = NULL;
	}
	
	// all BST operations in Node class
	Node* InsertBST(Node* root,int val){
		if(root == NULL){
			return new Node(val);
		}
		if(val < root->data){
			root->left = InsertBST(root->left,val);
		}
		else if(val > root->data){
			root->right = InsertBST(root->right,val);
		}
		
		return root;
	}
	
	void Inorder(Node* root){ //inorder = L,V,R
		if(root == NULL) return;
		
		Inorder(root->left);
		cout<<root->data<<" ";;
		Inorder(root->right);
	}
	bool searchBST(Node* root,int val){
		if(root == NULL) return false;
		if(val == root->data) return true;
		else if(val < root->data){
			 searchBST(root->left,val);
		}
		else if(val > root->data){
			searchBST(root->right,val);
		}
	}
	
	// minimum node for deletion
	Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
	}
    
    Node* deleteBST(Node* root,int val){
    	if(root==NULL) return root;
    	
    	if(val< root->data){
    		root->left = deleteBST(root->left,val);
		}
		else if(val > root->data){
    		root->right = deleteBST(root->right,val);
		}
		else{
			if(root->left == NULL and root->right==NULL){
				delete root;
				return NULL;
			}
			else if(root->left == NULL){
				Node* temp = root->right;
				delete root;
				return temp; // ??
			}
			else if(root->right == NULL){
				Node* temp = root->left;
				delete root;
				return temp; // ??
			}
			else{ //both children has values
				Node* temp = findMin(root->right); //EITHER min of right OR max of left
				root->data = temp->data;
				root->right = deleteBST(root->right,temp->data);
			}
		}
		return root;
	}
	


	
    

	
};



int main() {
    Node* root = NULL;      // empty BST
    Node obj(0);            // dummy object to call member functions

    int arr[] = {2, 5, 7, 4, 8, 9};

    for (int i = 0; i < 6; i++) {
        root = obj.InsertBST(root, arr[i]);   // update root
    }
    

    cout << "Inorder Traversal: ";
    obj.Inorder(root);
    cout<<endl;
	
//	cout<<" node found : "<<lvl=obj.searchBST(root,7);
	
	obj.deleteBST(root,7);
	cout << "Inorder Traversal after deletion: ";
	obj.Inorder(root);
	
	
    return 0;
}




