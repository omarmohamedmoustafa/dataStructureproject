#include"Minify.h"
void Minify(string path, vector<string> file)
{
	string whitespace = " \n\r\t\f\v";	
	ofstream minified(path);
	minified.clear();
	for (int i = 0; i < file.size(); i++)
	{
		int x = file[i].find_first_not_of(whitespace);
		file[i].erase(0, x);
		minified << file[i];
	}
	minified.close();
}
