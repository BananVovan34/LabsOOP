#include "politobjects.h"

int lab() {
	const string FILE_PATH = "inputStates.txt";

	int n = getStatesCount(FILE_PATH);

	if (n != -1) {
		politObjects states(FILE_PATH);

		cout << states;

		bool exit = false;

		while (!(exit)) {
			switch (getUserAction()) {
			case 1:
				states.calculationOfAmountOf("area", "��������_�������");
				states.calculationOfAmountOf("population", "��������_�������");

				break;

			case 2:
				states.findMaxOf("area", "���������");
				states.findMaxOf("population", "���������");

				break;

			case 3:
				newRecord(states);
				cout << states;

				break;

			case 4:
				states.deleteRecord();
				cout << states;

				break;

			case 5:
				cout << "\n[ ������� ] ����� �� ���������...";
				exit = true;

				break;

			default:
				cerr << "\n[ ������ ] ������������ �������� action" << endl << endl;
			}
		}

		states.~listStates();

		return 0;
	}
	else {
		cerr << "\n[ ������ ] ������������ �������� ���������� ��������: " << n << endl;

		return 1;
	}
}