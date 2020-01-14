#ifndef GENETIC_H
#define GENETIC_H

class Genetic {
private:
	int size; // ile miast
	int popSize; // wielkosc populacji
	int stop; // maksymalna liczba pokolen - warunek zatrzymania
	double mutationRate; // wspolczynnik mutacji
	double crossoverRate; // wspolczynnik krzyzowania
	int startIndex; // wierzcholek poczatkowy
public:
	Genetic();
	Genetic(int size, int popSize, int stop, double mutationRate, double crossoverRate);
	~Genetic();
	// kopia z poprzednich projektow
	int * randomSwap(int *path);
	void swapValues(int &first, int &second);
	int sumCosts(int *path, int **costs);
	void copyArray(int *from, int *to);
	void printPath(int *path);
	// operatory genetyczne
	int * mutation(int *path);
	void oxCrossover(int *firstParent, int *secondParent);
};

#endif // GENETIC_H
