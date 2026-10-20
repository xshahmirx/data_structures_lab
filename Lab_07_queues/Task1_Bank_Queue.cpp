
#include <iostream>
using namespace std;

const int SIZE = 5;

class Queue {
    int customers[SIZE];
    int front, rear;

public:
    Queue() {
        front = 0;
        rear = -1;
    }

    void enqueue(int token) {
        if (rear == SIZE - 1) {
            cout << "Queue Overflow!\n";
            return;
        }

        customers[++rear] = token;
        cout << "Customer " << token << " added.\n";
    }

    void dequeue() {
        if (front > rear) {
            cout << "Queue Underflow! No customers waiting.\n";
            return;
        }

        cout << "Serving customer: " << customers[front] << endl;
        front++;
    }

    void display() {
        if (front > rear) {
            cout << "No customers waiting.\n";
            return;
        }

        cout << "Waiting customers: ";
        for (int i = front; i <= rear; i++) {
            cout << customers[i] << " ";
        }
        cout << endl;
    }

    void countCustomers() {
        if (front > rear)
            cout << "Number of waiting customers: 0\n";
        else
            cout << "Number of waiting customers: "
                 << rear - front + 1 << endl;
    }
};

int main() {
    Queue q;
    int choice, token;

    do {
        cout << "\n--- Bank Customer Service System ---\n";
        cout << "1. Add Customer\n";
        cout << "2. Serve Customer\n";
        cout << "3. Display Customers\n";
        cout << "4. Count Customers\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter token number: ";
                cin >> token;
                q.enqueue(token);
                break;
            case 2:
                q.dequeue();
                break;
            case 3:
                q.display();
                break;
            case 4:
                q.countCustomers();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
