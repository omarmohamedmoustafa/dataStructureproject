#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
using namespace std;
class node
{
public:
    char character;
    long long frequency;
    node* left;
    node* right;
    node(char character, long long frequency)
    {
        right = left = NULL;
        this->character = character;
        this->frequency = frequency;
    }
};
class compare
{
public:
    bool operator()(node* left, node* right)
    {
        return (left->frequency > right->frequency);
    }
};
string fileAsString;
priority_queue<node*, vector<node*>, compare> minHeap;
void   addToHashTable(node* root, string oldChars[], string newCode);
string ReadFromFile(string path);
string Encode(string s);
string Decode(string s);
