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
    string ownerSecret = "ИП Смирнов"; // Для friend-функции

public:
    static int cafesCreated; // статическое поле для подсчета объектов

    static CafeDetails cafeDetails; // статическая информация о кафе
    string currentStatusText;

    // Конструктор по умолчанию
    CafeInfoActivity() : Activity("Информация о кафе") {
        cafesCreated++;
    }

    // Конструктор копирования с вызовом базового конструктора
    CafeInfoActivity(const CafeInfoActivity& other)
        : Activity(other.title),
        currentStatusText(other.currentStatusText) {
        // Статические данные не копируются
    }

    // Обновление статуса кафе
    void updateStatus(int hour) {
        this->currentStatusText = (hour >= cafeDetails.openHour && hour < cafeDetails.closeHour)
            ? "Открыто" : "Закрыто";
    }

    // Отображение информации о кафе
    void showInfo() const {
        showTitle();
        cout << "Название: " << cafeDetails.name << endl;
        cout << "Адрес: " << cafeDetails.address << endl;
        cout << "Время работы: " << cafeDetails.openHour << ":00 – "
            << cafeDetails.closeHour << ":00" << endl;
        cout << "Вместимость: " << cafeDetails.capacity << " гостей" << endl;
        cout << "Особенности:" << endl;
        cout << "- " << cafeDetails.feature1 << endl;
        cout << "- " << cafeDetails.feature2 << endl;
        cout << "- " << cafeDetails.feature3 << endl;
        cout << "Статус: " << currentStatusText << endl;
    }

    // Статический метод для отображения количества созданных кафе
    static void showCafeCount() {
        cout << "Создано объектов CafeInfoActivity: " << cafesCreated << endl;
    }

    // Дружественная функция для доступа к приватному полю
    friend void showOwner(const CafeInfoActivity& cafe);

    // Перегрузка оператора сравнения
    bool operator==(const CafeInfoActivity& other) const {
        return cafeDetails.name == other.cafeDetails.name &&
            cafeDetails.address == other.cafeDetails.address;
    }

    // Перегрузка оператора += для объединения особенностей
    CafeInfoActivity& operator+=(const string& feature) {
        if (cafeDetails.feature3.empty()) {
            cafeDetails.feature3 = feature;
        }
        else if (cafeDetails.feature2.empty()) {
            cafeDetails.feature2 = feature;
        }
        else if (cafeDetails.feature1.empty()) {
            cafeDetails.feature1 = feature;
        }
        return *this;
    }
};

// Инициализация статических членов
int CafeInfoActivity::cafesCreated = 0;
CafeInfoActivity::CafeDetails CafeInfoActivity::cafeDetails = {
    "Кафе Чинар",
    "пр. Центральный, 42",
    10, 23, 75,
    "Живая музыка по выходным",
    "Бесплатная парковка",
    "Терраса на крыше"
};

// Реализация дружественной функции
inline void showOwner(const CafeInfoActivity& cafe) {
    cout << "Секретный владелец кафе: " << cafe.ownerSecret << endl;
}