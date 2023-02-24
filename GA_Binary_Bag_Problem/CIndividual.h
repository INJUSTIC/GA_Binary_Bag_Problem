#pragma once
#include <string>
#include<iostream>
#include<vector>
#include "CKnapsackProblem.h"
#include <random>

using namespace std;

class CIndividual
{
private:
	void generate_Genotype(int length);
	double fitness;
	int genotype_Size;
	CIndividual();
	vector<bool> genotype;
public:
	CIndividual(int genotype_Length);
	void Calc_Fitness(CKnapsackProblem* knap_prob);
	double get_Fitness() { return fitness; }
	void Mutate(double mut_Prob);
	vector<bool>* getGenotype() { return &genotype; }
	pair<CIndividual*, CIndividual*> Intersection(CIndividual* intersectionPair);
	pair<CIndividual*, CIndividual*> Intersection(CIndividual* first_intersectionPair, CIndividual* second_intersectionPair);
};
