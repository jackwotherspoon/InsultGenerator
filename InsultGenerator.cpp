/*
 * InsultGenerator.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Jack Wotherspoon
 */
#include "InsultGenerator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

FileException::FileException(const string& message) : message(message) {} //end of FileException constructor
string& FileException::what() {return message;}

InsultGenerator::InsultGenerator(){} // end of InsultGenerator constructor

void InsultGenerator::initialize(){
	ifstream inFile;
	string line;
	inFile.open("InsultsSource.txt");   // open file with all insult words
	if (inFile.fail()) {
			throw FileException("File can not be read!");
		} //end of exception check
	int count(0);
	while (inFile >> line){     // go through each line of file and sort into vectors by column
				count++;
				if (count==1){
					col1.push_back(line);   // add to column 1
				}
				if (count==2){
					col2.push_back(line);   // add to column 2
				}
				if (count==3){
					col3.push_back(line);   // add to column 3
					count=0;
				}
	}
	inFile.close();

} // end of initialize

int InsultGenerator::randomNum(){
	int num = rand() % 49; //generate random number between index of 0 and 49
	return num;
} // end of randomNum

string InsultGenerator::talkToMe() {
	string insult;
	int num1 = randomNum();
	int num2 = randomNum();
	int num3 = randomNum();
	insult = "Thou " + col1[num1] + " " + col2[num2] + " " + col3[num3] + "!";  //return a random index for each column and create an insult of type string
	return insult;
} // end of talkToMe

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {} // end of numInsultsOutOfBounds constructor
string& NumInsultsOutOfBounds::what() {return message;} // end of exception

vector<string> InsultGenerator::generate(int numInsults){
	if (numInsults < 1 || numInsults > 10000){
		throw NumInsultsOutOfBounds("This is not valid number of insults! Must be between 1 and 10000");
	} // end of exception check

	set<string> setOfInsults;
	string insult;
	while (numInsults > setOfInsults.size()){    //keep generating insults until set is filled with number that was requested
		insult = string(talkToMe());
		setOfInsults.insert(insult);
	} //create sets of insults that are sorted and do not repeat
	vector<string> insults;
	copy(setOfInsults.begin(), setOfInsults.end(), back_inserter(insults));
	return insults;
} //end of generate

void InsultGenerator::generateAndSave(string fileName, int numInsults){
	int lineNumber=0;
	vector<string> insultVector = generate(numInsults);   // generate required number of insults
	ofstream outFile(fileName.c_str());                   // create output file to write to
	if (outFile.fail()){
		throw FileException("File can not be written");  // if file can not be written to throw exception
	} // end of file exception

	while(lineNumber < numInsults){
		outFile << insultVector[lineNumber] << endl;
		lineNumber++;
	}
	outFile.close();
}
