#pragma once
#include <string>
#include <queue>
#include <fstream>
#include<map>
#include "userData.cpp"
#include<algorithm>
using namespace std;
string minify(string path);
string getTagData(int& i, string compData);
vector<_user> getData(string compData);
_user m_Influencer(vector<_user> users);
_user m_Active(vector<_user> users);
vector<_user> mutualFollower(vector<_user> users, int id1, int id2);
vector<_user> suggestions(vector<_user> users, int id);
vector<pair<int, _post>> searchInPosts(string target);
string JSON(vector<_user> users);
