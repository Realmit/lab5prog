#include <iostream>
#include <windows.h>
#include "CafeApp.h"
using namespace std;

int main() {
    cout << "| Начало работы ЧИНАР |\n";
    CafeApp app;
    app.run();
    cout << "| Конец |\n";

    system("pause");
    return 0;
}