#pragma once
#include <string>
#include "LinkedList.cpp"
#include <iostream>


class Stack
{
private:
    Node* Top;
public:
    Stack()
    {
        Top = NULL;
    }
    bool isEmpty()
    {
        return (Top == NULL ? 1 : 0);
    }
    void Push(string Copy_Data)
    {
        Node* newNode = new Node();
        newNode->data = Copy_Data;
        if (isEmpty())
        {
            newNode->Next = NULL;
            Top = newNode;
        }
        else
        {
            newNode->Next = Top;
            Top = newNode;
        }
    }
    void Pop()
    {
        if (isEmpty())
        {
            cout << "You Cannot Pop an EMpty Stack!" << endl;
        }
        else
        {
            Node* delPtr = Top;
          //  cout << "The Popped value = " << Top->data << endl;
            Top = Top->Next;
            delete delPtr;

        }
    }
    void Display()
    {
        Node* Temp = Top;

        if (isEmpty())
        {
            cout << "Stack is Empty..." << endl;
        }
        else
        {
            cout << "The Stack Contains: ";
            while (Temp != NULL)
            {
                cout << Temp->data << " ";
                Temp = Temp->Next;
            }
            cout << endl;
        }
    }
    string Peak()
    {
        if (isEmpty())
        {
           // cout << "You Cannot Peak an EMpty Stack!" << endl;
            return "empty";
        }
        else
        {
            //cout << "The Peaked Value =";
            return Top->data;
        }
    }
    int Count()
    {
        int Count = 0;
        if (isEmpty())
        {
            cout << "The stack is Empty!!";
        }
        else
        {
            Node* Temp = Top;
            while (Temp != NULL)
            {
                Count++;
                Temp = Temp->Next;

            }
            return Count;
        }
    }
    bool isFound(string Copy_Data)
    {
        bool found = false;
        if (isEmpty())
        {
            cout << "You Cannot Search an Empty Stack" << endl;
        }
        else
        {
            Node* Temp = Top;
            while (Temp != NULL)
            {
                if (Temp->data._Equal (Copy_Data))
                {
                    found = true;
                }
                Temp = Temp->Next;
            }
            return found;
        }
    }
};


