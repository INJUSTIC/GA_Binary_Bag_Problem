#include "CGeneticAlgorithm.h"
#include "CIndividual.h"

CGeneticAlgorithm::CGeneticAlgorithm(int pop_Size, double cross_Prob, double mut_Prob)
{
	this->pop_Size = pop_Size;
	this->cross_Prob = cross_Prob;
	this->mut_Prob = mut_Prob;
	length_Of_Genotype = 0;
}

bool CGeneticAlgorithm::try_To_Create_GA_Instance(CGeneticAlgorithm** GA, int pop_Size, double cross_Prob, double mut_Prob)
{
	if (pop_Size <= 0 || cross_Prob <= 0 || cross_Prob > 1 || mut_Prob <= 0 || mut_Prob > 1) return false;
	if (*GA != NULL) delete *GA;
	*GA = new CGeneticAlgorithm(pop_Size, cross_Prob, mut_Prob);
	return true;
}

vector<bool>* CGeneticAlgorithm::RunAlgorithm(CKnapsackProblem& knap_prob, int generation_Numb)
{
	length_Of_Genotype = knap_prob.getItemCount();
	generate_Pop();
	for (int i = 0; i < generation_Numb; i++)
	{
		calc_Fitness(&knap_prob);
		intersection();
		mutation();
	}
	calc_Fitness(&knap_prob);
	return findBest();
}

vector<bool>* CGeneticAlgorithm::findBest()
{
	int bestIndividualIndex = 0;
	double biggestFitness = 0;
	for (int i = 0; i < pop_Size; i++)
	{
		double fitness = population.at(i).get_Fitness();
		if (fitness > biggestFitness)
		{
			bestIndividualIndex = i;
			biggestFitness = fitness;
		}
	} 
	return population.at(bestIndividualIndex).getGenotype();
}

void CGeneticAlgorithm::calc_Fitness(CKnapsackProblem* knap_prob)
{
	for (int i = 0; i < population.size(); i++)
	{
		population.at(i).Calc_Fitness(knap_prob);
	}
}

void CGeneticAlgorithm::intersection()
{
	////srand(time(NULL));
	vector<CIndividual> new_Population;
	for (int i = 0; i < pop_Size; i+=2)
	{
		int first = get_Candidate_Index();
		int second = get_Candidate_Index();
		int third = get_Candidate_Index();
		while (first == second || first == third || second == third)
		{
			if (first == second) second = get_Candidate_Index();
			if(first == third) third = get_Candidate_Index();
			if (second == third) third = get_Candidate_Index();
		}
		double cross = (rand() % 101) / 100.0;
		if (cross > cross_Prob)
		{
			int par[] = { first, second, third };
			int fst = rand() % 3;
			int snd = rand() % 3;
			while (snd == fst) snd = rand() % 3;
			new_Population.push_back(population.at(par[fst]));
			new_Population.push_back(population.at(par[snd]));
		}
		else
		{
			pair<CIndividual*, CIndividual*> children = population.at(first).Intersection(&(population.at(second)), &(population.at(third)));
			new_Population.push_back(*children.first);
			if (new_Population.size() != population.size())
			{
				new_Population.push_back(*children.second);
			}
			delete children.first;
			delete children.second;
		}
	}
	population = new_Population;
}

int CGeneticAlgorithm::get_Candidate_Index()
{
	int first = rand() % pop_Size;
	int second = rand() % pop_Size;
	while(second == first) second = rand() % pop_Size;
	int winner = population.at(first).get_Fitness() < population.at(second).get_Fitness() ? second : first;
	return winner;
}

void CGeneticAlgorithm::mutation()
{
	for (int i = 0; i < pop_Size; i++)
	{
		population.at(i).Mutate(mut_Prob);
	}
}

void CGeneticAlgorithm::generate_Pop()
{
	population.clear();
	for (int i = 0; i < pop_Size; i++)
	{
		population.push_back(CIndividual(length_Of_Genotype));
	}
}

string CGeneticAlgorithm::getError()
{
	return "Incorrect parameters while creating CGeneticAlgorithm object";
}