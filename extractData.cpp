#include"extractData.h"
#include <cassert>
using namespace std;
vector<pair<int, _post>> allPosts;
map<int, int> followers;
//==========================EXTRA-HELPERS==========================//
string minify(string path)
{
	vector <string> file;
	ifstream MyReadFile(path);
	string myText;
	string compData;
	while (getline(MyReadFile, myText))
	{
		file.push_back(myText);
	}
	string whitespace = " \n\r\t\f\v";
	for (int i = 0; i < file.size(); i++)
	{
		int x = file[i].find_first_not_of(whitespace);
		file[i].erase(0, x);
		compData += file[i];
	}
	return compData;
}
string getTagData(int& i, string compData)
{
	int firstOfCloseTag = 0;
	firstOfCloseTag = compData.find_first_of("</", i);
	string tagData = compData.substr(i + 1, (firstOfCloseTag - i - 1));
	i = compData.find_first_of('>', firstOfCloseTag);
	return tagData;
}
vector<_user> getData(string compData)
{
	//allPosts.clear();
	bool userId = false;
	int usersCount = 0;
	int postsCount = 0;
	vector<_user> users;
	int sz = compData.size();
	int i;
	int startIndex, endIndex = 0;
	for (i = 0; i < sz;)
	{
		startIndex = compData.find_first_of('<', i);
		endIndex = compData.find_first_of('>', startIndex);
		string tagName = compData.substr(startIndex + 1, (endIndex - startIndex - 1));
		if (endIndex != -1)i = endIndex;
		if (tagName == "/users")
			break;
		else if (tagName == "/user")
		{
			postsCount = 0;
			userId = false;
		}
		else if (tagName == "user")
		{
			usersCount++;
			_user u;
			users.push_back(u);
		}
		else if (tagName == "id")
		{
			if (!userId)
			{
				users[usersCount - 1].setId(stoi(getTagData(i, compData)));
				userId = true;
			}
			else
			{
				int followerId = stoi(getTagData(i, compData));
				followers[followerId]++;
				users[usersCount - 1].setFollower(followerId);
			}
		}
		else if (tagName == "name")
		{
			users[usersCount - 1].setName(getTagData(i, compData));
		}
		else if (tagName == "post")
		{
			postsCount++;
			_post p;
			users[usersCount - 1].setPost(p);
			
		}
		else if (tagName == "/post")
		{
			pair<int, _post> my_pair;
			my_pair.first = users[usersCount - 1].getId();
			my_pair.second = users[usersCount - 1].posts[postsCount - 1];
			allPosts.push_back(my_pair);
			//allPosts.push_back(users[usersCount - 1].posts[postsCount-1]);
		}
		else if (tagName == "body")
		{
			users[usersCount - 1].posts[postsCount - 1].setBody(getTagData(i, compData));
		}
		else if (tagName == "topic")
		{
			users[usersCount - 1].posts[postsCount - 1].addTopic(getTagData(i, compData));
		}
	}
	return users;
}
