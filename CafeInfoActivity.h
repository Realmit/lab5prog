#pragma once
#include <iostream>
#include <string>
#include "Activity.h"
using namespace std;

class CafeInfoActivity : public Activity {
public:
    struct CafeDetails {
        string name;
        string address;
        int openHour;
        int closeHour;
        int capacity;
        string feature1;
        string feature2;
        string feature3;
    };

private:
    string ownerSecret = "ИП Смирнов";

public:
    static int cafesCreated;
    static CafeDetails cafeDetails;
    string currentStatusText;

    CafeInfoActivity() : Activity("Информация о кафе") {
        cafesCreated++;
    }

    CafeInfoActivity(const CafeInfoActivity& other)
        : Activity(other), currentStatusText(other.currentStatusText) {}

    void updateStatus(int hour) {
        currentStatusText = (hour >= cafeDetails.openHour && hour < cafeDetails.closeHour)
            ? "Открыто" : "Закрыто";
    }

    void showInfo() const {
        showTitle();
        cout << "Название: " << cafeDetails.name << '\n';
        cout << "Адрес: " << cafeDetails.address << '\n';
        cout << "Время работы: " << cafeDetails.openHour << ":00 – "
            << cafeDetails.closeHour << ":00\n";
        cout << "Вместимость: " << cafeDetails.capacity << " гостей\n";
        cout << "Особенности:\n";
        cout << "- " << cafeDetails.feature1 << '\n';
        cout << "- " << cafeDetails.feature2 << '\n';
        cout << "- " << cafeDetails.feature3 << '\n';
        cout << "Статус: " << currentStatusText << '\n';
    }

    static void showCafeCount() {
        cout << "Создано объектов CafeInfoActivity: " << cafesCreated << '\n';
    }

    friend void showOwner(const CafeInfoActivity& cafe);

    void execute() const override {
        showInfo();
    }
};

int CafeInfoActivity::cafesCreated = 0;
CafeInfoActivity::CafeDetails CafeInfoActivity::cafeDetails = {
    "Кафе Чинар",
    "пр. Центральный, 42",
    10, 23, 75,
    "Живая музыка по выходным",
    "Бесплатная парковка",
    "Терраса на крыше"
};

void showOwner(const CafeInfoActivity& cafe) {
    cout << "Секретный владелец кафе: " << cafe.ownerSecret << '\n';
}