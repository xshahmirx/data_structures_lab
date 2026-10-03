#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string data;
    Node* next;
};

int main()
{
    // Create 5 player nodes
    Node* first = new Node();
    Node* second = new Node();
    Node* third = new Node();
    Node* fourth = new Node();
    Node* fifth = new Node();

    // Store player names
    first->data = "Player 1";
    second->data = "Player 2";
    third->data = "Player 3";
    fourth->data = "Player 4";
    fifth->data = "Player 5";

    // Connect nodes
    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = first;

    // Display each player's turn once
    cout << "Player Turns:" << endl;

    Node* current = first;

    do
    {
        cout << current->data << endl;
        current = current->next;
    }
    while (current != first);

    // Show that turn returns to first player
    cout << "\nAfter Player 5, turn returns to: "
         << current->data << endl;

    return 0;
}