
#include <iostream>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;

    Node(int value) {
        id = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insertNode(Node* node, int value, bool& added) {
        if (node == nullptr) {
            added = true;
            return new Node(value);
        }

        if (value < node->id)
            node->left = insertNode(node->left, value, added);
        else if (value > node->id)
            node->right = insertNode(node->right, value, added);

        return node;
    }

    bool searchNode(Node* node, int value) {
        if (node == nullptr)
            return false;

        if (node->id == value)
            return true;

        if (value < node->id)
            return searchNode(node->left, value);

        return searchNode(node->right, value);
    }

    Node* findMin(Node* node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int value, bool& removed) {
        if (node == nullptr)
            return nullptr;

        if (value < node->id)
            node->left = deleteNode(node->left, value, removed);
        else if (value > node->id)
            node->right = deleteNode(node->right, value, removed);
        else {
            removed = true;

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->id = temp->id;

            bool successorRemoved = false;
            node->right = deleteNode(
                node->right, temp->id, successorRemoved
            );
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr)
            return;

        cout << node->id << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->id << " ";
    }

    int countNodes(Node* node) {
        if (node == nullptr)
            return 0;

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    int height(Node* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;

        return rightHeight + 1;
    }

    void destroy(Node* node) {
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

    void insert(int value) {
        bool added = false;
        root = insertNode(root, value, added);

        if (added)
            cout << "ID inserted successfully.\n";
        else
            cout << "Duplicate ID rejected. Tree unchanged.\n";
    }

    void search(int value) {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
            return;
        }

        if (searchNode(root, value))
            cout << "ID exists in the tree.\n";
        else
            cout << "ID was not found.\n";
    }

    void remove(int value) {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
            return;
        }

        bool removed = false;
        root = deleteNode(root, value, removed);

        if (removed) {
            cout << "ID deleted successfully.\n";
            cout << "Updated in-order traversal: ";
            inorder(root);
            cout << endl;
        } else {
            cout << "ID was not found. Tree unchanged.\n";
        }
    }

    void showInorder() {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
            return;
        }

        cout << "In-order: ";
        inorder(root);
        cout << endl;
    }

    void showPreorder() {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
            return;
        }

        cout << "Pre-order: ";
        preorder(root);
        cout << endl;
    }

    void showPostorder() {
        if (root == nullptr) {
            cout << "The tree is empty.\n";
            return;
        }

        cout << "Post-order: ";
        postorder(root);
        cout << endl;
    }

    void showCount() {
        cout << "Total nodes: " << countNodes(root) << endl;
    }

    void showHeight() {
        cout << "Height (number of levels): "
             << height(root) << endl;
    }
};

int main() {
    BST tree;

    tree.insert(55);
    tree.insert(35);
    tree.insert(75);
    tree.insert(25);
    tree.insert(45);
    tree.insert(65);
    tree.insert(85);
    tree.insert(40);
    tree.insert(50);

    int choice, id;

    do {
        cout << "\nHOSPITAL AND EMERGENCY INVENTORY MANAGEMENT SYSTEM\n";
        cout << "1. Insert an ID\n";
        cout << "2. Search for an ID\n";
        cout << "3. Delete an ID\n";
        cout << "4. Display in-order traversal\n";
        cout << "5. Display pre-order traversal\n";
        cout << "6. Display post-order traversal\n";
        cout << "7. Count total nodes\n";
        cout << "8. Calculate height\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number from 1 to 9.\n";
            choice = 0;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter ID to insert: ";
            cin >> id;
            tree.insert(id);
            break;

        case 2:
            cout << "Enter ID to search: ";
            cin >> id;
            tree.search(id);
            break;

        case 3:
            cout << "Enter ID to delete: ";
            cin >> id;
            tree.remove(id);
            break;

        case 4:
            tree.showInorder();
            break;

        case 5:
            tree.showPreorder();
            break;

        case 6:
            tree.showPostorder();
            break;

        case 7:
            tree.showCount();
            break;

        case 8:
            tree.showHeight();
            break;

        case 9:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice. Enter a number from 1 to 9.\n";
        }

    } while (choice != 9);

    return 0;
}
