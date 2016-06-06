#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void createInputFile(ifstream &inFile, ofstream &outFile)
{
	string type;
	string line;
	while (inputFile >> type)
	{
		getline(inputFile, line);
		if (type == "char")
		{
			cout << "This is a char: ";
		}
		if (type == "int")
		{
			cout << "This is an int: ";
		}
		if (type == "int[]")
		{
			cout << "This is an int array: ";
		}
		cout << line << endl;
	}

	// outputFile << x << endl;
}

int main()
{
	string type;
	string line;
	ifstream dataFile;
	dataFile.open("example.tdata", ios::in | ios::beg);

	ofstream inputFile;
	inputFile.open("temp.tin", ios::out | ios::trunc);

	if (dataFile.is_open())
	{
		createInputFile(dataFile, inputFile);
	}
	else
	{
		cout << "Specified data file does not exist. Please recheck specified." << endl;
		return 1;
	}
		
	dataFile.close();
	inputFile.close();


	return 0;
}