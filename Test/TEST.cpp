#include <iostream>

using namespace std;

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};

struct List {
    DNode* head;
    DNode* tail;
};

DNode* createNode(int data)
{
    DNode* newNode = new DNode;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addSorted (List &l, int data)
{
    DNode* newNode = createNode(data);
    if (l.head == NULL || l.head->data > data)
    {
        newNode->next = l.head;
        if (l.head != NULL)
            l.head->prev = newNode;
        l.head = newNode;
    }
    else
    {
        DNode* curNode = l.head;
        while (curNode->next != NULL && curNode->next->data < data)
            curNode = curNode->next;

        if (curNode->next == NULL)
        {
            curNode->next = newNode;
            newNode->prev = l.tail;
            l.tail = newNode;
            return;
        }
        else
        {
            newNode->next = curNode->next;
            curNode->next->prev = newNode;
            newNode->prev = curNode;
            curNode->next = newNode;
        }
        
    }
}

void printLL(List l)
{
    for (DNode* curNode = l.head; curNode != NULL; curNode = curNode->next)
        cout << curNode->data << " <-> ";
}

int main ()
{
    List l;
    l.head = l.tail = NULL;
    addSorted(l, 0);
    addSorted(l, 5);
    addSorted(l, 4);
    addSorted(l, 10);
    addSorted(l, 390);
    addSorted(l, -30);
    printLL(l);
    cout << l.head->data << " " << l.tail->data;
    return 0;
}