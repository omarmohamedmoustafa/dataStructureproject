#include "fixing.h"
#include"prettify.h"
#include <stack>
string GetTagName(string line)
{
	int indxOpen, indxClose = 0;
	indxOpen = line.find_first_of('<', indxClose);
	indxClose = line.find_first_of('>', indxOpen);
	if (line.find("<>") != -1 || line.find("</>") != -1)
	{
		string Tagname = line.substr(indxOpen, (indxClose - indxOpen + 1));
		return Tagname;
	}
	if (line[indxOpen + 1] == '/')
		indxOpen++;
	string Tagname = line.substr(indxOpen + 1, (indxClose - indxOpen - 1));
	return Tagname;
}
void fixing(vector <string> &file, vector <error> &errors , string path) 
{
	string originalTagName;
	stack <string> temp;
	ofstream mynew(path);
	int i = 0;
	for (i = errors.size() - 1; i >= 0; i--) {
		if (errors[i].line <= file.size() - 1)
		{
			//get TagName from error
			originalTagName = GetTagName(errors[i].tagName);
			if (originalTagName == "<>" || originalTagName == "</>")
			{
				int idx = file[errors[i].line].find(originalTagName);
				file[errors[i].line].erase(idx, originalTagName.size());
			}
			else
			{
				int idx = file[errors[i].line].find(originalTagName + ">");
				//both tags in same line but original tag isnot the first tag
				if (idx != -1 && GetTagName(file[errors[i].line]) != originalTagName)
				{
						//open tag is missed
						if (errors[i].tagName.find('/') == -1) {
							while (file[errors[i].line][idx - 1] != '>' && idx > 1)
								idx--;
						}
						//close tag is missed
						else
						{
							idx++;
							while (file[errors[i].line][idx] != '<' && idx < file[errors[i].line].size() - 1)
								idx++;
						}
						file[errors[i].line].insert(idx, errors[i].tagName);
				}
				else
				{
					file[errors[i].line] = errors[i].tagName + file[errors[i].line];
				}
			}
		}
		else
		{
			temp.push(errors[i].tagName);
		}
	}
	while (temp.size())
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