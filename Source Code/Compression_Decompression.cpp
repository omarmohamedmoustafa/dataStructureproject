#include"Compression_Decompression.h"
string fileAsString;
priority_queue<node*, vector<node*>, compare> minHeap;
void Replace(node* root, string oldChars[], string newCode)
{
    /*in order*/
    if (root == NULL)
        return;
    else if (root->left == NULL && root->right == NULL)//leaf
        oldChars[root->character] = newCode;
    Replace(root->left, oldChars, newCode + "0");
    Replace(root->right, oldChars, newCode + "1");
}
string ReadFromFile(string path)
{
    fileAsString="";
    ifstream OriginalFile(path);
    string fileLine;
    while (getline(OriginalFile, fileLine)) {
        fileAsString += fileLine;
        fileAsString += '\n';
    }
    OriginalFile.close();
    return fileAsString;
}
string Encode(string s)
{
    int  freqArr[256] = { 0 };
    string oldChars[256];
    string encoded;
    /* filling the frequency array in correspondance to each character*/
    for (int i = 0; i < s.length(); i++)
    {
        freqArr[s[i]]++;
    }
    /*MIN HEAP (INVERSED MAX QUEUE)*/
    for (int i = 0; i < 256; i++)
    {
        if (freqArr[i])
            minHeap.push(new node(char(i), freqArr[i]));
    }
    /*creating tree structure from the heap in order*/
    node* left, * right, * top;
    while (minHeap.size() != 1)
    {
        // Extract the two minimum freq items from queue
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        /*creating a top node with a distinct character from my file chars to be distinguishable*/
        top = new node('|', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        /*re-pushing top to be taken into consideration within next itteration*/
        minHeap.push(top);
    }
    /*replacing the chars with binary representations*/
    Replace(minHeap.top(), oldChars, "");
    /*fill encoded with bin representation of my file*/
    for (int i = 0; i < s.length(); i++) {
        encoded.append(oldChars[s[i]]);
    }
    cout << "Original file size = " << fileAsString.size() * 8<<endl;
    cout << "Compressed file size = " << encoded.size()<<endl;
    cout << encoded << endl;
    return encoded;
}
void Decode(string s)
{
    ofstream lastOut("last.txt");
    node* root = minHeap.top();
    string decompressed;
    node* temp = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;
        //at reaching leaf-->now i got the character:)
        if (temp->left == NULL && temp->right == NULL) {
            decompressed += temp->character;
            temp = root;
        }
    }
    for (int i = 0; i < decompressed.size(); i++)
    {
        lastOut << decompressed[i];
    }
    lastOut.close();
    while (minHeap.size())
    {
        minHeap.pop();
    }
    cout << "Original file has been recreated sucessfully" << endl;
}
