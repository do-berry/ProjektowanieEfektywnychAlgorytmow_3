#include "Genetic.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <assert.h>     /* assert */


using namespace std;

Genetic::Genetic() {}

Genetic::Genetic(int size, int popSize, double mutationRate, double crossoverRate) {
	this->size = size;
	this->popSize = popSize;
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

// sumowanie kosztow 
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

// wypisywanie sciezki
void Genetic::printPath(vector<int> path) {
	for (int i = 0; i < size; i++)
	{
		cout << path.at(i) << "->";
	}
	cout << path.at(0) << endl;
}

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
	// losowanie indeksu poczatkowego elementu
	int beginIndex = rand() % (parentSize / 2);

	// kopiowanie polowy elementow z pierwszego rodzica do potomka
	for (int i = 0; i < parentSize / 2; ++i) {
		child.population.push_back(firstParent.population.at(beginIndex + i));
	}

	// kopiowanie elementow nieobecnych z drugiego rodzica
	for (int i = 0; i < parentSize; ++i) {
		bool inPath = false;
		for (int j = 0; j < child.population.size(); ++j) {
			if (secondParent.population.at(i) == child.population.at(j)) {
				inPath = true;
				break;
			}
		}

		if (!inPath) {
			child.population.push_back(secondParent.population.at(i));
		}
	}

	child.cost = sumCosts(child.population, costs);

	return child;
}

// generowanie populacji poczatkowej
vector<Population> Genetic::generatePopulation(int **costs) {
	vector<Population> population;
	Population p; // path + cost

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

// selekcja
void Genetic::selection(vector<Population> &population) {
	sort(population.begin(), population.end(), compareCosts);

	// wybieranie polowy elemnetow
	int limit = population.size() / 2;

	for (int i = 0; i < limit; i++) {
		population.pop_back();
	}
}

// glowny algorytm
void Genetic::algorithm(int **costs) {
	vector<Population> population = generatePopulation(costs);

	for (int k = 0; k < 5000; k++) {
		double random = double(rand()) / (double(RAND_MAX) + 1.0);

		// selekcja osobnikow
		selection(population);
		int parentSize = population.size();
		if (random < crossoverRate) {
			for (int j = 0; j < size; j++) {
				// losowanie rodzicow do krzyzowania
				int x, y;
				do {
					x = rand() % parentSize;
					y = rand() % parentSize;
					if (parentSize == 1) {
						break;
					}
				} while (x == y);
				
				// krzyzowanie
				Population child = oxCrossover(population.at(x), population.at(y), costs);
				population.push_back(child);
			}
		}

		// mutacja
		for (int j = 0; j < population.size(); j++) {
			mutation(population.at(j), costs);
		}

		// sortowanie
		sort(population.begin(), population.end(), compareCosts);

		if (population.front().cost < solution.cost) {
			solution.cost = population.front().cost;
			solution.population = population.front().population;
		}
	}
}

