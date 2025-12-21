#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class ReservationActivity {
public:
    struct Reservation {
        string date;
        string time;
        int guests;
        string type;

        // Перегрузка оператора == для сравнения бронирований
        friend bool operator==(const Reservation& a, const Reservation& b) {
            return a.date == b.date && a.time == b.time &&
                a.guests == b.guests && a.type == b.type;
        }

        // Перегрузка оператора вывода для Reservation
        friend ostream& operator<<(ostream& os, const Reservation& r) {
            os << r.date << " " << r.time
                << ", гостей: " << r.guests
                << ", тип: " << r.type;
            return os;
        }
    };

    static const string availableTimeSlots[6];
    Reservation selected;

    // Конструктор по умолчанию
    ReservationActivity() : selected() {}

    // Выбор бронирования с валидацией времени
    void select(const string& date,
        const string& time,
        int guests,
        const string& type) {
        bool validTime = false;
        for (const auto& slot : availableTimeSlots) {
            if (slot == time) {
                validTime = true;
                break;
            }
        }


        if (!validTime)
            throw invalid_argument("Неверное время: " + time);

        selected = { date, time, guests, type };
        cout << "Бронь выбрана: " << date << " " << time << " (" << type << ")" << endl;
    }
    // Отправка бронирования через указанный контакт
    void send(const string& contact) const {
        cout << "Отправляем бронь через " << contact << "..." << endl;
        cout << "Дата: " << selected.date << endl;
        cout << "Время: " << selected.time << endl;
        cout << "Гостей: " << selected.guests << endl;
        cout << "Тип: " << selected.type << endl;
    }

    // Перегрузка оператора вывода для всего ReservationActivity
    friend ostream& operator<<(ostream& os, const ReservationActivity& r) {
        os << "Текущая бронь:\n" << r.selected;
        return os;
    }
};

// Инициализация доступных временных слотов
const string ReservationActivity::availableTimeSlots[6] = {
    "11:00", "13:30", "15:00", "17:30", "19:30", "21:00"
};