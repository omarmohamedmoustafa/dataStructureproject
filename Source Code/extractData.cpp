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
_user m_Influencer(vector<_user> users)
{
	
	//assert(users.size() != 0);

	_user user = users[0];
	int max = 0;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getNumFollowers() > max)
		{
			max = users[i].getNumFollowers();
			user = users[i];
		}
	}
	return user;
}
_user m_Active(vector<_user> users)
{
	int maxFollowing = 0;
	int userId=0;

	for (auto follower : followers)    
	{ 
		if (follower.second > maxFollowing)
		{
			userId = follower.first;
			maxFollowing = follower.second;
		}	
	}
	int i = 0;
	for (i = 0; i < users.size(); i++)
	{
		if (users[i].getId() == userId)
			break;
	}
	return users[i];
}
vector<_user> mutualFollower(vector<_user> users,int id1 , int id2)
{
	map<int, int> mutual;
	_user u1,u2;

	vector <int> mutualIDs;
	vector<_user> result;

	//find user 1 & 2 with gived ids
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getId() == id1)
			u1 = users[i];
		else if (users[i].getId() == id2)
			u2 = users[i];
	}

	vector <int> followers1 = u1.getFollowers();
	vector <int> followers2 = u2.getFollowers();
	//freq array for user1 followers
	for (int i = 0; i < followers1.size(); i++)
	{
		mutual[followers1[i]]++;
	}

	//get mutual followers ids
	for (int i = 0; i < followers2.size(); i++)
	{
		if (mutual[followers2[i]] > 0)
		{
			mutualIDs.push_back(followers2[i]);
		}
	}
	sort(mutualIDs.begin(), mutualIDs.end());

	//get users with ids in mutual_ids vector
	for (int i = 0; i < users.size(); i++)
	{
		if (binary_search(mutualIDs.begin(), mutualIDs.end(), users[i].getId()))
		{
			result.push_back(users[i]);
		}
	}

	return result;
}
vector<_user> suggestions(vector<_user> users, int id)
{
	_user u1;
	//get the followers of the target user
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getId() == id)
		{
			u1 = users[i];
			break;
		}
	}
	vector <int>  followers_u1 = u1.getFollowers();
	sort(followers_u1.begin(), followers_u1.end());
	vector <int>  suggestIds;
	vector<_user> followersAsU;
	
	//push all followers into vector (as user not id)
	for (int i = 0; i < users.size(); i++)
	{
		if (binary_search(followers_u1.begin(), followers_u1.end(), users[i].getId()))
		{
			followersAsU.push_back(users[i]);
		}
	}

	//add followers of followers ids int vector
	for (int i = 0; i < followersAsU.size(); i++)
	{
		vector<int> temp = followersAsU[i].getFollowers();
		suggestIds.insert(suggestIds.end(), temp.begin(), temp.end());
	}

	//users ids want to suggest to the target
	vector<int>result;
	sort(suggestIds.begin(), suggestIds.end());

	//check if user already have this in its followers 
	for (int i = 0; i < suggestIds.size(); i++)
	{
		if (i + 1 == suggestIds.size())
		{
			//for last elment in the array
			if (!binary_search(followers_u1.begin(), followers_u1.end(), suggestIds[i]) && suggestIds[i]!=id)
			{
				result.push_back(suggestIds[i]);
			}
		}
		else if (suggestIds[i] != suggestIds[i+1] && suggestIds[i]!=id)
		{
			if(!binary_search(followers_u1.begin(), followers_u1.end(), suggestIds[i]))
			{
				result.push_back(suggestIds[i]);
			}
		}
	}

	//get the users of this ids
	vector<_user>finalResult;
	for (int i = 0; i < users.size(); i++)
	{
		if (binary_search(result.begin(), result.end(), users[i].getId()))
		{
			finalResult.push_back(users[i]);
		}
	}
	
	return finalResult;
}
vector<pair<int, _post>> searchInPosts(string target)
{
	vector<pair<int, _post>> result;
	for (int i = 0; i < allPosts.size(); i++)
	{
		if (allPosts[i].second.isFound(target))
		{
			result.push_back(allPosts[i]);
		}
	}
	return result;
}
