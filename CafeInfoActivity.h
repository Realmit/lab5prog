#pragma once
#include <iostream>
#include <string>
#include "Activity.h"

class CafeInfoActivity : public Activity {
public:
    struct CafeDetails {
        std::string name;
        std::string address;
        int openHour;
        int closeHour;
        int capacity;
        std::string feature1;
        std::string feature2;
        std::string feature3;
    };

private:
    std::string ownerSecret = "ИП Смирнов";

public:
    static int cafesCreated;
    static CafeDetails cafeDetails;
    std::string currentStatusText;

    CafeInfoActivity() : Activity("Информация о кафе") {
        cafesCreated++;
    }

    CafeInfoActivity(const CafeInfoActivity& other)
        : Activity(other.title), currentStatusText(other.currentStatusText) {}

    void updateStatus(int hour) {
        currentStatusText = (hour >= cafeDetails.openHour && hour < cafeDetails.closeHour)
            ? "Открыто" : "Закрыто";
    }

    void showInfo() const {
        showTitle();
        std::cout << "Название: " << cafeDetails.name << std::endl;
        std::cout << "Адрес: " << cafeDetails.address << std::endl;
        std::cout << "Время работы: " << cafeDetails.openHour << ":00 – "
            << cafeDetails.closeHour << ":00" << std::endl;
        std::cout << "Вместимость: " << cafeDetails.capacity << " гостей" << std::endl;
        std::cout << "Особенности:" << std::endl;
        std::cout << "- " << cafeDetails.feature1 << std::endl;
        std::cout << "- " << cafeDetails.feature2 << std::endl;
        std::cout << "- " << cafeDetails.feature3 << std::endl;
        std::cout << "Статус: " << currentStatusText << std::endl;
    }

    static void showCafeCount() {
        std::cout << "Создано объектов CafeInfoActivity: " << cafesCreated << std::endl;
    }

    friend void showOwner(const CafeInfoActivity& cafe);

    bool operator==(const CafeInfoActivity& other) const {
        return cafeDetails.name == other.cafeDetails.name &&
            cafeDetails.address == other.cafeDetails.address;
    }

    CafeInfoActivity& operator+=(const std::string& feature) {
        if (cafeDetails.feature3.empty()) cafeDetails.feature3 = feature;
        else if (cafeDetails.feature2.empty()) cafeDetails.feature2 = feature;
        else if (cafeDetails.feature1.empty()) cafeDetails.feature1 = feature;
        return *this;
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

inline void showOwner(const CafeInfoActivity& cafe) {
    std::cout << "Секретный владелец кафе: " << cafe.ownerSecret << std::endl;
}