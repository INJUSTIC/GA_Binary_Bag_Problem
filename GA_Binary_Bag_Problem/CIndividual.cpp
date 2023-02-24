#include "CIndividual.h"
#include "CKnapsackProblem.h"

CIndividual::CIndividual(int genotype_Length)
{
	generate_Genotype(genotype_Length);
}

CIndividual::CIndividual() 
{
	fitness = 0;
	genotype_Size = 0;
}

void CIndividual::generate_Genotype(int length)
{
	genotype_Size = length;
	for (int i = 0; i < genotype_Size; i++)
	{
		genotype.push_back(rand() % 2);
	}
}

void CIndividual::Calc_Fitness(CKnapsackProblem* knap_prob)
{
	fitness = 0;
	vector<double>* itemWeights = knap_prob->getItemWeights();
	vector<double>* itemValues = knap_prob->getItemValues();
	double sum_weight = 0;
	for (int i = 0; i < genotype_Size; i++)
	{
		if (genotype.at(i))
		{
			fitness += itemValues->at(i);
			sum_weight += itemWeights->at(i);
			if (sum_weight > knap_prob->get_Bag_Value())
			{
				fitness = 0;
				return;
			}
		}
	}
}

pair<CIndividual*, CIndividual*> CIndividual::Intersection(CIndividual* intersectionPair)
{
	//srand(time(NULL));
	CIndividual* first_Child = new CIndividual();
	CIndividual* secondChild = new CIndividual();
	first_Child->genotype_Size = secondChild->genotype_Size = genotype_Size;
	int splitIndex = rand() % (genotype_Size - 1) + 1;
	for (int i = 0; i < splitIndex; i++)
	{
		first_Child->genotype.push_back(genotype.at(i));
		secondChild->genotype.push_back(intersectionPair->genotype.at(i));
	}
	for (int i = splitIndex; i < genotype_Size; i++)
	{
		first_Child->genotype.push_back(intersectionPair->genotype.at(i));
		secondChild->genotype.push_back(genotype.at(i));
	}
	return pair<CIndividual*, CIndividual*>(first_Child, secondChild);
}

pair<CIndividual*, CIndividual*> CIndividual::Intersection(CIndividual* first_intersectionPair, CIndividual* second_intersectionPair)
{
	CIndividual** parents = new CIndividual*[3];
	parents[0] = this, parents[1] = first_intersectionPair, parents[2] = second_intersectionPair;
	CIndividual* first_Child = new CIndividual();
	CIndividual* secondChild = new CIndividual();
	first_Child->genotype_Size = secondChild->genotype_Size = genotype_Size;
	int res1, res2;
	for (int i = 0; i < genotype_Size; i++)
	{
		res1 = rand() % 3;
		res2 = rand() % 3;
		while(res2 == res1) res2 = rand() % 3;
		first_Child->genotype.push_back(parents[res1]->genotype.at(i));
		secondChild->genotype.push_back(parents[res2]->genotype.at(i));
	}
	delete[] parents;
	return pair<CIndividual*, CIndividual*>(first_Child, secondChild);
}


void CIndividual::Mutate(double mutProb)
{
	//srand(time(NULL));
	for (int i = 0; i < genotype.size(); i++)
	{
		if (((rand() % 101) / 100.0) <= mutProb)
		{
			genotype[i] = !genotype[i];
		}
	}
}