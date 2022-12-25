#include "fixing.h"
#include <stack>
string GetTagName(string line)
{
	int indxOpen, indxClose = 0;
	indxOpen = line.find_first_of('<', indxClose);
	indxClose = line.find_first_of('>', indxOpen);
	string Tagname = line.substr(indxOpen + 1, (indxClose - indxOpen - 1));
	return Tagname;
}
void fixing(vector <string> &file, vector <error> &errors , string path) 
{
	stack <string> temp;
	ofstream mynew(path);
	string arr[] = {"</id>", "</name>"};
	int i = 0;
	for (i = errors.size() - 1; i >= 0; i--) {
		if (errors[i].line <= file.size() - 1)
		{
			if (include(arr, 2, errors[i].tagName))
				file[errors[i].line] = file[errors[i].line] + errors[i].tagName;
			else
			{
					file.insert(file.begin()+errors[i].line, errors[i].tagName);
			}
		}
		else
		{
			temp.push(errors[i].tagName);
		}
	}
	while(temp.size())
	{
		file.push_back(temp.top());
		temp.pop();
	}

	mynew.clear();
	string s;
	for (int i = 0; i < file.size(); i++) 
	{
		mynew << file[i] << endl;
	}

	mynew.close();

}
