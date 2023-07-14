#include <iostream>

using namespace std;

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};

struct DLL {
    DNode* pHead;
    DNode* pTail;
};

DNode* createNode (int data)
{
    DNode* newNode = new DNode;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addHead (int data, DLL &l)
{
    DNode* newNode = createNode(data);
    if (l.pHead == NULL) {
        l.pHead = l.pTail = newNode;
        return;
    }

    newNode->next = l.pHead;
    l.pHead->prev = newNode;
    l.pHead = newNode;
}

void addTail (int data, DLL &l)
{
    DNode* newNode = createNode (data);
    if (l.pHead == NULL) {
        l.pHead = l.pTail = newNode;
        return;
    }

    l.pTail->next = newNode;
    newNode->prev = l.pTail;
    l.pTail = newNode;
}

void printDLL (DLL l)
{
    for (DNode* curNode = l.pHead; curNode != NULL; curNode = curNode->next)
        cout << curNode->data << " <-> ";
    cout << endl;
}

void removeHead (DLL &l)
{
    if (l.pHead == NULL)
        return;

    else if (l.pHead->next == NULL)
    {
        delete l.pHead;
        l.pHead = NULL;
        return;
    }

    DNode* temp = l.pHead;
    l.pHead = l.pHead->next;
    delete temp;
}

void removeTail (DLL &l)
{
    if (l.pTail == NULL)
        return;

    DNode* temp = l.pTail;
    l.pTail = l.pTail->prev;
    l.pTail->next = NULL;
    delete temp;
}

void removeAll (DLL &l)
{
    while (l.pHead != NULL)
        removeHead (l);
}

void addBefore (DLL &l, int data, int val)
{
    DNode* newNode = createNode(data);
    if (l.pHead->data == val) {
        addHead (data, l);
        return;
    }
    
    else
    {
        DNode* curNode = l.pHead;
        while (curNode->next->data != val)
        {
            curNode = curNode->next;
        }

        newNode->next = curNode->next;
        curNode->next->prev = newNode;
        curNode->next = newNode;
        newNode->prev = curNode;
    }
}

void addAfter (DLL &l, int data, int val)
{
    DNode* newNode = createNode(data);

    DNode* curNode = l.pHead;
    while (curNode->data != val)
    {
        curNode = curNode->next;
    }

    if (curNode->next == NULL)
    {
        addTail(data, l);
        return;
    }

    newNode->next = curNode->next;
    curNode->next->prev = newNode;
    curNode->next = newNode;
    newNode->prev = curNode;
}

void removeBefore (int val, DLL &l)
{
    if (l.pHead->next->data == val)
    {   
        removeHead(l);
        return;
    }
    
    else
    {
        DNode* curNode = l.pHead;
        while (curNode->next->next->data != val)
            curNode = curNode->next;

        DNode* temp = curNode->next;
        curNode->next = temp->next;
        temp->next->prev = curNode;
        delete temp;
    }
}

void removeAfter (int val, DLL &l)
{
    DNode* curNode = l.pHead;
    while (curNode->data != val)
        curNode = curNode->next;
    
    if (curNode->next->next == NULL)
    {
        removeTail(l);
        return;
    }

    DNode* temp = curNode->next;
    curNode->next = temp->next;
    temp->next->prev = curNode;
    delete temp;
}

int main ()
{
    DLL l;
    l.pHead = l.pTail = NULL;
    int n;
    n = 5;
    for (int i = 0; i < n; ++i)
    {
        addHead(i, l);
    }
    printDLL(l);
    addBefore(l, 5, 4);
    printDLL(l);
    addAfter(l, 6, 0);
    printDLL(l);
    removeBefore(4, l);
    printDLL(l);
    removeAfter(0, l);
    printDLL(l);
    removeAll (l);
    return 0;
}