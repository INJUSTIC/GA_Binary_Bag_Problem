#pragma once
#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include <iostream>

class CGeneticAlgorithm
{
private:
	int pop_Size;
	double cross_Prob;
	double mut_Prob;
	int length_Of_Genotype;
	void generate_Pop();
	void calc_Fitness(CKnapsackProblem* knap_prob);
	vector<CIndividual> population;
	void intersection();
	void mutation();
	int get_Candidate_Index();
	vector<bool>* findBest();
	CGeneticAlgorithm(int pop_Size, double cross_Prob, double mut_Prob);

public:
	static bool try_To_Create_GA_Instance(CGeneticAlgorithm** GA, int pop_Size, double cross_Prob, double mut_Prob);
	vector<bool>* RunAlgorithm(CKnapsackProblem& knap_prob, int generation_Numb);
	static string getError();
};
