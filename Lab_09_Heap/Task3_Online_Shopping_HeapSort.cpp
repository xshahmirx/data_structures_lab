#include <iostream>
#include <string>
using namespace std;

struct OrderNode
{
    int orderID;
    string customerName;
    double orderAmount;
    OrderNode* left;
    OrderNode* right;

    OrderNode(int id, string name, double amount)
    {
        orderID = id;
        customerName = name;
        orderAmount = amount;
        left = NULL;
        right = NULL;
    }
};

class OrderMaxHeap
{
private:
    OrderNode* root;
    int size;

    OrderNode* getNode(int index)
    {
        if (index == 1)
            return root;

        OrderNode* current = root;
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

    void swapData(OrderNode* a, OrderNode* b)
    {
        int tempID = a->orderID;
        a->orderID = b->orderID;
        b->orderID = tempID;

        string tempName = a->customerName;
        a->customerName = b->customerName;
        b->customerName = tempName;

        double tempAmount = a->orderAmount;
        a->orderAmount = b->orderAmount;
        b->orderAmount = tempAmount;
    }

    void heapifyUp(int index)
    {
        while (index > 1)
        {
            OrderNode* current = getNode(index);
            OrderNode* parent = getNode(index / 2);

            if (current->orderAmount > parent->orderAmount)
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

            OrderNode* current = getNode(index);
            OrderNode* leftChild = getNode(leftIndex);

            if (leftChild->orderAmount > current->orderAmount)
                largest = leftIndex;

            if (rightIndex <= size)
            {
                OrderNode* rightChild = getNode(rightIndex);
                OrderNode* largestNode = getNode(largest);

                if (rightChild->orderAmount > largestNode->orderAmount)
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
    OrderMaxHeap()
    {
        root = NULL;
        size = 0;
    }

    void insert(int id, string name, double amount)
    {
        OrderNode* newNode = new OrderNode(id, name, amount);
        size++;

        if (size == 1)
            root = newNode;
        else
        {
            OrderNode* parent = getNode(size / 2);

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
            cout << "No orders available." << endl;
            return;
        }

        OrderNode* queue[100];
        int front = 0, rear = 0;

        queue[rear++] = root;

        cout << "\nOrders in Max Heap (Level Order):\n";

        while (front < rear)
        {
            OrderNode* current = queue[front++];

            cout << "Order ID: " << current->orderID
                 << " | Customer: " << current->customerName
                 << " | Amount: " << current->orderAmount << endl;

            if (current->left != NULL)
                queue[rear++] = current->left;

            if (current->right != NULL)
                queue[rear++] = current->right;
        }
    }

    double deleteRoot()
    {
        if (root == NULL)
            return 0;

        double deletedAmount = root->orderAmount;

        if (size == 1)
        {
            delete root;
            root = NULL;
            size = 0;
            return deletedAmount;
        }

        OrderNode* lastNode = getNode(size);
        OrderNode* lastParent = getNode(size / 2);

        swapData(root, lastNode);

        if (size % 2 == 0)
            lastParent->left = NULL;
        else
            lastParent->right = NULL;

        delete lastNode;
        size--;

        heapifyDown(1);

        return deletedAmount;
    }

    void heapSort()
    {
        double deletedAmounts[100];
        int count = 0;

        cout << "\nDeleting Orders from Max Heap:\n";

        while (size > 0)
        {
            double amount = deleteRoot();
            deletedAmounts[count] = amount;
            count++;

            cout << "Deleted Order Amount: " << amount << endl;
        }

        cout << "\nOrder Amounts in Ascending Order:\n";

        for (int i = count - 1; i >= 0; i--)
            cout << deletedAmounts[i] << endl;
    }
};

int main()
{
    OrderMaxHeap orders;

    orders.insert(301, "Ali", 2500);
    orders.insert(302, "Ahmed", 7500);
    orders.insert(303, "Sara", 1200);
    orders.insert(304, "Usman", 9800);
    orders.insert(305, "Ayesha", 4300);
    orders.insert(306, "Hamza", 6100);

    cout << "ONLINE SHOPPING ORDER SORTING";
    orders.display();

    orders.heapSort();

    return 0;
}
