#include <locale.h>
#include <Windows.h>

#include "lab.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    lab();
    return 0;
}