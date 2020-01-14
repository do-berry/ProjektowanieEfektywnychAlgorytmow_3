#include "Genetic.h"
#include <cstdlib>
#include <iostream>

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

/*
	kopie metod z poprzednich projektow
*/

int * Genetic::randomSwap(int *path) {
	int a = rand() % size;
	int b = rand() % size;

	while (a == b) {
		b = rand() % size;
	}
	swapValues(path[a], path[b]);

	return path;
}

void Genetic::swapValues(int &first, int &second)
{
	int copy = first;
	first = second;
	second = copy;
}

int Genetic::sumCosts(int *path, int **costs) {
	int sum = 0;
	for (int i = 1; i < size; i++)
	{
		sum += costs[path[i - 1]][path[i]];
	}
	sum += costs[path[size - 1]][path[0]];

	return sum;
}

void Genetic::copyArray(int *from, int *to)
{
	for (int i = 0; i < size; i++)
	{
		to[i] = from[i];
	}
}

void Genetic::printPath(int *path) {
	for (int i = 0; i < size; i++)
	{
		cout << path[i] << "->";
	}
	cout << path[0] << endl;
}

/*
	operatory genetyczne
*/

// mutacja: zamiana losowych wierzcholkow
// - innych niz wierzcholek poczatkowy
int * Genetic::mutation(int * path) {
	double random = double(rand()) / (double(RAND_MAX) + 1.0);

	if (random < mutationRate) {
		path = randomSwap(path);
	}
	
	return path;
}

// krzyzowanie OX
void Genetic::oxCrossover(int * firstParent, int * secondParent) {
	int * child = new int[size];
	bool * visited = new bool[size];
	double random = double(rand()) / (double(RAND_MAX) + 1.0);

	if (random < crossoverRate) {
		int firstIndex = rand() % size + 1;
		int secondIndex = rand() % size + 1;

		while (firstIndex == secondIndex) {
			secondIndex = rand() % size;
		}
		if (firstIndex > secondIndex) {
			swapValues(firstIndex, secondIndex);
		}

		//cout << "indexes: " << firstIndex << " " << secondIndex << endl;

		for (int i = firstIndex; i <= secondIndex; i++) {
				child[i] = firstParent[i];
				visited[firstParent[i]] = true;
		}

		int childIndex = 0;
		for (int i = 0; i < size; i++) {
			if (visited[secondParent[i]] != true) {
				while (child[childIndex] > 0 && childIndex < size) {
					childIndex++;
				}
				child[childIndex] = secondParent[i]; // czy to dobrze czy to zle
			}
		}
	}
	
	//printPath(child);
}
