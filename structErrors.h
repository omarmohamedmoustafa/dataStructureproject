#pragma once
#include <string>
using namespace std;

struct error {
	string tagName;
	int line;
};

bool include(string s[], int size, string f);
