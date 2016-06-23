#include <ctype.h>
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
		// cout << "file " << filePath << " is open\n" << endl;
		while (getline(file, line)) {
			line = removeComments(line);
			if (!line.empty()){
				fileLines.push_back(line);
			}
		}
		file.close();
		// cout << "file " << filePath << " is closed, extraction performed\n" << endl;
	}
	else {
		cout << "unable to open file " << filePath << "\n" << endl;
	}

	return fileLines;
}

string stringTranslate(string str){
	int numeric;
	string translated;
	for (int i = 0; i < str.length(); i++){ // start at 1 and end at length-1 to discard ' ' or " "
		if (i > 0){
			translated += " "; // if not the first letter of the string, append space before translation
		}
		numeric = (int) str.at(i);
		translated += to_string(numeric);
	}
	return translated;
}

vector<string> createInput(string inFile)
{
	vector<string> input; 
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
			if (subString != ""){
				line.push_back(subString);
			}
		}

		if (line[2] == ":="){ // check to make sure ":=" is at the correct position, else throw error
			
			type = line[0];
			inputLine = name = line[1];
			inputLine += " := ["; // insert equals and opening bracket

			if (type == "int"){ 
				/* Error Handling */
				// check that only one value is assigned to int variable
				if (line.size() != 4){
					cout << "Problem on line " << i + 1 << ": An int must contain only one value." << endl;
					exit(EXIT_FAILURE);
				}

				// check that value is a valid integer
				for (int x = 0; x < line[3].length(); x++){
					if (!(isdigit(line[3].at(x)))) {
						cout << "Problem on line " << i + 1 << ": An int can only contain an integer number." << endl;
						exit(EXIT_FAILURE);
					}
				}
				inputLine += line[3]; // insert int value
			}

			else if (type == "char"){
				/* Error Handling*/
				if (line[3].length() > 3){
					cout << "Problem on line " << i + 1 << ": A char can only contain one character." << endl;
					exit(EXIT_FAILURE);
				}
				
				if ((line[3].at(0) != '\'') | (line[3].at(line[3].length()-1) != '\'')) {
					cout << "Problem on line " << i + 1 << ": A char must be surrounded by single quotation marks." << endl;
					exit(EXIT_FAILURE);
				}
			

				/* Sanitizing */
				line[3].erase(0, 1); // erase starting '
				line[3].erase(2, 1); // erase ending '  
				inputLine += stringTranslate(line[3]); // value
			}
			else if (type == "int[]"){
				/* Error Handling*/
				if ((line[3].at(0) != '[') | ((line[line.size() - 1].at(line[line.size() - 1].length() - 1)) != ']')) {
					cout << "Problem on line " << i + 1 << ": A integer array must be surrounded by brackets." << endl;
					exit(EXIT_FAILURE);
				}

				/**************************
				STILL NEED TO CHECK IN BETWEEN BRACKETS :-(
				***************************/

				/* Sanitizing */
				line[3].erase(0, 1); // erase starting "
				line[line.size() - 1].erase(line[line.size() - 1].length() - 1); // erase ending "
				for (int j = 3; j < line.size(); j++){
					if (j > 3){
						inputLine += " "; // add space between numbers
						inputLine += line[j]; // insert value
					}
					else {
						inputLine += line[j]; // insert value
					}
				}
			}
			else if (type == "string"){
				/* Error Handling */
				// Checks for use of double quote marks around string
				if ((line[3].at(0) != '"') | ((line[line.size() - 1].at(line[line.size() - 1].length() - 1)) != '"')) {
					cout << "Problem on line " << i + 1 << ": A string must be surrounded by double quotation marks." << endl;
					exit(EXIT_FAILURE);
				}

				/* Sanitizing */
				line[3].erase(0, 1); // erase starting double quote
				line[line.size()-1].erase(line[line.size()-1].length()-1); // erase ending double quote
				for (int j = 3; j < line.size(); j++){ // iterate through each word in string
					if (j > 3){
						inputLine += " "; // add space between words
					}
					inputLine += stringTranslate(line[j]); // insert each value
				}
			}
		}
		else {
			/* Error Handling */
			// Checks for single type and single variable name
			cout << "Error on line " << i + 1 << ": Variable declarations must be of format \"<type> <name> := <value>\"" << endl;
			exit(EXIT_FAILURE);
		}
		inputLine += "]"; // insert closing bracket
		input.push_back(inputLine); // add to vector to be returned
	}
	return input;
}

int main()
{
	string dataFile = "example.tdata";
	vector<string> test = createInput(dataFile);
	
	for (int i = 0; i < test.size(); i++){
		cout << test[i] << endl;
	}

	return 0;
}