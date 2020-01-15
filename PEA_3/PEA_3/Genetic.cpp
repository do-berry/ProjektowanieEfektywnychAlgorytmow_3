#include "Genetic.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

Genetic::Genetic() {}

Genetic::Genetic(int size, int popSize, int stop, double mutationRate, double crossoverRate) {
	this->size = size;
	this->popSize = popSize;
	this->stop = stop;
	this->mutationRate = mutationRate;
	this->crossoverRate = crossoverRate;
}

Genetic::~Genetic() {}

bool Genetic::compareCosts(const Population& first, const Population& second) {
	return first.cost < second.cost;
}

int Genetic::sumCosts(vector<int> path, int **costs) {
	int sum = 0;

	for (int i = 0; i < path.size() - 1; i++)
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

// krzyzowanie OX
Population Genetic::oxCrossover(Population firstParent, Population secondParent, int **costs) {
	Population child;
	child.population.resize(size, -1); // {-1, -1, .. , -1}
	child.cost = -1;

	printPath(firstParent.population);
	printPath(secondParent.population);

	double random = double(rand()) / (double(RAND_MAX) + 1.0);

	if (random < crossoverRate) {
		vector<int> visited;
		int x, y;
		do {
			x = rand() % size;
			y = rand() % size;
		} while (x == y);

		if (x > y) {
			swap(x, y);
		}

		cout << x << " " << y << endl;

		for (int i = x; i <= y; i++) {
			child.population.at(i) = firstParent.population.at(i);
			visited.push_back(firstParent.population.at(i));
		}

		int childIndex = 0;
		for (int i = 0; i < size; i++) {
			if (find(visited.begin(), visited.begin() + visited.size(), secondParent.population.at(i)) == visited.end()) {
				while (child.population.at(childIndex) > 0  && childIndex < child.population.size()) {
					childIndex++;
				}

				child.population.at(childIndex) = secondParent.population.at(i);
				visited.push_back(secondParent.population.at(i));
			}
		}

		child.cost = sumCosts(child.population, costs);
	}

	printPath(child.population);

	return child;
}

//vector<Population> Genetic::generatePopulation() {
//	
//}
