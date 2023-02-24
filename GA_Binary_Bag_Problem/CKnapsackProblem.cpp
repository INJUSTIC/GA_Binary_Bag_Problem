#include "CKnapsackProblem.h";

/*
CKnapsackProblem::CKnapsackProblem(string path)
{
	problemSource = NULL;
	int result = readProblemFromFile(path);

}
*/

CKnapsackProblem::CKnapsackProblem()
{
	problemSource = NULL;
	bagValue = 0;
	itemCount = 0;
}

int CKnapsackProblem::try_to_create_Prob_Instance(string path, CKnapsackProblem** prob)
{
	if (*prob != NULL) delete *prob;
	*prob = new CKnapsackProblem();
	int result = (*prob)->readProblemFromFile(path);
	if (result != 0) delete *prob;
	return result;
}


/*
void CKnapsackProblem::setToDefault()
{
	bagValue = 0;
	itemCount = 0;
	itemWeights.clear();
	itemValues.clear();
	delete problemSource;
	problemSource = NULL;
}
*/

double CKnapsackProblem::GetGenotypeValue(vector<bool>* genotype)
{
	double value = 0;
	for (int i = 0; i < itemCount; i++)
	{
		if (genotype->at(i)) value += itemValues.at(i);
	}
	return value;
}

int CKnapsackProblem::readProblemFromFile(string path)
{
	if (problemSource != NULL) return ERR_FILE_ALREADY_TAKEN;
	problemSource = new ifstream(path);
	if (!problemSource->is_open()) return ERR_FILE_NOT_OPEN;
	vector<string> lines;
	string line;
	while (getline(*problemSource, line)) lines.push_back(line);
	if (lines.size() != file_line_count)
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}
	try
	{
		bagValue = stod(lines.at(0));
	}
	catch (...)
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}
	if (bagValue <= 0)
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}
	try
	{
		itemCount = stoi(lines.at(1));
	}
	catch (...)
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}
	if (itemCount <= 0) 
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}
	string weightLine = lines.at(2);
	char* char_array = new char[weightLine.length() + 1];
	char* next_token;
	for (int i = 0; i < weightLine.length(); i++)
	{
		char_array[i] = weightLine[i];
	}
	char_array[weightLine.length()] = '\0';
	char* token = strtok_s(char_array, " ", &next_token);
	for (int i = 0; token != NULL && i < itemCount; i++)
	{
		double weight;
		try
		{
			weight = stod(token);
		}
		catch (...)
		{
			delete token;
			delete[] char_array;
			problemSource->close();
			return ERR_INVALID_DATA_IN_FILE;
		}
		if (weight <= 0)
		{
			delete[] char_array;
			delete token;
			problemSource->close();
			return ERR_INVALID_DATA_IN_FILE;
		}
		itemWeights.push_back(weight);
		token = strtok_s(NULL, " ", &next_token);
	}
	if (itemWeights.size() < itemCount || token != NULL)
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}

	string valueLine = lines.at(3);
	for (int i = 0; i < valueLine.length(); i++)
	{
		char_array[i] = valueLine[i];
	}
	char_array[valueLine.length()] = '\0';
	token = strtok_s(char_array, " ", &next_token);
	for (int i = 0; token != NULL && i < itemCount; i++)
	{
		double value;
		try
		{
			value = stod(token);
		}
		catch (...)
		{
			delete token;
			delete[] char_array;
			problemSource->close();
			return ERR_INVALID_DATA_IN_FILE;
		}
		if (value <= 0)
		{
			delete[] char_array;
			delete token;
			problemSource->close();
			return ERR_INVALID_DATA_IN_FILE;
		}
		itemValues.push_back(value);
		token = strtok_s(NULL, " ", &next_token);
	}
	if (itemValues.size() < itemCount || token != NULL)
	{
		problemSource->close();
		return ERR_INVALID_DATA_IN_FILE;
	}
	problemSource->close();
	return ERR_OK;
}

string CKnapsackProblem::getError(int error_Type)
{
	switch (error_Type)
	{
	case 1:
	{
		return "File is already used";
	}
	case 2:
	{
		return "Error while opening the file";
	}
	case 3:
	{
		return "File contains invalid data";
	}
	default:
	{
		return "Unknown error";
	}
	}
}