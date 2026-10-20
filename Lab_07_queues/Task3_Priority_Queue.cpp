
#include <iostream>
using namespace std;

const int SIZE = 5;

class PriorityQueue {
    int patientID[SIZE];
    int priority[SIZE];
    int count;

public:
    PriorityQueue() {
        count = 0;
    }

    void enqueue(int id, int p) {
        if (count == SIZE) {
            cout << "Queue Full! Cannot add patient.\n";
            return;
        }

        patientID[count] = id;
        priority[count] = p;
        count++;

        cout << "Patient P" << id
             << " added with priority " << p << ".\n";
    }

    void dequeue() {
        if (count == 0) {
            cout << "Queue Empty! No patients waiting.\n";
            return;
        }

        int highest = 0;

        for (int i = 1; i < count; i++) {
            if (priority[i] < priority[highest]) {
                highest = i;
            }
        }

        cout << "Treating patient P" << patientID[highest]
             << " with priority " << priority[highest] << ".\n";

        for (int i = highest; i < count - 1; i++) {
            patientID[i] = patientID[i + 1];
            priority[i] = priority[i + 1];
        }

        count--;
    }

    void display() {
        if (count == 0) {
            cout << "No patients waiting.\n";
            return;
        }

        cout << "Waiting patients:\n";
        for (int i = 0; i < count; i++) {
            cout << "Patient P" << patientID[i]
                 << " | Priority: " << priority[i] << endl;
        }
    }
};

int main() {
    PriorityQueue q;
    int choice, id, p;

    do {
        cout << "\n--- Hospital Emergency Department ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Treat Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient ID: ";
                cin >> id;
                cout << "Enter priority (1 = highest): ";
                cin >> p;

                if (p < 1) {
                    cout << "Invalid priority.\n";
                } else {
                    q.enqueue(id, p);
                }
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
