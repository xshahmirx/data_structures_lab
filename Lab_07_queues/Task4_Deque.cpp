
#include <iostream>
using namespace std;

const int SIZE = 5;

class Deque {
    int passengers[SIZE];
    int front, rear, count;

public:
    Deque() {
        front = 0;
        rear = -1;
        count = 0;
    }

    void insertFront(int id) {
        if (count == SIZE) {
            cout << "Deque Full! Cannot add request.\n";
            return;
        }

        if (count == 0) {
            front = rear = 0;
        } else {
            front = (front - 1 + SIZE) % SIZE;
        }

        passengers[front] = id;
        count++;

        cout << "Request " << id << " added at front.\n";
    }

    void insertRear(int id) {
        if (count == SIZE) {
            cout << "Deque Full! Cannot add request.\n";
            return;
        }

        if (count == 0) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }

        passengers[rear] = id;
        count++;

        cout << "Request " << id << " added at rear.\n";
    }

    void deleteFront() {
        if (count == 0) {
            cout << "Deque Empty! No requests to remove.\n";
            return;
        }

        cout << "Removed from front: " << passengers[front] << endl;

        if (count == 1) {
            front = 0;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }

        count--;
    }

    void deleteRear() {
        if (count == 0) {
            cout << "Deque Empty! No requests to remove.\n";
            return;
        }

        cout << "Removed from rear: " << passengers[rear] << endl;

        if (count == 1) {
            front = 0;
            rear = -1;
        } else {
            rear = (rear - 1 + SIZE) % SIZE;
        }

        count--;
    }

    void display() {
        if (count == 0) {
            cout << "No passenger requests waiting.\n";
            return;
        }

        cout << "Front -> ";
        for (int i = 0; i < count; i++) {
            cout << passengers[(front + i) % SIZE] << " ";
        }
        cout << "<- Rear\n";
    }
};

int main() {
    Deque d;
    int choice, id;

    do {
        cout << "\n--- Train Station Passenger Management ---\n";
        cout << "1. Insert at Front\n";
        cout << "2. Insert at Rear\n";
        cout << "3. Remove from Front\n";
        cout << "4. Remove from Rear\n";
        cout << "5. Display Requests\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter request ID: ";
                cin >> id;
                d.insertFront(id);
                break;
            case 2:
                cout << "Enter request ID: ";
                cin >> id;
                d.insertRear(id);
                break;
            case 3:
                d.deleteFront();
                break;
            case 4:
                d.deleteRear();
                break;
            case 5:
                d.display();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
