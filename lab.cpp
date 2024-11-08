#include "politobjects.h"

int lab() {
	const string FILE_PATH = "inputStates.txt";

	if (getObjectsCount(FILE_PATH) != -1) {
		politObjects listOfObjects(FILE_PATH);

		cout << listOfObjects;

		bool exit = false;

		while (!(exit)) {
			switch (getUserAction()) {
			case 1:
				listOfObjects.calculationOfAmountOf("area", "��������_�������");
				listOfObjects.calculationOfAmountOf("population", "��������_�������");

				break;

			case 2:
				listOfObjects.findMaxOf("area", "���������");
				listOfObjects.findMaxOf("population", "���������");

				break;

			case 3:
				newRecord(listOfObjects);
				cout << listOfObjects;

				break;

			case 4:
				listOfObjects.deleteRecord();
				cout << listOfObjects;

				break;

			case 5:
				listOfObjects.saveData();

				break;

			case 6:
				listOfObjects.searchByName();

				break;

			case 7:
				cout << "\n[ ������� ] ����� �� ���������...";
				exit = true;

				break;

			default:
				cerr << "\n[ ������ ] ������������ �������� action" << endl << endl;
			}
		}

		listOfObjects.~politObjects();

		return 0;
	}
	else {
		cerr << "\n[ ������ ] ������������ �������� ���������� ��������" << endl;

		return 1;
	}
}