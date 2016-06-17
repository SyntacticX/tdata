#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

string removeComments(string line){
	/* If comment is found (whole line), skip line
	* If comment is found (in line), delete comment out.
	* Otherwise, return the line
	*/

	size_t found = line.find("#");
	if (found != string::npos)
		if (found == 0)
			return "";
		else
			return line.substr(0, found);
	else
		return line;
}

vector<string> extractFile(string filePath){
	ifstream file;
	string line;
	vector<string> fileLines(0);

	file.open(filePath);

	// Traverse through each line, checks for comments and removes if found
	if (file.is_open()) {
		cout << "file " << filePath << " is open\n" << endl;
		while (getline(file, line)) {
			line = removeComments(line);
			if (!line.empty()){
				fileLines.push_back(line);
			}
		}
		file.close();
		cout << "file " << filePath << " is closed, extraction performed\n" << endl;
	}
	else {
		cout << "unable to open file " << filePath << "\n" << endl;
	}

	return fileLines;
}


string stringTrans(string str){
	int numeric;
	string translated;
	for (int i = 1; i < str.length()-1; i++){ // start at 1 and end at length-1 to discard ' ' or " "
		if (i > 1){
			translated += " "; // if not the first letter of the string, append space before translation
		}
		numeric = (int) str.at(i);
		translated += to_string(numeric);
	}
	return translated;
}

void createInputFile(string inFile)
{
	vector<string> dataLines = extractFile(inFile); // extract .tdata file in a vector containing all the file lines (comments removed)
	int size = dataLines.size();
	string type;
	string name;


	for (int i = 0; i < size; i++){ // iterate through file lines, create a vector containing all sub strings
		vector<string> line;
		istringstream iss(dataLines[i]);
		string inputLine;

		while (iss){
			string subString;
			iss >> subString;
			line.push_back(subString);
		}

		if (line[2] == ":="){ // check to make sure ":=" is at the correct position, else throw error
			
			type = line[0];
			name = line[1];

			if (type == "int"){
				inputLine = name; // variable name
				inputLine += " := "; // equals
				inputLine += "["; // opening bracket
				inputLine += line[3]; // value
				inputLine += "]"; // closing bracket
			}
			else if (type == "char"){
				inputLine = name; // variable name
				inputLine += " := "; // equals
				inputLine += "["; // opening bracket
				inputLine += stringTrans(line[3]); // value
				inputLine += "]"; // closing bracket

			}

		}
		else {
			cout << "Error on line " << i + 1 << ": Variable declarations must be of format \"<type> <name> := <value>\"" << endl;
			break;
		}

		cout << inputLine << endl;
	
	}


}


int main()
{
	string type;
	string line;
	string dataFile = "example.tdata";

	createInputFile(dataFile);
	/*
	string s = "a";
	// char x = a.at(0);
	int i = (int) s.at(0);

	string g;

	g += s;
	g += " ";
	g += to_string(i);

	cout << g << endl;
	*/
	return 0;
}