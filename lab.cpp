#include "states.h"

int lab() {
	const string FILE_PATH = "inputStates.txt";

	int n = getStatesCount(FILE_PATH);

	if (n != -1) {
		listStates states(FILE_PATH);

		states.dataOutput();

		bool exit = false;

		while (!(exit)) {
			int action = getUserAction();

			switch (action) {
			case 1:
				states.calculationOfAmountOf("area", "��������_�������");
				states.calculationOfAmountOf("population", "��������_�������");

				break;

			case 2:
				states.findMaxOf("area", "���������");
				states.findMaxOf("population", "���������");

				break;

			case 3:
				states.newRecord();
				states.dataOutput();

				break;

			case 4:
				states.deleteRecord();
				states.dataOutput();

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