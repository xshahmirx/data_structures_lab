#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int flightNo;
    string destination, departure;
    Node *left, *right;

    Node(int n, string d, string t) {
        flightNo = n;
        destination = d;
        departure = t;
        left = right = NULL;
    }
};

class BST {
    Node *root;

    Node* add(Node *r, int n, string d, string t) {
        if (r == NULL)
            return new Node(n, d, t);

        if (n < r->flightNo)
            r->left = add(r->left, n, d, t);
        else if (n > r->flightNo)
            r->right = add(r->right, n, d, t);
        else
            cout << "Duplicate flight number.\n";

        return r;
    }

    Node* find(Node *r, int n) {
        if (r == NULL || r->flightNo == n)
            return r;

        if (n < r->flightNo)
            return find(r->left, n);

        return find(r->right, n);
    }

    Node* minNode(Node *r) {
        while (r != NULL && r->left != NULL)
            r = r->left;

        return r;
    }

    Node* erase(Node *r, int n) {
        if (r == NULL)
            return NULL;

        if (n < r->flightNo)
            r->left = erase(r->left, n);

        else if (n > r->flightNo)
            r->right = erase(r->right, n);

        else {
            // Case 1: No left child
            if (r->left == NULL) {
                Node *temp = r->right;
                delete r;
                return temp;
            }

            // Case 2: No right child
            if (r->right == NULL) {
                Node *temp = r->left;
                delete r;
                return temp;
            }

            // Case 3: Two children
            Node *temp = minNode(r->right);

            r->flightNo = temp->flightNo;
            r->destination = temp->destination;
            r->departure = temp->departure;

            r->right = erase(r->right, temp->flightNo);
        }

        return r;
    }

    void show(Node *r) {
        cout << "Flight Number: " << r->flightNo
             << " | Destination: " << r->destination
             << " | Departure: " << r->departure << endl;
    }

    void inorder(Node *r) {
        if (r == NULL)
            return;

        inorder(r->left);
        show(r);
        inorder(r->right);
    }

    void preorder(Node *r) {
        if (r == NULL)
            return;

        show(r);
        preorder(r->left);
        preorder(r->right);
    }

    void postorder(Node *r) {
        if (r == NULL)
            return;

        postorder(r->left);
        postorder(r->right);
        show(r);
    }

    int count(Node *r) {
        if (r == NULL)
            return 0;

        return 1 + count(r->left) + count(r->right);
    }

    int height(Node *r) {
        if (r == NULL)
            return 0;

        int leftHeight = height(r->left);
        int rightHeight = height(r->right);

        if (leftHeight > rightHeight)
            return 1 + leftHeight;

        return 1 + rightHeight;
    }

    void displayTree(Node *r, int space) {
        if (r == NULL)
            return;

        space += 5;

        displayTree(r->right, space);

        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";

        cout << r->flightNo << endl;

        displayTree(r->left, space);
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int n, string d, string t) {
        root = add(root, n, d, t);
    }

    void search(int n) {
        Node *result = find(root, n);

        if (result == NULL)
            cout << "Flight not found.\n";
        else {
            cout << "Flight found:\n";
            show(result);
        }
    }

    void remove(int n) {
        if (find(root, n) == NULL) {
            cout << "Flight not found.\n";
        } else {
            root = erase(root, n);
            cout << "Flight deleted successfully.\n";
        }
    }

    void traversals() {
        cout << "\nINORDER TRAVERSAL\n";
        inorder(root);

        cout << "\nPREORDER TRAVERSAL\n";
        preorder(root);

        cout << "\nPOSTORDER TRAVERSAL\n";
        postorder(root);
    }

    void minMax() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        Node *minimum = minNode(root);
        Node *maximum = root;

        while (maximum->right != NULL)
            maximum = maximum->right;

        cout << "\nMinimum Flight:\n";
        show(minimum);

        cout << "Maximum Flight:\n";
        show(maximum);
    }

    void statistics() {
        cout << "\nTotal Flights: " << count(root) << endl;
        cout << "Height of BST: " << height(root) << endl;
    }

    void display() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "\nBST STRUCTURE (Right side appears above)\n";
        displayTree(root, 0);
    }
};

int main() {
    BST airport;

    int flightNumbers[12] = {
        450, 250, 650, 150, 350, 550,
        750, 100, 200, 300, 400, 600
    };

    string destinations[12] = {
        "London", "Dubai", "Istanbul", "Doha",
        "Karachi", "Riyadh", "Paris", "Muscat",
        "Lahore", "Jeddah", "Tokyo", "Baku"
    };

    string departureTimes[12] = {
        "08:00", "08:30", "09:00", "09:30",
        "10:00", "10:30", "11:00", "11:30",
        "12:00", "12:30", "13:00", "13:30"
    };

    for (int i = 0; i < 12; i++) {
        airport.insert(
            flightNumbers[i],
            destinations[i],
            departureTimes[i]
        );
    }

    int choice, number;
    string destination, time;

    do {
        cout << "\n===== AIRPORT FLIGHT SCHEDULING SYSTEM =====\n";
        cout << "1. Insert Flight\n";
        cout << "2. Search Flight\n";
        cout << "3. Delete Flight\n";
        cout << "4. Display Traversals\n";
        cout << "5. Minimum and Maximum Flight\n";
        cout << "6. Count Flights and Tree Height\n";
        cout << "7. Display BST Structure\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Flight Number: ";
            cin >> number;

            cout << "Enter Destination: ";
            getline(cin >> ws, destination);

            cout << "Enter Departure Time: ";
            getline(cin >> ws, time);

            airport.insert(number, destination, time);
        }
        else if (choice == 2) {
            cout << "Enter Flight Number to Search: ";
            cin >> number;

            airport.search(number);
        }
        else if (choice == 3) {
            cout << "Enter Flight Number to Delete: ";
            cin >> number;

            airport.remove(number);
        }
        else if (choice == 4) {
            airport.traversals();
        }
        else if (choice == 5) {
            airport.minMax();
        }
        else if (choice == 6) {
            airport.statistics();
        }
        else if (choice == 7) {
            airport.display();
        }
        else if (choice == 8) {
            cout << "Exiting Airport System.\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}