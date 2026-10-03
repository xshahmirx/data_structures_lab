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
    // Create 5 song nodes
    Node* first = new Node();
    Node* second = new Node();
    Node* third = new Node();
    Node* fourth = new Node();
    Node* fifth = new Node();

    // Store song names
    first->data = "Song 1";
    second->data = "Song 2";
    third->data = "Song 3";
    fourth->data = "Song 4";
    fifth->data = "Song 5";

    // Connect nodes
    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = first;

    // Display all songs once
    cout << "Music Playlist:" << endl;

    Node* current = first;

    do
    {
        cout << current->data << endl;
        current = current->next;
    }
    while (current != first);

    // Play playlist for 2 complete rounds
    cout << "\nPlaying Playlist for 2 Complete Rounds:" << endl;

    current = first;

    for (int round = 1; round <= 2; round++)
    {
        cout << "\nRound " << round << ":" << endl;

        do
        {
            cout << current->data << endl;
            current = current->next;
        }
        while (current != first);
    }

    return 0;
}