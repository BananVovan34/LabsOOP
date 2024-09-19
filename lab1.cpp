#include "states.h"

int lab1() {
	const string FILE_PATH = "inputStates.txt";

	int numStates = getStatesCount(FILE_PATH);

	if (numStates != -1) {
		State* states = new State[numStates];

		readingFromFile(states, numStates, FILE_PATH);

		dataOutput(states, numStates);

		calculationOfAmountOf(states, numStates, "area", "Северная_Америка");
		calculationOfAmountOf(states, numStates, "population", "Северная_Америка");

		findMaxOf(states, numStates, "area", "Испанский");
		findMaxOf(states, numStates, "population", "Испанский");

		delete[] states;

		return 0;
	}
	else {
		cerr << "[ Ошибка ] Некорректный параметр numStates " << numStates << endl;

		return 1;
	}
}