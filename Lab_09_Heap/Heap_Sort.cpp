#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class MaxHeap
{
public:
    Node* root;

    MaxHeap()
    {
        root = NULL;
    }

    void insert(int value)
    {
        Node* newNode = new Node(value);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left == NULL)
            {
                temp->left = newNode;
                break;
            }
            else
                q.push(temp->left);

            if (temp->right == NULL)
            {
                temp->right = newNode;
                break;
            }
            else
                q.push(temp->right);
        }

        heapifyUp(newNode);
    }

    void heapifyUp(Node* newNode)
    {
        Node* parent = NULL;

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left == newNode || temp->right == newNode)
            {
                parent = temp;
                break;
            }

            if (temp->left != NULL)
                q.push(temp->left);

            if (temp->right != NULL)
                q.push(temp->right);
        }

        if (parent != NULL && newNode->data > parent->data)
        {
            swap(newNode->data, parent->data);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Node* temp)
    {
        Node* largest = temp;

        if (temp->left != NULL &&
            temp->left->data > largest->data)
            largest = temp->left;

        if (temp->right != NULL &&
            temp->right->data > largest->data)
            largest = temp->right;

        if (largest != temp)
        {
            swap(temp->data, largest->data);
            heapifyDown(largest);
        }
    }

    int deleteRoot()
    {
        int value = root->data;

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return value;
        }

        queue<Node*> q;
        q.push(root);

        Node* last = root;
        Node* parent = NULL;

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();

            if (temp->left != NULL)
            {
                parent = temp;
                last = temp->left;
                q.push(temp->left);
            }

            if (temp->right != NULL)
            {
                parent = temp;
                last = temp->right;
                q.push(temp->right);
            }
        }

        root->data = last->data;

        if (parent->right == last)
            parent->right = NULL;
        else
            parent->left = NULL;

        delete last;

        heapifyDown(root);

        return value;
    }

    void heapSort()
    {
        int sorted[100];
        int count = 0;

        while (root != NULL)
        {
            sorted[count] = deleteRoot();
            count++;
        }

        cout << "Ascending Order: ";

        for (int i = count - 1; i >= 0; i--)
        {
            cout << sorted[i] << " ";
        }
    }
};

int main()
{
    MaxHeap h;

    h.insert(40);
    h.insert(20);
    h.insert(50);
    h.insert(10);
    h.insert(30);

    h.heapSort();

    return 0;
}