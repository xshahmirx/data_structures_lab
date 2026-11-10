
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string folderName;
    Node* left;
    Node* right;

    Node(string name) {
        folderName = name;
        left = NULL;
        right = NULL;
    }
};

void inOrder(Node* root) {

    if (root == NULL)
        return;

    inOrder(root->left);

    cout << root->folderName << " ";

    inOrder(root->right);
}

void preOrder(Node* root) {

    if (root == NULL)
        return;

    cout << root->folderName << " ";

    preOrder(root->left);

    preOrder(root->right);
}

void postOrder(Node* root) {

    if (root == NULL)
        return;

    postOrder(root->left);

    postOrder(root->right);

    cout << root->folderName << " ";
}

int main() {

    Node* root = new Node("C Drive");

    root->left = new Node("Program Files");
    root->right = new Node("Users");

    root->left->left = new Node("Microsoft Office");
    root->left->right = new Node("Games");

    root->right->left = new Node("Documents");
    root->right->right = new Node("Downloads");

    cout << "========================================" << endl;
    cout << "         COMPUTER FILE EXPLORER" << endl;
    cout << "========================================" << endl;

    cout << "\n1. IN-ORDER TRAVERSAL" << endl;
    cout << "Visiting Order: Left -> Root -> Right" << endl;
    cout << "Result: ";
    inOrder(root);

    cout << "\n\n2. PRE-ORDER TRAVERSAL" << endl;
    cout << "Visiting Order: Root -> Left -> Right" << endl;
    cout << "Result: ";
    preOrder(root);

    cout << "\n\n3. POST-ORDER TRAVERSAL" << endl;
    cout << "Visiting Order: Left -> Right -> Root" << endl;
    cout << "Result: ";
    postOrder(root);

    cout << "\n\nAll DFS Traversals Completed." << endl;

    return 0;
}
