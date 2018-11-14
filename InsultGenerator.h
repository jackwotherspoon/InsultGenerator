/*
 * InsultGenerator.h
 *
 *  Created on: Sep 26, 2018
 *      Author: Jack Wotherspoon
 *
 */
#ifndef INSULTGENERATOR_H_
#define INSULTGENERATOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

//create File Exception class which checks if file can be opened and if not then spits out error message
class FileException{
public:
		FileException(const string& message);
		string& what();
private:
		string message;
}; // end FileException class

//create NumInsultsOutOfBounds class which will be used to test if number of insults generate is within range specified otherwise spits out error message
class NumInsultsOutOfBounds{
public:
		NumInsultsOutOfBounds(const string& message);
		string& what();
private:
		string message;
}; //end NumInsultsOutOfBounds class

//create insultGenerator class which is used to generate insults and save them if needed
class InsultGenerator{
public:
		InsultGenerator();
		void initialize();										// initialize function reads input file and puts file content into vectors
		string talkToMe();										// talkToMe function returns one insult
		vector<string> generate (const int numInsults);			//generate function calls talkToMe and returns vector with number of insults requested in alpabetical order with no duplicates
		void generateAndSave(string fileName, int numInsults);	// generateAndSave calls generate and then saves vector of insults to a set which is then written to a file
private:
		int randomNum();										//randomNum generates random number between
		vector<string> col1;
		vector<string> col2;
		vector<string> col3;
		set<string> setOfInsults;
}; //end InsultGenerator class




#endif
