#include <fstream>
#include <string>
#include <stack>
#include <iostream>

using namespace std;


stack<char>brack;
stack<string> tags;
stack<int> lvls;
bool written = true;
string returnObrackets(string tag)
{
	if (tag[0] != '/')		//open
	{
		if (tag[tag.length() - 1] == 's') {
			brack.push(']');
			return "[";
		}
		else if (tag + "s" == tags.top())
		{
			brack.push('}');
			return "{";
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}
}



void Json(string path, string JsonPath)
{
	ifstream MyReadFile(path);
	string myText;
	string tag;
	ofstream Json(JsonPath);
	Json.clear();
	int indxOpen = 0, indxClose = 0, lvl = 0;
	string lastT;
	int lastL = 0;
	bool any = false;


	while (getline(MyReadFile, myText))
	{
		indxOpen = indxClose = 0;
		bool twoTags = false;
		string tabs;
		for (int i = 0; i < myText.length(); i++)
		{
			if (myText[i] < 60)
				tabs += ' ';
			else
				break;
		}
		lvl = tabs.length() / 4;

		indxOpen = myText.find_first_of('<');
		indxClose = myText.find_first_of('>');

		if (myText.find_last_of('<') != indxOpen)
		{
			twoTags = true;
		}
		if (indxOpen > -1 && indxClose > -1)
		{
			tag = myText.substr(indxOpen + 1, (indxClose - indxOpen) - 1);

			//cout << tag<<endl;
		}
		else							//not tag
		{
			string line = myText.substr(tabs.length(), myText.length());
			cout << endl << tabs << line;
			continue;
		}


		if (tag.find('/') == -1)		//open tag
		{
			if (!tags.empty())
			{
				if (!any)
				{
					lastL = lvls.top();
					lastT = tags.top();
				}

				if (lvl > lastL || tag != lastT)
				{
					written = true;
					cout << endl << tabs << "\"" << tag << "\"" << ":";							//1
					cout << returnObrackets(tag);
					tags.push(tag);
					lvls.push(lvl);
				}
				else
				{
					written = false;
					returnObrackets(tag);
					tags.push(tag);
					lvls.push(lvl);
				}
			}
			else
			{
				written = true;
				cout << endl << tabs << "\"" << tag << "\"" << ":";						//3
				cout << returnObrackets(tag);
				tags.push(tag);
				lvls.push(lvl);
			}
			if (twoTags)
			{
				string line = myText.substr(myText.find_first_of('>') + 1, myText.find_last_of('<') - myText.find_first_of('>') - 1);
				cout << "\"" << line << "\"" << " ";
				any = true;
				lastT = tags.top();
				tags.pop();
				lastL = lvls.top();
				lvls.pop();
			}
		}


		else if (tag.find('/') != -1)						//closeTag
		{
			any = true;
			lastT = tags.top();
			lastL = lvls.top();
			if (lastT == tag.substr(1, tag.length() - 1))
			{
				tags.pop();
				lvls.pop();
			}
		}

	}
}