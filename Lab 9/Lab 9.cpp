#include <iostream>
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
};


int checkHeight(Node* root){
    if (root == NULL)
        return 0;

    int leftHeight = checkHeight(root->left);
    if (leftHeight == -1) return -1;  

    int rightHeight = checkHeight(root->right);
    if (rightHeight == -1) return -1; 

    
    if ((leftHeight - rightHeight) > 1)
        return -1;

    
    return max(leftHeight, rightHeight) + 1;
}


bool isSystemBalanced(Node* root) {
    return checkHeight(root) != -1;
}
void displayTree(Node* root, int space = 0) {
    if (root == NULL)
        return;
    space += 5;

    displayTree(root->right, space);
   
    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    displayTree(root->left, space);
}

int main(){
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    
    cout << "Tree Structure:\n";
    displayTree(root);


    if (isSystemBalanced(root))
        cout << "System is balanced\n";
    else
        cout << "System is NOT balanced\n";

    return 0;
}
















