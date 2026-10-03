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
    Node* first = new Node();
    Node* second = new Node();
    Node* third = new Node();
    Node* fourth = new Node();
    Node* fifth = new Node();

    first->data = "Google";
    second->data = "YouTube";
    third->data = "GitHub";
    fourth->data = "LinkedIn";
    fifth->data = "Air University";
    
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


    cout << "Browser History (First to Last):" << endl;

    Node* current = first;

    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }
    cout << "\nBrowser History (Last to First):" << endl;

    current = fifth;

    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->prev;
    }

    return 0;
}