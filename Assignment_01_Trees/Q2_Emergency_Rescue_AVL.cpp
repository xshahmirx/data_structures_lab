#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
public:
    int emergencyID;
    int severity;
    int height;
    string location;
    Node *left, *right;

    Node(int id, string loc, int sev) {
        emergencyID = id;
        location = loc;
        severity = sev;
        height = 1;
        left = right = NULL;
    }
};

class AVL {
    Node *root;

    int getHeight(Node *n) {
        if (n == NULL)
            return 0;

        return n->height;
    }

    int getBalance(Node *n) {
        if (n == NULL)
            return 0;

        return getHeight(n->left) - getHeight(n->right);
    }

    void updateHeight(Node *n) {
        n->height = 1 + max(
            getHeight(n->left),
            getHeight(n->right)
        );
    }

    // Right Rotation
    Node* rightRotate(Node *y) {
        Node *x = y->left;
        Node *temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left Rotation
    Node* leftRotate(Node *x) {
        Node *y = x->right;
        Node *temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balanceTree(Node *n) {
        if (n == NULL)
            return n;

        updateHeight(n);

        int balance = getBalance(n);

        // LL Case
        if (balance > 1 && getBalance(n->left) >= 0)
            return rightRotate(n);

        // LR Case
        if (balance > 1 && getBalance(n->left) < 0) {
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

        // RR Case
        if (balance < -1 && getBalance(n->right) <= 0)
            return leftRotate(n);

        // RL Case
        if (balance < -1 && getBalance(n->right) > 0) {
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }

        return n;
    }

    Node* insertNode(Node *n, int id, string loc, int sev) {
        if (n == NULL)
            return new Node(id, loc, sev);

        if (id < n->emergencyID)
            n->left = insertNode(n->left, id, loc, sev);

        else if (id > n->emergencyID)
            n->right = insertNode(n->right, id, loc, sev);

        else {
            cout << "Duplicate Emergency ID.\n";
            return n;
        }

        return balanceTree(n);
    }

    Node* minimumNode(Node *n) {
        while (n->left != NULL)
            n = n->left;

        return n;
    }

    Node* deleteNode(Node *n, int id) {
        if (n == NULL)
            return NULL;

        if (id < n->emergencyID)
            n->left = deleteNode(n->left, id);

        else if (id > n->emergencyID)
            n->right = deleteNode(n->right, id);

        else {
            // Node has zero or one child
            if (n->left == NULL || n->right == NULL) {
                Node *temp;

                if (n->left != NULL)
                    temp = n->left;
                else
                    temp = n->right;

                delete n;
                return temp;
            }

            // Node has two children
            Node *temp = minimumNode(n->right);

            n->emergencyID = temp->emergencyID;
            n->location = temp->location;
            n->severity = temp->severity;

            n->right = deleteNode(
                n->right,
                temp->emergencyID
            );
        }

        return balanceTree(n);
    }

    Node* searchNode(Node *n, int id) {
        if (n == NULL || n->emergencyID == id)
            return n;

        if (id < n->emergencyID)
            return searchNode(n->left, id);

        return searchNode(n->right, id);
    }

    void displayRecord(Node *n) {
        cout << "Emergency ID: " << n->emergencyID
             << " | Location: " << n->location
             << " | Severity: " << n->severity << endl;
    }

    void inorder(Node *n) {
        if (n == NULL)
            return;

        inorder(n->left);
        displayRecord(n);
        inorder(n->right);
    }

    void showNodeDetails(Node *n) {
        if (n == NULL)
            return;

        showNodeDetails(n->left);

        cout << "Emergency ID: " << n->emergencyID
             << " | Height: " << n->height
             << " | Balance Factor: " << getBalance(n)
             << endl;

        showNodeDetails(n->right);
    }

    void displayTree(Node *n, int space) {
        if (n == NULL)
            return;

        space += 5;

        displayTree(n->right, space);

        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";

        cout << n->emergencyID << endl;

        displayTree(n->left, space);
    }

public:
    AVL() {
        root = NULL;
    }

    void insert(int id, string loc, int sev) {
        root = insertNode(root, id, loc, sev);
    }

    void search(int id) {
        Node *result = searchNode(root, id);

        if (result == NULL) {
            cout << "Emergency record not found.\n";
        }
        else {
            cout << "Emergency record found:\n";
            displayRecord(result);
        }
    }

    void remove(int id) {
        if (searchNode(root, id) == NULL) {
            cout << "Emergency ID not found.\n";
        }
        else {
            root = deleteNode(root, id);
            cout << "Emergency record deleted successfully.\n";
            cout << "AVL tree has been balanced again.\n";
        }
    }

    void displayInorder() {
        cout << "\n===== INORDER TRAVERSAL =====\n";

        if (root == NULL)
            cout << "Tree is empty.\n";
        else
            inorder(root);
    }

    void displayLevelOrder() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        queue<Node*> q;
        q.push(root);

        cout << "\n===== LEVEL ORDER TRAVERSAL (BFS) =====\n";

        while (!q.empty()) {
            Node *current = q.front();
            q.pop();

            displayRecord(current);

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }
    }

    void displayHeightBalance() {
        cout << "\n===== HEIGHT AND BALANCE FACTORS =====\n";

        if (root == NULL)
            cout << "Tree is empty.\n";
        else
            showNodeDetails(root);
    }

    void display() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "\n===== FINAL AVL TREE STRUCTURE =====\n";
        cout << "(Right side appears above)\n";

        displayTree(root, 0);
    }
};

int main() {
    AVL rescue;

    int emergencyIDs[12] = {
        40, 20, 60, 10, 30, 50,
        70, 5, 15, 25, 35, 55
    };

    string locations[12] = {
        "North", "South", "East", "West",
        "Central", "Airport", "Market",
        "Sector A", "Sector B", "Sector C",
        "Sector D", "Sector E"
    };

    int severityLevels[12] = {
        5, 4, 3, 5, 2, 4,
        1, 5, 3, 2, 4, 3
    };

    for (int i = 0; i < 12; i++) {
        rescue.insert(
            emergencyIDs[i],
            locations[i],
            severityLevels[i]
        );
    }

    cout << "12 emergency records inserted successfully.\n";

    int choice, id, severity;
    string location;

    do {
        cout << "\n===== EMERGENCY RESCUE OPERATIONS =====\n";
        cout << "1. Insert Emergency\n";
        cout << "2. Search Emergency\n";
        cout << "3. Delete Emergency\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Level Order Traversal (BFS)\n";
        cout << "6. Display Height and Balance Factors\n";
        cout << "7. Display Final AVL Tree\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Emergency ID: ";
            cin >> id;

            cout << "Enter Location: ";
            getline(cin >> ws, location);

            cout << "Enter Severity Level (1-5): ";
            cin >> severity;

            if (severity < 1 || severity > 5) {
                cout << "Invalid severity. Enter a value from 1 to 5.\n";
            }
            else {
                rescue.insert(id, location, severity);
            }
        }
        else if (choice == 2) {
            cout << "Enter Emergency ID to Search: ";
            cin >> id;

            rescue.search(id);
        }
        else if (choice == 3) {
            cout << "Enter Emergency ID to Delete: ";
            cin >> id;

            rescue.remove(id);
        }
        else if (choice == 4) {
            rescue.displayInorder();
        }
        else if (choice == 5) {
            rescue.displayLevelOrder();
        }
        else if (choice == 6) {
            rescue.displayHeightBalance();
        }
        else if (choice == 7) {
            rescue.display();
        }
        else if (choice == 8) {
            cout << "Exiting Emergency Rescue System.\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}