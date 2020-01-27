#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
using namespace std;

struct Population {
	vector<int> population;
	int cost;
};

class Genetic {
private:
	int size; // ile miast
	int popSize; // wielkosc populacji
	double mutationRate; // wspolczynnik mutacji
	double crossoverRate; // wspolczynnik krzyzowania
	vector<Population> population; // populacja
	void selection(vector<Population> &population);
	Population mutation(Population path, int **costs);
	Population oxCrossover(Population &firstParent, Population &secondParent, int **costs);
	vector<Population> generatePopulation(int **costs);
	static bool compareCosts(const Population &first, const Population &second);
	int sumCosts(vector<int> &path, int **costs);
public:
	Population solution; // najlepsze znalezione rozwiazanie
	Genetic();
	Genetic(int size, int popSize, double mutationRate, double crossoverRate);
	~Genetic();
	void printPath(vector<int> path);
	void algorithm(int **costs);
};

#endif // GENETIC_H
