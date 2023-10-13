#include "validation.h"
#include "fixing.h"
#include <iostream>

void pushErrors(string tag , int lineNumber, vector<error> &errors ) {
	error E;
	if (tag == "" || tag == "/") {
		E.tagName = "<" + tag + "> is an empty tag";
	}
	else
		E.tagName = "<"+tag+">";
	E.line = lineNumber;
	errors.push_back(E);
}

void validation(ifstream &MyReadFile , vector<error> &errors,  vector<string> &file)
{
	// Read from the text file
	Stack validation;
	int indxOpen, indxClose = 0;
	int lineNumber = 0;
	string myText, pushedTags = "", TagName;
	while (getline(MyReadFile, myText)) 
	{
		file.push_back(myText);
		lineNumber++;
		while (indxClose != -1)
		{
			//catch open or close tags in the line
			indxOpen = myText.find_first_of('<', indxClose);
			indxClose = myText.find_first_of('>', indxOpen);

			if (indxOpen > -1 && indxClose > -1)			//check if a tag is found 
			{
				//Extract the tag name from line
				TagName = myText.substr(indxOpen + 1, (indxClose - indxOpen - 1));
			}
			else if (indxOpen > -1 && indxClose == -1)
			{
				//check if close tag with '<' without '>' 
				indxClose = myText.find_first_of(' ', indxOpen);
				cout << " '>' is missing in line  " << lineNumber << endl;
				//Extract the tag name even if '>' is missing
				TagName = myText.substr(indxOpen + 1, (indxClose - indxOpen));
			}
			else
			{
				// if line has no tag names
				continue;
			}
			//handling an empty tag problem
			if (TagName == "" || TagName == "/")
			{
				pushErrors(TagName, lineNumber - 1, errors);
			}
			else {
				// check if the tag name is open tag	
				if (TagName.find('/') == -1)
				{
					//push the open tag
					if (validation.Peak() != TagName)
					{
						validation.Push(TagName);
						pushedTags += TagName + " ";
					}
					//not to push two same open tags above each other
					else
					{
						pushErrors("/" + TagName, lineNumber - 1, errors);
					}
				}
				// if the tag name is close tag	
				else
				{
					string closeTag = TagName.substr(1, TagName.size() - 1);
					//if same then pop from stack
					if (validation.Peak() == closeTag)
					{
						//cout << "matched: " << closeTag << endl;
						int idx = pushedTags.find(closeTag + " ");
						if (idx != -1)
							pushedTags.erase(idx, closeTag.size());
						validation.Pop();
					}
					else if (validation.isEmpty())
					{
						pushErrors(closeTag, lineNumber, errors);
					}
					//push remaining closed tags in the file
					else
					{
						//open tag not exist in the stack
						if (pushedTags.find(closeTag + " ") == -1)
						{
							pushErrors(closeTag, lineNumber - 1, errors);
						}
						//pop from stack till the correct open tag
						else
						{
							while (validation.Peak() != closeTag && !validation.isEmpty())
							{
								pushErrors("/" + validation.Peak(), lineNumber - 1, errors);
								int idx = pushedTags.find(validation.Peak() + " ");
								if (idx != -1)
									pushedTags.erase(idx, (validation.Peak()).size());
								validation.Pop();
							}
							if (!validation.isEmpty())
								validation.Pop();
						}
					}
				}
			}
		}
		// start from first char in next line
		indxClose = 0;
	}
	// check if stack is empty
	while(!validation.isEmpty())
	{
		// push the error to vector of struct 
		pushErrors("/"+validation.Peak(), lineNumber++, errors);
		validation.Pop();
	}
	//Output the errors
	if (!errors.size())
		cout << "Success!\n";
	else {
		for (int i = 0; i < errors.size(); i++)
		{
			if(errors[i].tagName.find("empty") == -1)
				cout << "Error in line " << errors[i].line + 1 << ": " << errors[i].tagName << " is missing!" << endl;
			else
				cout << "Error in line " << errors[i].line + 1 << ": " << errors[i].tagName << endl;
		}
	}
	// close file
	MyReadFile.close();
}

