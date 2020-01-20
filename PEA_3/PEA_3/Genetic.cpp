#include "Genetic.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <assert.h>     /* assert */


using namespace std;

Genetic::Genetic() {}

Genetic::Genetic(int size, int popSize, int stop, double mutationRate, double crossoverRate) {
	this->size = size;
	this->popSize = popSize;
	this->stopTime = stop;
	this->mutationRate = mutationRate;
	this->crossoverRate = crossoverRate;

	// domyslne gdy nie zostalo znalezione rozwiazanie
	solution.cost = INT_MAX;
	solution.population.resize(size, -1);
}

Genetic::~Genetic() {
	population.clear();
}

bool Genetic::compareCosts(const Population &first, const Population &second) {
	return (first.cost < second.cost);
}

int Genetic::sumCosts(vector<int> &path, int **costs) {
	int sum = 0;

	int size = path.size();

	assert(size > 0);

	for (int i = 0; i < size - 1; i++)
	{
		sum += costs[path.at(i)][path.at(i + 1)];
	}
	sum += costs[path.at(path.size() - 1)][path.at(0)];

	return sum;
}

void Genetic::printPath(vector<int> path) {
	for (int i = 0; i < size; i++)
	{
		cout << path.at(i) << "->";
	}
	cout << path.at(0) << endl;
}

/*
operatory genetyczne
*/

// mutacja: zamiana losowych wierzcholkow
Population Genetic::mutation(Population path, int **costs) {
	double random = double(rand()) / (double(RAND_MAX) + 1.0);

	if (random < mutationRate) {
		int x, y;
		do {
			x = rand() % size;
			y = rand() % size;
		} while (x == y);

		swap(path.population.at(x), path.population.at(y));

		int newCost = sumCosts(path.population, costs);
		path.cost = newCost;
	}

	return path;
}

// krzyzowanie
Population Genetic::oxCrossover(Population &firstParent, Population &secondParent, int **costs) {
	Population child;

	int parentSize = firstParent.population.size();
	//int pivot = rand() % parentSize;


	//
	// Copy first part.
	//

	int beginIndex = rand() % (parentSize / 2);

	for (int i = 0; i < parentSize / 2; ++i)
	{
		child.population.push_back(firstParent.population.at(beginIndex + i));
	}

	//
	// Copy second part.
	//

	for (int i = 0; i < parentSize; ++i)
	{
		bool exist = false;
		for (int j = 0; j < child.population.size(); ++j)
		{
			if (secondParent.population.at(i) == child.population.at(j))
			{
				exist = true;
				break;
			}
		}

		if (!exist)
		{
			child.population.push_back(secondParent.population.at(i));
		}
	}

	child.cost = sumCosts(child.population, costs);

	return child;

	////for (int i = pivot; i < parentSize; i++)
	////while(child.population.size() < firstParent.population.size()) // fix it
	////{
	//	for (int j = 0; j < parentSize; j++)
	//	//while (child.population.size() < firstParent.population.size())
	//	{
	//		std::vector<int>::iterator itBegin = child.population.begin();
	//		std::vector<int>::iterator itEnd = child.population.end();
	//		std::vector<int>::iterator it = find(itBegin, itEnd, secondParent.population[j]);

	//		if (it != itEnd)
	//		{
	//			child.population.push_back(*it);
	//		}
	//	}
	////}



	//for (int i = pivot; i < parentSize; i++)
	//{
	//	child.population.at(i) = firstParent.population.at(i);
	//	//visited.at(firstParent.population.at(i)) = true;
	//}

	//vector<bool> visited;
	//visited.resize(size, false);


	//for (int i = 1; i < size - 1; i++) {
	//	child.population.at(i) = firstParent.population.at(i);
	//	visited.at(firstParent.population.at(i)) = true;
	//}

	//bool isStartVisited = false;
	//for (int i = 0; i < size; i++) {
	//	if (visited[secondParent.population.at(i)] == false) {
	//		if (isStartVisited == false) {
	//			child.population.at(0) = secondParent.population.at(i);
	//			visited.at(secondParent.population.at(i)) = true;
	//			isStartVisited = true;
	//		}
	//		else {
	//			child.population.at(size - 1) = secondParent.population.at(i);
	//			visited.at(secondParent.population.at(i)) = true;
	//		}
	//	}
	//}

	//child.cost = sumCosts(child.population, costs);
	//
	//return child;
}

vector<Population> Genetic::generatePopulation(int **costs) {
	vector<Population> population;
	Population p; // path + cost

				  // popSize - wielkosc populacji
	for (int i = 0; i < popSize; i++) {
		// {0, 1, .. , n}
		for (int j = 0; j < size; j++) {
			p.population.push_back(j);
		}
		// mieszanie
		random_shuffle(p.population.begin(), p.population.end());
		// przypisanie kosztu rozwiazania
		p.cost = sumCosts(p.population, costs);
		// dodanie do populacji
		population.push_back(p);

		p.population.clear();
	}

	return population;
}

void Genetic::selection(vector<Population> &population) {
	//cout << "sorted:" << endl;
	sort(population.begin(), population.end(), compareCosts);

	// nowy rozmiar populacji
	int newPopSize = population.size() * 0.5;//selectionRate;
	vector<Population> newPopulation;

	int limit = population.size() / 2;

	for (int i = 0; i < limit; i++)
		population.pop_back();


	//population.clear();
	//
	//population = newPopulation;
	//popSize = newPopSize;

	//newPopulation.clear();
}

void Genetic::algorithm(int **costs) {
	clock_t start, stop;
	vector<Population> population = generatePopulation(costs);
	vector<int> path;

	//int globalPopSize = popSize;
	//int counter = 0;
	start = clock();
	//do {
	for (int k = 0; k < 500; k++)
	{
		//counter++;
		//for (int i = 0; i < globalPopSize; i++) {
		//double random = double(rand()) / (double(RAND_MAX) + 1.0);

		selection(population);
		int parrentSize = population.size();
		//int howMany = globalPopSize - population.size();
		//if (random < crossoverRate) {
		//int first, second;
		for (int j = 0; j < size; j++)
		{
			int x, y;
			do
			{
				x = rand() % parrentSize;
				y = rand() % parrentSize;
			} while (x == y);

			Population child = oxCrossover(population.at(x), population.at(y), costs);
			population.push_back(child);
		}
		//}
		//}

		for (int j = 0; j < population.size(); j++) {
			mutation(population.at(j), costs);
		}

		sort(population.begin(), population.end(), compareCosts);

		//while (population.size() > globalPopSize) {
		//	population.pop_back();
		//	popSize--;
		//}

		//stop = clock();

		if (population.front().cost < solution.cost) {
			solution.cost = population.front().cost;
			solution.population = population.front().population;
		}
		//cout << "dupa " << counter << endl;
	} //while (getStopTime(stop, start) <= stopTime);
	  //cout << "dupa " << counter << endl;
}

double Genetic::getStopTime(double stop, double start) {
	return (double(stop - start) / CLOCKS_PER_SEC);
}
