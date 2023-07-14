#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
};

struct DLL {
    DNode* phead;
    DNode* ptail;
};

DNode* createNode (int data)
{
    DNode* newNode = new DNode;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void addHead (DLL &l, int data)
{
    DNode* newNode = createNode (data);

    if (l.phead == NULL) {
        l.phead = l.ptail = newNode;
        return;
    }

    newNode->next = l.phead;
    l.phead->prev = newNode;
    l.phead = newNode;
}

void addTail (DLL &l, int data)
{
    DNode* newNode = createNode (data);

    if (l.phead == NULL) {
        l.phead = l.ptail = newNode;
        return;
    }

    l.ptail->next = newNode;
    newNode->prev = l.ptail;
    l.ptail = newNode;
}

void printDLL (DLL l)
{
    for (DNode* curNode = l.phead; curNode != NULL; curNode = curNode->next)
    {
        cout << curNode->data << " <-> ";
    }
    cout << endl;
}

void removeHead (DLL &l)
{
    if (l.phead == NULL)
        return;

    else if (l.phead->next == NULL)
    {
        delete l.phead;
        l.phead = l.ptail = NULL;
    }

    else
    {
        DNode* removeNode = l.phead;
        l.phead = l.phead->next;
        l.phead->prev = NULL;
        delete removeNode;
    }
}

void removeAll (DLL &l)
{
    while (l.phead != NULL)
    {
        removeHead(l);
    }
}

DLL mergeLL (DLL l1, DLL l2)
{
    DLL result;
    result.phead = result.ptail = NULL;

    DNode* temp = NULL;
    while (l1.phead != NULL && l2.phead != NULL)
    {
        if (l1.phead->data > l2.phead->data)
        {
            temp = l1.phead;
            l1.phead = l1.phead->next;
            addHead(result, temp->data);
        }
        else
        {
            temp = l2.phead;
            l2.phead = l2.phead->next;
            addHead(result, temp->data);
        }
    }
    while (l1.phead != NULL)
    {
        temp = l1.phead;
        l1.phead = l1.phead->next;
        addHead(result, temp->data);
    }
    while (l2.phead != NULL)
    {
        temp = l2.phead;
        l2.phead = l2.phead->next;
        addHead(result, temp->data);
    }
    return result;
}

void swap (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort (DLL &list)
{
    int swapped = 0;
    DNode* curNode = NULL;
    DNode* nextNode = NULL;

    if (list.phead == NULL)
        return;
    
    do
    {
        curNode = list.phead;
        swapped = 0;

        while (curNode->next != nextNode)
        {
            if (curNode->data < curNode->next->data)
            {
                swap (curNode->data, curNode->next->data);
                swapped = 1;
            }
            curNode = curNode->next;
        }
        nextNode = curNode;
    } 
    while (swapped == 1);
}

int main () {
    srand(time(NULL));
    int n1, n2;
    DLL list1, list2, merge;
    list1.phead = list1.ptail = NULL;
    list2.phead = list2.ptail = NULL;

    cin >> n1;
    for (int i = 0; i < n1; ++i)
        //addHead(list1, 2*i);
        addHead(list1, rand() % 10);
    
    cin >> n2;
    for (int i = 0; i < n2; ++i)
        //addHead(list2, 2*i+1);
        addHead(list2, rand() % 10);

    printDLL(list1);
    printDLL (list2);
    cout << "----After sort---" << endl;
    bubbleSort(list1);
    bubbleSort(list2);
    printDLL(list1);
    printDLL (list2);
    cout << "---After merge---" << endl;
    merge = mergeLL(list1, list2);
    printDLL (merge);
    cout << merge.phead->data << " " << merge.ptail->data;
    removeAll(list1);
    removeAll (list2);
    removeAll (merge);
    return 0;
}