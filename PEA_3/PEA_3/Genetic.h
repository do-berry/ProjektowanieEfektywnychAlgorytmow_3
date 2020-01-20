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
	int popSize = 300; // wielkosc populacji
	int stopTime = 90; // czas maksymalny - warunek zatrzymania
	double mutationRate = 0.1; // wspolczynnik mutacji
	double crossoverRate = 0.9; // wspolczynnik krzyzowania
	double selectionRate = 0.2;
	vector<Population> population; // populacja
public:
	Population solution;

	Genetic();
	Genetic(int size, int popSize, int stop, double mutationRate, double crossoverRate);
	~Genetic();
	
	// operatory genetyczne
	Population mutation(Population path, int **costs);
	Population oxCrossover(Population firstParent, Population secondParent, int **costs);
	vector<Population> generatePopulation(int **costs);

	/*   NOWE   */
	static bool compareCosts(const Population &first, const Population &second);
	int sumCosts(vector<int> path, int **costs);
	void printPath(vector<int> path);
	void selection(vector<Population> &population);
	void algorithm(int **costs);
	double getStopTime(double stop, double start);
};

#endif // GENETIC_H
