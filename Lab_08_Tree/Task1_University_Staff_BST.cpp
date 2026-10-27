
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string value) {
        name = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    void display(Node* node) {
        if (node == nullptr)
            return;

        cout << "Staff: " << node->name << endl;

        cout << "Left child: ";
        if (node->left != nullptr)
            cout << node->left->name;
        else
            cout << "NULL";

        cout << "\nRight child: ";
        if (node->right != nullptr)
            cout << node->right->name;
        else
            cout << "NULL";

        cout << "\n\n";

        display(node->left);
        display(node->right);
    }

    void destroy(Node* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    ~BinaryTree() {
        destroy(root);
    }
};

class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        id = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int value, bool& added) {
        if (node == nullptr) {
            added = true;
            return new BSTNode(value);
        }

        if (value < node->id)
            node->left = insert(node->left, value, added);
        else if (value > node->id)
            node->right = insert(node->right, value, added);
        else
            cout << "Duplicate ID rejected: " << value << endl;

        return node;
    }

    bool search(BSTNode* node, int value, int& visits) {
        if (node == nullptr)
            return false;

        visits++;

        if (node->id == value)
            return true;

        if (value < node->id)
            return search(node->left, value, visits);

        return search(node->right, value, visits);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int value, bool& removed) {
        if (node == nullptr)
            return nullptr;

        if (value < node->id)
            node->left = deleteNode(node->left, value, removed);
        else if (value > node->id)
            node->right = deleteNode(node->right, value, removed);
        else {
            removed = true;

            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->id = temp->id;

            bool successorRemoved = false;
            node->right = deleteNode(
                node->right, temp->id, successorRemoved
            );
        }

        return node;
    }

    void inorder(BSTNode* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }

    void destroy(BSTNode* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        destroy(root);
    }

    void insertID(int value) {
        bool added = false;
        root = insert(root, value, added);

        if (added)
            cout << "ID inserted: " << value << endl;
    }

    void searchID(int value) {
        int visits = 0;
        bool found = search(root, value, visits);

        if (found)
            cout << "ID " << value << " exists. Node visits: "
                 << visits << endl;
        else
            cout << "ID " << value << " does not exist. Node visits: "
                 << visits << endl;
    }

    void deleteID(int value) {
        bool removed = false;
        root = deleteNode(root, value, removed);

        if (removed)
            cout << "ID deleted: " << value << endl;
        else
            cout << "ID not found: " << value << endl;

        cout << "IDs in ascending order: ";
        inorder(root);
        cout << endl;
    }

    void display() {
        cout << "IDs in ascending order: ";
        inorder(root);
        cout << endl;
    }
};

void insertInitialIDs(BST& tree) {
    tree.insertID(48);
    tree.insertID(28);
    tree.insertID(68);
    tree.insertID(18);
    tree.insertID(38);
    tree.insertID(58);
    tree.insertID(78);
}

void testDeletionCases() {
    cout << "\n--- Separate deletion tests using fresh trees ---\n";

    cout << "\n1. Leaf deletion (delete 18):\n";
    {
        BST tree;
        insertInitialIDs(tree);
        tree.deleteID(18);
    }

    cout << "\n2. One-child deletion (delete 28 after removing 18):\n";
    {
        BST tree;
        insertInitialIDs(tree);
        tree.deleteID(18);
        tree.deleteID(28);
    }

    cout << "\n3. Two-child deletion (delete 28):\n";
    {
        BST tree;
        insertInitialIDs(tree);
        tree.deleteID(28);
    }
}

int main() {
    cout << "UNIVERSITY STAFF MANAGEMENT SYSTEM\n\n";

    BinaryTree staffTree;
    staffTree.root = new Node("Director");
    staffTree.root->left = new Node("Dean");
    staffTree.root->right = new Node("Registrar");
    staffTree.root->left->left = new Node("HOD Computer Science");
    staffTree.root->left->right = new Node("HOD Mathematics");
    staffTree.root->right->left = new Node("HR Manager");
    staffTree.root->right->right = new Node("Finance Manager");

    cout << "General Binary Tree:\n";
    staffTree.display(staffTree.root);

    cout << "BST of Staff IDs:\n";
    BST tree;
    insertInitialIDs(tree);

    int id;

    for (int i = 1; i <= 3; i++) {
        cout << "Enter additional staff ID " << i << ": ";
        cin >> id;
        tree.insertID(id);
    }

    cout << "\nSearch tests:\n";
    tree.searchID(48);

    cout << "Enter an ID to test a missing search: ";
    cin >> id;
    tree.searchID(id);

    tree.searchID(1);

    cout << "\nEnter a staff ID to delete: ";
    cin >> id;
    tree.deleteID(id);

    testDeletionCases();

    cout << "\nExplanation:\n";
    cout << "A general binary tree does not follow a sorting rule, "
         << "so in-order traversal may not be sorted.\n";

    cout << "A valid BST stores smaller IDs on the left and larger "
         << "IDs on the right, so in-order traversal is ascending.\n";

    return 0;
}
