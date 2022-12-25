#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// no. tabs to ba added
int counter = -1;
// case to handle
int TagCase;

// add no. tabs string = counter 
string addTab()
{
	string tabs = "";
	for (int i = 0; i < counter; i++)
	{
		tabs += "\t";
	}
	return tabs;
}
void singleTabCaseDefine(string line, int indexOpen)
{
	if (line[indexOpen + 1] == '/')
	{
		TagCase = 3;
	}
	else
	{
		TagCase = 1;
	}
}

//check if line has tags or not
void tagDefine(string line)
{
	int firstOpen = line.find_first_of('<');
	int lastOpen = line.find_last_of('<');

	//line has tags(tag)
	if (firstOpen != -1 && lastOpen != -1)
	{
		//line has only one tag
		if (firstOpen == lastOpen)
		{
			singleTabCaseDefine(line, firstOpen);
			return;
		}
		//line has more than one tag(two tags)
		else
		{
			TagCase = 2;
		}
	}
	//line with no tags
	else
	{
		TagCase = 0;
		return;
	}

}

void prettify(string path , vector <string> &file)
{
	//vector <string> prettified;
	for (int i = 0; i < file.size(); i++)
	{
		tagDefine(file[i]);
		switch (TagCase)
		{
			//line has one tag(open)
			case 1:
			{
				//add tab -> push
				counter++;
				file[i]=addTab() + file[i];
				break;
			}
			//line has two tags (open & close)
			case 2:
			//line has no tags
			case 0:
			{
				//add tab -> push -> delete tab
				counter++;
				file[i] = addTab() + file[i];
				counter--;
				break;
			}
			//line has one tag(close)
			case 3:
			{
				//push -> delete tap
				file[i] = addTab() + file[i];
				counter--;
				break;
			}
		}
	}

	//clear the file and rewrite the new prettified version
	ofstream pretified(path);
	pretified.clear();
	for (int i = 0; i < file.size(); i++)
	{
		pretified << file[i] << endl;
	}
	pretified.close();

}
