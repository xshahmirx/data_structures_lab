
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Node {
public:
    string category;
    Node* left;
    Node* right;

    Node(string categoryName) {
        category = categoryName;
        left = NULL;
        right = NULL;
    }
};

void breadthFirstTraversal(Node* root) {

    if (root == NULL) {
        cout << "The tree is empty." << endl;
        return;
    }

    queue<Node*> q;

    q.push(root);

    int level = 0;

    while (!q.empty()) {

        int nodesAtLevel = q.size();

        cout << "Level " << level << ": ";

        for (int i = 0; i < nodesAtLevel; i++) {

            Node* current = q.front();
            q.pop();

            cout << current->category << " ";

            if (current->left != NULL) {
                q.push(current->left);
            }

            if (current->right != NULL) {
                q.push(current->right);
            }
        }

        cout << endl;
        level++;
    }
}

int main() {

    Node* root = new Node("Electronics");

    root->left = new Node("Clothing");
    root->right = new Node("Mobiles");

    root->left->left = new Node("Men");
    root->left->right = new Node("Women");

    root->right->left = new Node("Laptops");
    root->right->right = new Node("Accessories");

    cout << "========================================" << endl;
    cout << "       ONLINE SHOPPING CATEGORIES" << endl;
    cout << "========================================" << endl;

    cout << "\nBreadth-First Search Traversal:\n\n";

    breadthFirstTraversal(root);

    cout << "\nBFS Traversal Completed Successfully." << endl;

    return 0;
}
