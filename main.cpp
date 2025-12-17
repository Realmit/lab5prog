#include <iostream>
#include <windows.h>
#include "CafeApp.h"
using namespace std;

int main() {
    cout << "| Начало работы ЧИНАР |" << endl;
    CafeApp app;
    app.run();
    cout << "| Конец |" << endl;
    return 0;
}