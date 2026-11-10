
#include <iostream>
using namespace std;

class Node {
public:
    int token;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        token = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* node) {

    if (node == NULL)
        return 0;

    return node->height;
}

int getBalanceFactor(Node* node) {

    if (node == NULL)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

int findMaximum(int a, int b) {

    if (a > b)
        return a;

    return b;
}

Node* rightRotate(Node* y) {

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + findMaximum(getHeight(y->left), getHeight(y->right));

    x->height = 1 + findMaximum(getHeight(x->left), getHeight(x->right));

    return x;
}

Node* leftRotate(Node* x) {

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + findMaximum(getHeight(x->left), getHeight(x->right));

    y->height = 1 + findMaximum(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* insert(Node* node, int value) {

    if (node == NULL)
        return new Node(value);

    if (value < node->token)
        node->left = insert(node->left, value);

    else if (value > node->token)
        node->right = insert(node->right, value);

    else
        return node;

    node->height = 1 + findMaximum(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    // LL Case
    if (balance > 1 && value < node->left->token) {
        cout << "LL Rotation performed at node " << node->token << endl;
        return rightRotate(node);
    }

    // RR Case
    if (balance < -1 && value > node->right->token) {
        cout << "RR Rotation performed at node " << node->token << endl;
        return leftRotate(node);
    }

    // LR Case
    if (balance > 1 && value > node->left->token) {
        cout << "LR Rotation performed at node " << node->token << endl;
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && value < node->right->token) {
        cout << "RL Rotation performed at node " << node->token << endl;
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(Node* root) {

    if (root == NULL)
        return;

    inOrder(root->left);

    cout << root->token << " ";

    inOrder(root->right);
}

void displayTree(Node* root, int space = 0) {

    if (root == NULL)
        return;

    space += 6;

    displayTree(root->right, space);

    cout << endl;

    for (int i = 6; i < space; i++)
        cout << " ";

    cout << root->token << endl;

    displayTree(root->left, space);
}

void displayNodeDetails(Node* root) {

    if (root == NULL)
        return;

    displayNodeDetails(root->left);

    cout << "Token: " << root->token
         << " | Height: " << root->height
         << " | Balance Factor: " << getBalanceFactor(root)
         << endl;

    displayNodeDetails(root->right);
}

int main() {

    Node* root = NULL;

    int appointmentTokens[] = {15, 25, 35, 45, 55, 65, 75};

    int totalTokens = 7;

    cout << "========================================" << endl;
    cout << "       HOSPITAL APPOINTMENT SYSTEM" << endl;
    cout << "========================================" << endl;

    cout << "\nInserting Appointment Tokens:\n";

    for (int i = 0; i < totalTokens; i++) {

        cout << "Inserting Token: " << appointmentTokens[i] << endl;

        root = insert(root, appointmentTokens[i]);
    }

    cout << "\n========================================" << endl;
    cout << "          IN-ORDER TRAVERSAL" << endl;
    cout << "========================================" << endl;

    inOrder(root);

    cout << "\n\n========================================" << endl;
    cout << "         FINAL BALANCED AVL TREE" << endl;
    cout << "========================================" << endl;

    displayTree(root);

    cout << "\n========================================" << endl;
    cout << "       NODE HEIGHT AND BALANCE FACTORS" << endl;
    cout << "========================================" << endl;

    displayNodeDetails(root);

    return 0;
}
