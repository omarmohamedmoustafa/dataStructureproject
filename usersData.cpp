#pragma once
#include<string>
#include<vector>
#include <iostream>
#include <sstream>
using namespace std;
class _post
{
private:
	string body;
	vector<string>topics;
public:
	bool isFound(string target)
	{
		if (body.find(target) != -1)
		{
			return true;
		}
		for (int i = 0; i < topics.size(); i++)
		{
			if (topics[i] == target)
			{
				return true;
			}
		}
		return false;
	}
	string getBody()
	{
		return this->body;
	}
	void setBody(string body)
	{
		this->body = body;
	}
	void addTopic(string topic)
	{
		topics.push_back(topic);
	}
	vector<string> getTopics()
	{
		return this->topics;
	}
	void printout()
	{
		cout << "BODY:" <<endl << this->body << endl;
		cout << "TOPICS:" << endl;
		for (int i = 0; i < topics.size(); i++)
		{
			cout << "\t" << "TOPIC:" << topics[i] << endl;
		}
	}
	string topicsJson()
	{
		std::ostringstream json;
		json << "\"topic\""<<":";
		if (topics.size() > 1)
		{
			json << "[" << endl;
			for(int i=0 ; i<topics.size();i++)
			{
				if(i != topics.size()-1)
					json << "\"" << topics[i] << "\"" << ",\n";
				else
					json << "\"" << topics[i] << "\"" << "\n";
			}
			json << "]\n";
		}
		else
			json << "\"" << topics[0] << "\"" << "\n";
		
		return json.str();
	}

	string json()
	{
		std::ostringstream json;
		json << "{\n";
		json << "\"body\"" <<":" << "\"" << this->getBody() << "\"" << "," << endl;
		json << "\"topics\"" << ":" << "{" << endl;
		json << topicsJson();
		json << "}\n";
		json << "}\n";

		return json.str();
	}
};
class _user
{
private:
	int id;
	string name;
	vector<int>followers;
public:
	vector<_post> posts;
	void setPost(_post post)
	{
		this->posts.push_back(post);
	}
	void setFollower(int id)
	{
		this->followers.push_back(id);
	}

	void setName(string name)
	{
		this->name = name;
	}
	void setId(int id)
	{
		this->id = id;
	}
	int getId()
	{
		return this->id;
	}
	string getName()
	{
		return this->name;
	}
	int getNumFollowers()
	{
		return this->followers.size();
	}
	vector<int> getFollowers()
	{
		return this->followers;
	}
	string print()
	{
		ostringstream m_user;
		m_user << "NAME: " << this->getName()<<endl;
		m_user << "ID: " << this->getId()<< endl;
		return m_user.str();
	}
};
