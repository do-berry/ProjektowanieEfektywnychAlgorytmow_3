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
	int stop; // maksymalna liczba pokolen - warunek zatrzymania
	double mutationRate; // wspolczynnik mutacji
	double crossoverRate; // wspolczynnik krzyzowania
	int startIndex; // wierzcholek poczatkowy
	int **population; // populacja
public:
	Genetic();
	Genetic(int size, int popSize, int stop, double mutationRate, double crossoverRate);
	~Genetic();
	
	// operatory genetyczne
	Population mutation(Population path, int **costs);
	Population oxCrossover(Population firstParent, Population secondParent, int **costs);
	//vector<Population> generatePopulation();

	/*   NOWE   */
	bool compareCosts(const Population& first, const Population& second);
	int sumCosts(vector<int> path, int **costs);
	void printPath(vector<int> path);
};

#endif // GENETIC_H
