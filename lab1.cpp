#include "states.h"

int lab1() {
	const string FILE_PATH = "inputStates.txt";

	int numStates = getStatesCount(FILE_PATH);

	if (numStates != -1) {
		State* states = new State[numStates];

		readingFromFile(states, numStates, FILE_PATH);

		dataOutput(states, numStates);

		calculationOfAmountOf(states, numStates, "area", "��������_�������");
		calculationOfAmountOf(states, numStates, "population", "��������_�������");

		findMaxOf(states, numStates, "area", "���������");
		findMaxOf(states, numStates, "population", "���������");

		delete[] states;

		return 0;
	}
	else {
		cerr << "[ ������ ] ������������ �������� numStates " << numStates << endl;

		return 1;
	}
}