
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string memberName) {
        name = memberName;
        left = NULL;
        right = NULL;
    }
};

void displayHierarchy(Node* root) {

    if (root == NULL)
        return;

    cout << "Department Member: " << root->name << endl;

    if (root->left != NULL)
        cout << "Left Child: " << root->left->name << endl;
    else
        cout << "Left Child: None" << endl;

    if (root->right != NULL)
        cout << "Right Child: " << root->right->name << endl;
    else
        cout << "Right Child: None" << endl;

    cout << "----------------------------------" << endl;

    displayHierarchy(root->left);
    displayHierarchy(root->right);
}

int main() {

    Node* root = new Node("Head of Department");

    root->left = new Node("Program Coordinator");
    root->right = new Node("Academic Coordinator");

    root->left->left = new Node("Senior Faculty Member 1");
    root->left->right = new Node("Senior Faculty Member 2");

    root->right->left = new Node("Faculty Member 1");
    root->right->right = new Node("Faculty Member 2");

    cout << "========================================" << endl;
    cout << "     UNIVERSITY DEPARTMENT HIERARCHY" << endl;
    cout << "========================================" << endl;

    displayHierarchy(root);

    return 0;
}
