
#include <iostream>
#include <string>
using namespace std;

struct StudentNode
{
    string name;
    int rollNumber;
    float marks;
    StudentNode* left;
    StudentNode* right;

    StudentNode(string n, int r, float m)
    {
        name = n;
        rollNumber = r;
        marks = m;
        left = NULL;
        right = NULL;
    }
};

class StudentMaxHeap
{
private:
    StudentNode* root;
    int size;

    StudentNode* getNode(int index)
    {
        if (index == 1)
            return root;

        StudentNode* current = root;
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

    void swapData(StudentNode* a, StudentNode* b)
    {
        string tempName = a->name;
        a->name = b->name;
        b->name = tempName;

        int tempRoll = a->rollNumber;
        a->rollNumber = b->rollNumber;
        b->rollNumber = tempRoll;

        float tempMarks = a->marks;
        a->marks = b->marks;
        b->marks = tempMarks;
    }

    void heapifyUp(int index)
    {
        while (index > 1)
        {
            StudentNode* current = getNode(index);
            StudentNode* parent = getNode(index / 2);

            if (current->marks > parent->marks)
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

            StudentNode* current = getNode(index);
            StudentNode* leftChild = getNode(leftIndex);

            if (leftChild->marks > current->marks)
                largest = leftIndex;

            if (rightIndex <= size)
            {
                StudentNode* rightChild = getNode(rightIndex);
                StudentNode* largestNode = getNode(largest);

                if (rightChild->marks > largestNode->marks)
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
    StudentMaxHeap()
    {
        root = NULL;
        size = 0;
    }

    void insert(string name, int roll, float marks)
    {
        StudentNode* newNode = new StudentNode(name, roll, marks);
        size++;

        if (size == 1)
            root = newNode;
        else
        {
            StudentNode* parent = getNode(size / 2);

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
            cout << "Heap is empty." << endl;
            return;
        }

        StudentNode* queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        cout << "\nStudent Merit Heap (Level Order):\n";

        while (front < rear)
        {
            StudentNode* current = queue[front++];

            cout << "Name: " << current->name
                 << " | Roll Number: " << current->rollNumber
                 << " | Marks: " << current->marks << endl;

            if (current->left != NULL)
                queue[rear++] = current->left;

            if (current->right != NULL)
                queue[rear++] = current->right;
        }
    }

    void deleteHighestMarks()
    {
        if (root == NULL)
        {
            cout << "No students available." << endl;
            return;
        }

        cout << "\nDeleted Student: " << root->name
             << " | Roll Number: " << root->rollNumber
             << " | Marks: " << root->marks << endl;

        if (size == 1)
        {
            delete root;
            root = NULL;
            size = 0;
            return;
        }

        StudentNode* lastNode = getNode(size);
        StudentNode* lastParent = getNode(size / 2);

        swapData(root, lastNode);

        if (size % 2 == 0)
            lastParent->left = NULL;
        else
            lastParent->right = NULL;

        delete lastNode;
        size--;

        heapifyDown(1);
    }
};

int main()
{
    StudentMaxHeap students;

    students.insert("Ali", 101, 85);
    students.insert("Ahmed", 102, 92);
    students.insert("Sara", 103, 96);
    students.insert("Usman", 104, 78);
    students.insert("Ayesha", 105, 89);
    students.insert("Hamza", 106, 94);

    cout << "UNIVERSITY STUDENT MERIT RANKING";
    students.display();

    cout << "\nRemoving Student With Highest Marks";
    students.deleteHighestMarks();

    cout << "\nUpdated Student Merit Heap";
    students.display();

    return 0;
}
