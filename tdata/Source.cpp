#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	string s;
	ifstream dataFile;
	dataFile.open("example.tdata", ios::in | ios::beg);

	/*
	ofstream inputFile;
	inputFile.open("temp.tin", ios::out | ios::trunc);
	*/

	if
	while (dataFile >> s)
	{
		cout << s << endl;
	}


	return 0;
}