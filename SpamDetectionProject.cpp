//Written By - Darien L
//Project 2 - Checkpoint B
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Global variable for length of all cases
int const LENGTH = 48;

//Function Declarations
void initializeVectors(vector<vector<int>>& S, vector<vector<int>>& H, string trainDataIn, string trainClassIn);
void tests(string testDataIn, vector<vector<int>>& testData);
double bayesFormula(vector<vector<int>> myVec, vector<vector<int>> testCase, int totalNum, int i);
double detectionRate(vector<vector<int>> S, vector<vector<int>> H, vector<vector<int>> testData,
	string testClassIn, int totalNum, int testClassHeight);
int getTestClassHeight(string testClassIn);
void userInput(string& trainDataIn, string& trainClassIn, string& testDataIn, string& testClassIn);

int main() {
	vector<vector<int>> S, H, testData;
	string trainDataIn, trainClassIn, testDataIn, testClassIn;

	//! USER INPUT:
	userInput(trainDataIn, trainClassIn, testDataIn, testClassIn);

	//! VECTOR INITIALIZATIONS:
	initializeVectors(S, H, trainDataIn, trainClassIn);

	//! TEST INITIALIZATIONS:
	tests(testDataIn, testData);
	
	//! OUTPUT:
	cout.precision(6);
	cout << "\nTraining using " << S.size() + H.size() << " cases" << endl;
	cout << "Evaluating " << testData.size() - 1 << " test cases" << endl;
	cout << "Successful detection rate of " << 
		detectionRate(S, H, testData, testClassIn, (S.size() + H.size()), getTestClassHeight(testClassIn))
		<< "%" << endl;

	return 0;
}

//Function for creating the 2D vectors and giving them the correct values
void initializeVectors(vector<vector<int>>& S, vector<vector<int>>& H, string trainDataIn, string trainClassIn) {
	int tempNum = 0;
	ifstream inFileClass, inFileData;
	inFileClass.open(trainClassIn.c_str());
	inFileData.open(trainDataIn.c_str());
	//While loop checks if 1 or 0 adding to height accordingly
	while (inFileClass >> tempNum) {
		if (tempNum == 1) {
			vector<int> tempVector1;	//Vector to store row elements
			for (int i = 0; i < LENGTH; i++) {
				inFileData >> tempNum;
				tempVector1.push_back(tempNum);
			}S.push_back(tempVector1);	//Pushing back above 1D vector to create the 2D vector
		}
		else {
			vector<int> tempVector2;	//Vector to store row elements
			for (int i = 0; i < LENGTH; i++) {
				inFileData >> tempNum;
				tempVector2.push_back(tempNum);
			}H.push_back(tempVector2);	//Pushing back above 1D vector to create the 2D vector
		}
	}inFileClass.close(); inFileData.close();
}

//Function for initializing the test 2D vector
void tests(string testDataIn, vector<vector<int>>& testData) {
	int tempNum = 0;
	ifstream inFileTestData;
	inFileTestData.open(testDataIn.c_str());

	while (!inFileTestData.eof()) {
		vector<int> tempVector;				//vector to store row elements
		for (int i = 0; i < LENGTH; i++) {
			inFileTestData >> tempNum;
			tempVector.push_back(tempNum);
		}testData.push_back(tempVector);	//Pushing back above 1D vector to create the 2D vector
	}inFileTestData.close();
}

//Funciton returns the float value of the probability for the test case to occur in the given class
double bayesFormula(vector<vector<int>> spamOrHamVec, vector<vector<int>> testData, int totalNum, int i) {
	double productResult = 1.0;
	int occuranceNum = 0;
	
	//For loop determines the product pie for the bayes formula
	for (int j = 0; j < LENGTH; j++) {
		//If statement for when testCase is '1' and else is for '0'
		if (testData[i][j] == 1) {
			//Calculates '1' occurrences in col
			for (int m = 0; m < spamOrHamVec.size(); m++) {
				if (spamOrHamVec[m][j] == 1)
					occuranceNum++;
			}productResult *= (double(occuranceNum) / double(spamOrHamVec.size()));
		}else {
			for (int m = 0; m < spamOrHamVec.size(); m++) {
				if (spamOrHamVec[m][j] == 1)
					occuranceNum++;
			}productResult *= 1.0 - (double(occuranceNum) / double(spamOrHamVec.size()));
		}occuranceNum = 0;
	}
	return double(spamOrHamVec.size()) / double(totalNum) * productResult;
}

//Function gets the detection rate percentage
double detectionRate(vector<vector<int>> S, vector<vector<int>> H, vector<vector<int>> testData,
		string testClassIn, int totalNum, int testClassHeight) {
	int counter = 0, testClassNum = -1;
	double probS = 0.0, probH = 0.0;
	ifstream inFileTestClass;
	inFileTestClass.open(testClassIn.c_str());

	for (int i = 0; i < testClassHeight; i++) {
		probS = bayesFormula(S, testData, totalNum, i);
		probH = bayesFormula(H, testData, totalNum, i);
		inFileTestClass >> testClassNum;

		if (probS > probH && testClassNum == 1)
			counter++;
		else if (probH > probS && testClassNum == 0)
			counter++;
	}inFileTestClass.close();
	return (double(counter) / double(testClassHeight)) * 100;
}

//Function gets test class height
int getTestClassHeight(string testClassIn) {
	int counter = 0, tempNum = 0;
	ifstream inFileTestClass;
	inFileTestClass.open(testClassIn.c_str());

	while (inFileTestClass >> tempNum) {
		counter++;
	}return counter;
}

// Function asks the user to input the file names corresponding to training data, training class, test data, and test class
void userInput(string& trainDataIn, string& trainClassIn, string& testDataIn, string& testClassIn) {
	cout << "Enter the names of the training data, training class, test data and test class files (in that order): ";
	getline(cin, trainDataIn); getline(cin, trainClassIn); getline(cin, testDataIn); getline(cin, testClassIn);
}