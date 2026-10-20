
#include <iostream>
using namespace std;

const int SIZE = 5;

class CircularQueue {
    int packets[SIZE];
    int front, rear, count;

public:
    CircularQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    void enqueue(int id) {
        if (count == SIZE) {
            cout << "Queue Full! Cannot add packet.\n";
            return;
        }

        rear = (rear + 1) % SIZE;
        packets[rear] = id;
        count++;

        cout << "Packet " << id << " added.\n";
    }

    void dequeue() {
        if (count == 0) {
            cout << "Queue Empty! No packets waiting.\n";
            return;
        }

        cout << "Transmitting packet: " << packets[front] << endl;
        front = (front + 1) % SIZE;
        count--;
    }

    void display() {
        if (count == 0) {
            cout << "No packets waiting.\n";
            return;
        }

        cout << "Packets waiting: ";
        for (int i = 0; i < count; i++) {
            cout << packets[(front + i) % SIZE] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q;
    int choice, id;

    do {
        cout << "\n--- Network Data Packet Management ---\n";
        cout << "1. Add Packet\n";
        cout << "2. Transmit Packet\n";
        cout << "3. Display Packets\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter packet ID: ";
                cin >> id;
                q.enqueue(id);
                break;
            case 2:
                q.dequeue();
                break;
            case 3:
                q.display();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
