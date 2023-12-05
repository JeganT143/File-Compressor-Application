#include<iostream>

using namespace std;

class Node
{
    public:
    char data ;
    unsigned int frequency;
    Node* left;
    Node* right;

    Node(char d = 0 ,int f = 0)
    {
        data = d;
        frequency = f;
        left = NULL;
        right = NULL;
    }

};

class minHeap
{
    public:
    Node* Arr;
    int capacity;
    int currentSize;

    minHeap(int c)
    {
        capacity = c;
        currentSize = 0;
        Arr = new Node[capacity];
    }

    int ind_parent(int i)
    {
        return (i-1)/2;
    }

    int ind_left(int i)
    {
        return (2*i +1);
    }

    int ind_right(int i)
    {
        return (2*i + 2);
    }

   void insertNode(Node node) {
    if (currentSize == capacity) {
        cout << "Heap is full" << endl;
        return;
    }

    int i = currentSize;
    Arr[i] = node;
    currentSize++;

    while (i > 0 && Arr[i].frequency < Arr[ind_parent(i)].frequency) {
        // Swap the node with its parent until it satisfies the min heap property
        Node temp = Arr[i];
        Arr[i] = Arr[ind_parent(i)];
        Arr[ind_parent(i)] = temp;
        i = ind_parent(i);
    }
}




  Node removeNode() {
    if (currentSize == 0) {
        // Heap is empty
        Node nullNode('\0', 0); // Return a default node or handle differently
        return nullNode;
    }

    Node removed = Arr[0];
    Arr[0] = Arr[currentSize - 1];
    currentSize--;

    int i = 0;
    int j = ind_left(i);
    while (j < currentSize) {
        // Check if right child exists and has a lower frequency
        if (j + 1 < currentSize && Arr[j].frequency > Arr[j + 1].frequency) {
            j = j + 1;
        }

        // Compare parent with the selected child
        if (Arr[i].frequency > Arr[j].frequency) {
            Node temp = Arr[i];
            Arr[i] = Arr[j];
            Arr[j] = temp;
            i = j;
            j = ind_left(j);
        } else {
            break;
        }
    }

    return removed;
}

};