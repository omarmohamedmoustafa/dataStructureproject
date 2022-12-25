#pragma once
#include <iostream>
#include "Stack.cpp"
#include <string>
#include <fstream>
#include <vector>
#include "structErrors.h"
using namespace std;



bool include(string s[], int size, string f);
int convert(string s);
void pushErrors(string tag, int lineNumber, vector<error>& errors);
void validation(ifstream &MyReadFile , vector<error> &errors, vector<string> &lines);
