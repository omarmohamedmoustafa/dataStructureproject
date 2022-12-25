#pragma once
#include <string>
#include "Node.cpp"
#include <iostream>
using namespace std;

class LinkedList
{
public:
    Node* head;
    LinkedList()
    {
        head = NULL;
    }
    bool isempty()
    {
        return (head == NULL);
    }
    void insertfirst(string copy_intnewdata)
    {
        Node* newnode = new Node();
        newnode->data = copy_intnewdata;
        if (isempty())
        {

            newnode->Next = NULL;
            head = newnode;
        }
        else
        {
            newnode->Next = head;
            head = newnode;
        }
    }
    void pop_front()
    {
        if (isempty())
        {
            return;
        }
        Node* delPtr = head;
        head = head->Next;
        delete delPtr;
        delPtr = NULL;
    }
    void pop_back()
    {
        if (isempty())
        {
            return;
        }
        if (head->Next == NULL)
        {
            delete head;
            head = NULL;
            return;
        }
        Node* temp_last = head->Next;
        Node* temp_prealast = head;
        while (temp_last->Next)
        {
            temp_last = temp_last->Next;
            temp_prealast = temp_prealast->Next;
        }
        temp_prealast->Next = NULL;
        delete temp_last;
        temp_last = NULL;

    }

    void display()
    {
        Node* Temp = head;
        while (Temp != NULL)
        {

            cout << Temp->data << ' ';

            Temp = Temp->Next;
        }
        cout << "\n";
    }
    int count()
    {
        int counter = 0;
        Node* Temp = head;
        while (Temp != NULL)
        {
            counter++;
            Temp = Temp->Next;
        }
        return counter;
    }
    bool isFound(string key)
    {
        bool found = false;
        Node* Temp = head;
        while (Temp != NULL)
        {
            if (Temp->data == key)
            {
                found = true;
            }
            Temp = Temp->Next;
        }
        return found;
    }
    void insertBefore(string preceeding, string newData)
    {
        if (isFound(preceeding))
        {
            Node* newNode = new Node();
            newNode->data = newData;
            Node* Temp = head;
            while (Temp != NULL && Temp->Next->data._Equal( preceeding))
            {
                Temp = Temp->Next;
            }
            newNode->Next = Temp->Next;
            Temp->Next = newNode;
        }
        else
        {
            cout << "Item Is not found" << endl;
        }
    }
    void append(string newVal)
    {
        Node* newNode = new Node();
        newNode->data = newVal;
        if (isempty())
        {
            insertfirst(newVal);
        }
        Node* Temp = head;
        while (Temp->Next != NULL)
        {
            Temp = Temp->Next;
        }
        Temp->Next = newNode;
        newNode->Next = NULL;
    }
    void clear()
    {
        if (isempty())return;
        while (!isempty())
        {
            delete head;
            head = NULL;

        }
        cout << "HI" << endl;
    }


};


