
#include <iostream>
#include <string>
using namespace std;

struct MedicineNode
{
    string medicineName;
    int medicineID;
    int expiryDate;
    MedicineNode* left;
    MedicineNode* right;

    MedicineNode(string name, int id, int date)
    {
        medicineName = name;
        medicineID = id;
        expiryDate = date;
        left = NULL;
        right = NULL;
    }
};

class MedicineMinHeap
{
private:
    MedicineNode* root;
    int size;

    MedicineNode* getNode(int index)
    {
        if (index == 1)
            return root;

        MedicineNode* current = root;
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

    void swapData(MedicineNode* a, MedicineNode* b)
    {
        string tempName = a->medicineName;
        a->medicineName = b->medicineName;
        b->medicineName = tempName;

        int tempID = a->medicineID;
        a->medicineID = b->medicineID;
        b->medicineID = tempID;

        int tempDate = a->expiryDate;
        a->expiryDate = b->expiryDate;
        b->expiryDate = tempDate;
    }

    void heapifyUp(int index)
    {
        while (index > 1)
        {
            MedicineNode* current = getNode(index);
            MedicineNode* parent = getNode(index / 2);

            if (current->expiryDate < parent->expiryDate)
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
            int smallest = index;
            int leftIndex = index * 2;
            int rightIndex = index * 2 + 1;

            MedicineNode* current = getNode(index);
            MedicineNode* leftChild = getNode(leftIndex);

            if (leftChild->expiryDate < current->expiryDate)
                smallest = leftIndex;

            if (rightIndex <= size)
            {
                MedicineNode* rightChild = getNode(rightIndex);
                MedicineNode* smallestNode = getNode(smallest);

                if (rightChild->expiryDate < smallestNode->expiryDate)
                    smallest = rightIndex;
            }

            if (smallest != index)
            {
                swapData(getNode(index), getNode(smallest));
                index = smallest;
            }
            else
                break;
        }
    }

public:
    MedicineMinHeap()
    {
        root = NULL;
        size = 0;
    }

    void insert(string name, int id, int date)
    {
        MedicineNode* newNode = new MedicineNode(name, id, date);
        size++;

        if (size == 1)
            root = newNode;
        else
        {
            MedicineNode* parent = getNode(size / 2);

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
            cout << "No medicines available." << endl;
            return;
        }

        MedicineNode* queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        cout << "\nMedicine Min Heap (Level Order):\n";

        while (front < rear)
        {
            MedicineNode* current = queue[front++];

            cout << "Medicine: " << current->medicineName
                 << " | Medicine ID: " << current->medicineID
                 << " | Expiry Date: " << current->expiryDate << endl;

            if (current->left != NULL)
                queue[rear++] = current->left;

            if (current->right != NULL)
                queue[rear++] = current->right;
        }
    }

    void deleteNearestExpiry()
    {
        if (root == NULL)
        {
            cout << "No medicines available." << endl;
            return;
        }

        cout << "\nMedicine With Nearest Expiry Date Deleted:\n";
        cout << "Medicine: " << root->medicineName
             << " | Medicine ID: " << root->medicineID
             << " | Expiry Date: " << root->expiryDate << endl;

        if (size == 1)
        {
            delete root;
            root = NULL;
            size = 0;
            return;
        }

        MedicineNode* lastNode = getNode(size);
        MedicineNode* lastParent = getNode(size / 2);

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
    MedicineMinHeap medicines;

    medicines.insert("Panadol", 401, 20270115);
    medicines.insert("Brufen", 402, 20261210);
    medicines.insert("Augmentin", 403, 20280320);
    medicines.insert("Calpol", 404, 20261130);
    medicines.insert("Disprin", 405, 20270525);
    medicines.insert("Flagyl", 406, 20270218);

    cout << "HOSPITAL MEDICINE EXPIRY MANAGEMENT";
    medicines.display();

    medicines.deleteNearestExpiry();

    cout << "\nUpdated Medicine Min Heap";
    medicines.display();

    return 0;
}
