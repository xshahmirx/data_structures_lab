
#include <iostream>
#include <string>
using namespace std;

struct PatientNode
{
    string name;
    int patientID;
    int priority;
    PatientNode* left;
    PatientNode* right;

    PatientNode(string n, int id, int p)
    {
        name = n;
        patientID = id;
        priority = p;
        left = NULL;
        right = NULL;
    }
};

class HospitalMaxHeap
{
private:
    PatientNode* root;
    int size;

    PatientNode* getNode(int index)
    {
        if (index == 1)
            return root;

        PatientNode* current = root;
        int bit = 1;

        while (bit * 2 <= index)
            bit *= 2;

        bit /= 2;

        while (bit > 0)
        {
            if (index & bit)
                current = current->right;
            else
                current = current->left;

            bit /= 2;
        }

        return current;
    }

    void swapData(PatientNode* a, PatientNode* b)
    {
        string tempName = a->name;
        a->name = b->name;
        b->name = tempName;

        int tempID = a->patientID;
        a->patientID = b->patientID;
        b->patientID = tempID;

        int tempPriority = a->priority;
        a->priority = b->priority;
        b->priority = tempPriority;
    }

    void heapifyUp(int index)
    {
        while (index > 1)
        {
            PatientNode* current = getNode(index);
            PatientNode* parent = getNode(index / 2);

            if (current->priority > parent->priority)
            {
                swapData(current, parent);
                index = index / 2;
            }
            else
                break;
        }
    }

    void heapifyDown(int index)
    {
        while (index * 2 <= size)
        {
            int largest = index;
            int leftIndex = index * 2;
            int rightIndex = index * 2 + 1;

            PatientNode* current = getNode(index);
            PatientNode* leftChild = getNode(leftIndex);

            if (leftChild->priority > current->priority)
                largest = leftIndex;

            if (rightIndex <= size)
            {
                PatientNode* rightChild = getNode(rightIndex);
                PatientNode* largestNode = getNode(largest);

                if (rightChild->priority > largestNode->priority)
                    largest = rightIndex;
            }

            if (largest != index)
            {
                swapData(getNode(index), getNode(largest));
                index = largest;
            }
            else
                break;
        }
    }

public:
    HospitalMaxHeap()
    {
        root = NULL;
        size = 0;
    }

    void insert(string name, int id, int priority)
    {
        PatientNode* newNode = new PatientNode(name, id, priority);
        size++;

        if (size == 1)
            root = newNode;
        else
        {
            PatientNode* parent = getNode(size / 2);

            if (size % 2 == 0)
                parent->left = newNode;
            else
                parent->right = newNode;
        }

        heapifyUp(size);
    }

    void display()
    {
        if (root == NULL)
        {
            cout << "No patients in the heap." << endl;
            return;
        }

        PatientNode* queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        cout << "\nHospital Emergency Heap (Level Order):\n";

        while (front < rear)
        {
            PatientNode* current = queue[front++];

            cout << "Patient: " << current->name
                 << " | Patient ID: " << current->patientID
                 << " | Priority: " << current->priority << endl;

            if (current->left != NULL)
                queue[rear++] = current->left;

            if (current->right != NULL)
                queue[rear++] = current->right;
        }
    }

    void treatHighestPriority()
    {
        if (root == NULL)
        {
            cout << "No patients available." << endl;
            return;
        }

        cout << "\nPatient Being Treated: " << root->name
             << " | Patient ID: " << root->patientID
             << " | Priority: " << root->priority << endl;

        if (size == 1)
        {
            delete root;
            root = NULL;
            size = 0;
            return;
        }

        PatientNode* lastNode = getNode(size);
        PatientNode* lastParent = getNode(size / 2);

        swapData(root, lastNode);

        if (size % 2 == 0)
            lastParent->left = NULL;
        else
            lastParent->right = NULL;

        delete lastNode;
        size--;

        heapifyDown(1);
    }

    void displayNextPatient()
    {
        if (root == NULL)
            cout << "\nNo patients are waiting." << endl;
        else
            cout << "\nNext Patient to be Treated: "
                 << root->name
                 << " | Patient ID: " << root->patientID
                 << " | Priority: " << root->priority << endl;
    }
};

int main()
{
    HospitalMaxHeap hospital;

    hospital.insert("Ali", 201, 3);
    hospital.insert("Ahmed", 202, 8);
    hospital.insert("Sara", 203, 5);
    hospital.insert("Usman", 204, 10);
    hospital.insert("Ayesha", 205, 6);
    hospital.insert("Hamza", 206, 9);

    cout << "HOSPITAL EMERGENCY MANAGEMENT SYSTEM";
    hospital.display();

    cout << "\nHighest Priority Patient";
    hospital.displayNextPatient();

    cout << "\nTreating Highest Priority Patient";
    hospital.treatHighestPriority();

    cout << "\nUpdated Hospital Emergency Heap";
    hospital.display();

    hospital.displayNextPatient();

    return 0;
}
