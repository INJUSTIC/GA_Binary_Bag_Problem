#pragma once
#include <string>
#include<iostream>
#include<vector>
#include <fstream>

const int ERR_OK = 0;
const int ERR_FILE_ALREADY_TAKEN = 1;
const int ERR_FILE_NOT_OPEN = 2;
const int ERR_INVALID_DATA_IN_FILE = 3;

using namespace std;
class CKnapsackProblem
{
public:
	double GetGenotypeValue(vector<bool>* genotype);
	vector<double>* getItemWeights() { return &itemWeights; };
	vector<double>* getItemValues() { return &itemValues; };
	double get_Bag_Value() { return bagValue; }
	int getItemCount() { return itemCount; }
	static int try_to_create_Prob_Instance(string path, CKnapsackProblem** prob);
	static string getError(int error_Type);
private:
	CKnapsackProblem();
	const int file_line_count = 4;
	//CKnapsackProblem(string path);
	double bagValue;
	int itemCount;
	vector<double> itemWeights, itemValues;
	ifstream* problemSource;
	int readProblemFromFile(string path);
	//void setToDefault();
};