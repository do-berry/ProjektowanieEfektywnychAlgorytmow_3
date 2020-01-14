#include <iostream>
#include <climits>
#include <windows.h>
#include "Reader.h"
#include "Genetic.h"
#include <chrono> 
#include <cstdlib>
#include <ctime>

using namespace std::chrono;
using namespace std;

int main()
{
	srand(time(NULL));

	char choice;
	Reader * reader;
	Genetic * genetic = new Genetic(10, 10, 10, 50, 50);
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
			else {/*
				int * child = new int[10], * solution = new int[10];
				for (int i = 0; i < 10; i++) {
					child[i] = i;
				}
				int * dupa = new int[10];
				for (int i = 0; i < 10; i++) {
					dupa[i] = child[9 - i];
				}

				genetic->printPath(child);
				genetic->printPath(dupa);

				genetic->oxCrossover(child, dupa);*/
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