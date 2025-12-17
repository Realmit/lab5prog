#pragma once
#include <iostream>
#include <string>
using namespace std;

class Activity {
protected:
    string title;
public:
    Activity(const string& title) : title(title) {}

    virtual void showTitle() const {
        cout << "=== " << title << " ===" << endl;
    }

    virtual ~Activity() = default;

    // Виртуальный оператор вывода для полиморфизма
    virtual ostream& print(ostream& os) const {
        os << "Активность: " << title;
        return os;
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Activity& activity) {
        return activity.print(os);
    }
};