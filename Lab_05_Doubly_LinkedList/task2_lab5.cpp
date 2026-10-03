#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string data;
    Node* prev;
    Node* next;
};

int main()
{
    // Create 5 nodes
    Node* first = new Node();
    Node* second = new Node();
    Node* third = new Node();
    Node* fourth = new Node();
    Node* fifth = new Node();

    // Store image names
    first->data = "Image1.jpg";
    second->data = "Image2.jpg";
    third->data = "Image3.jpg";
    fourth->data = "Image4.jpg";
    fifth->data = "Image5.jpg";

    // Connect nodes
    first->prev = NULL;
    first->next = second;

    second->prev = first;
    second->next = third;

    third->prev = second;
    third->next = fourth;

    fourth->prev = third;
    fourth->next = fifth;

    fifth->prev = fourth;
    fifth->next = NULL;

    // Forward traversal
    cout << "Images from First to Last:" << endl;

    Node* current = first;

    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }

    // Backward traversal
    cout << "\nImages from Last to First:" << endl;

    current = fifth;

    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->prev;
    }

    return 0;
}