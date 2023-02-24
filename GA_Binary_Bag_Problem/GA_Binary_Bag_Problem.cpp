#include <iostream>
#include <vector>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"

void report_Knap_Prob_Error(int error)
{
	cout << CKnapsackProblem::getError(error) << endl;
}

void report_GA_Error()
{
	cout << CGeneticAlgorithm::getError() << endl;
}

void knap_prob_ex()
{
	CKnapsackProblem* knap_prob = NULL;
	string file_Name = "problem_data.txt";
	int res = CKnapsackProblem::try_to_create_Prob_Instance(file_Name, &knap_prob);
	if (res != 0)
	{
		report_Knap_Prob_Error(res);
		return;
	}
	CGeneticAlgorithm* GA = NULL;
	res = CGeneticAlgorithm::try_To_Create_GA_Instance(&GA, 50, 0.6, 0.1);
	if (!res)
	{
		report_GA_Error();
		return;
	}
	double result = knap_prob->GetGenotypeValue(GA->RunAlgorithm(*knap_prob, 4000));
	cout << result << endl;
}

int main()
{
	knap_prob_ex();
}