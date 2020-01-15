#include <iostream>
#include <climits>
#include <windows.h>
#include "Reader.h"
#include "Genetic.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std::chrono;
using namespace std;

int main()
{
	srand(time(NULL));

	char choice;
	Reader * reader;
	Genetic * genetic = new Genetic(6, 10, 10, 50, 50);
	char name[] = "test.txt";
	boolean isRead = false;					// czy graf jest wczytany

	cout << "Menu:" << endl;
	cout << "1. Wczytaj graf" << endl
		<< "2. Wyswietl graf" << endl
		<< "0. Wyjscie" << endl;

	do {
		cout << "Twoj wybor: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
			reader = new Reader(name);
			isRead = true;
			break;
		case '2':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				reader->printTab();
			}
			break;
		case '3':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				vector<int> v;
				for (int i = 0; i < 6; i++) {
					v.push_back(i);
				}
				Population p;
				p.population = v;
				p.cost = 3;
				Population r;
				for (int i = 0; i < 6; i++) {
					r.population.push_back(5 - i);
				}
				r.cost = 5;
				//cout << genetic->sumCosts(v, reader->tab) << endl;
				genetic->oxCrossover(p, r, reader->tab);
			}
			break;
		case '0':
			break;
		default:
			cout << "Bledny wybor." << endl;
		}
	} while (choice != '0');

	delete reader;
    return 0;
}