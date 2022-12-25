#include "validation.h"
#include "fixing.h"
string branchTags[] = { "id","name","topic","body" };
bool include(string s[], int size, string f)
{
	for (int i = 0; i < size; i++)
	{
		if (f._Equal(s[i]))
			return true;
	}
	return false;
}

int convert(string s)
{
	if (s == "users")
		return 2;
	else if (s == "user")
		return 3;
	else if (s == "posts")
		return 4;
	else if (s == "followers")
		return 4;
	else if (s == "post")
		return 5;
	else if (s == "follower")
		return 5;
	else if (s == "topics")
		return 6;
	else if (include(branchTags, 4, s))
		return 7;
	else
		return -1;
}

void pushErrors(string tag , int lineNumber, vector<error> &errors ) {
	error E;
	E.tagName = "</"+tag+">";
	if (tag == "id" || tag == "name")
		E.line = lineNumber-1;
	else
		E.line = lineNumber;
	errors.push_back(E);
}

void validation(ifstream &MyReadFile , vector<error> &errors,  vector<string> &file)
{
	// Read from the text file
	Stack validation;
	int indxOpen, indxClose = 0;
	bool x = false;
	int lineNumber = 0;
	string myText;
	int count = 0;
	while (getline(MyReadFile, myText)) 
	{

		file.push_back(myText);
		//cout << myText<<endl;
		while (indxClose != -1)
		{
			//catch open or close tags in the line
			indxOpen = myText.find_first_of('<', indxClose);
			indxClose = myText.find_first_of('>', indxOpen);


			string TagName;

			if (indxOpen > -1 && indxClose > -1)			//check if found 
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

			// check if the tag name is close tag	
			if (TagName.find('/') != -1)
			{
				
				if (convert(TagName.substr(1, (TagName.size() - 1))) == -1)
				{
					//delete wrong tag name
					int index1 = myText.find_last_of('<');
					int index2 = myText.find_last_of('>');
					pushErrors(validation.Peak(), lineNumber+1, errors);
					validation.Pop();
					myText.erase(index1, (index2 - index1)+1);
					file.pop_back();
					file.push_back(myText);
				}
				else
				{
					// main case : close tag matches last open tag pushed
					if (validation.Peak() == TagName.substr(1, (TagName.size() - 1)) && !validation.isEmpty())
					{
						validation.Pop();
					}

					// in case close tag doesn't match last open tag pushed
					else
					{	
						// push the error to vector of struct 
						pushErrors(validation.Peak(), lineNumber, errors);

						validation.Pop();
						string CompareName = TagName.substr(1, TagName.size() - 1);
						// check if : after pop the missing open tag if the tag name in the line matches the last tag in stack
						while (CompareName.compare(validation.Peak())!=0 && !validation.isEmpty())
						{
							pushErrors(validation.Peak(), lineNumber, errors);
							validation.Pop();
						}
						if (CompareName.compare(validation.Peak()) == 0 && !validation.isEmpty())
						{
							validation.Pop();
						}
					}

				}
				
			}


			// if the tag name is open tag	
			else
			{
				while (convert(TagName) <= convert(validation.Peak()) && !validation.isEmpty() && convert(TagName)!=-1)
				{
					// push the error to vector of struct 
					pushErrors(validation.Peak(), lineNumber, errors);
					validation.Pop();
				}
				

				//push the open tag
				validation.Push(TagName);
			}

		}

		// start from first char in next line
		indxClose = 0;
		lineNumber++;
	}
	//validation.Display();

	// check if stack is empty
	while(!validation.isEmpty())
	{
		// push the error to vector of struct 
		pushErrors(validation.Peak(), lineNumber, errors);
		validation.Pop();
	}

	for (int i = 0; i < errors.size(); i++)
	{
		cout << "Error in line " << errors[i].line+1 << ": " << errors[i].tagName << " is missing!" << endl;
	}

	// close file
	MyReadFile.close();
}

