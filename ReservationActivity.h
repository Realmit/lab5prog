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

        friend bool operator==(const Reservation& a, const Reservation& b) {
            return a.date == b.date && a.time == b.time &&
                a.guests == b.guests && a.type == b.type;
        }

        friend ostream& operator<<(ostream& os, const Reservation& r) {
            os << r.date << ' ' << r.time
                << ", гостей: " << r.guests
                << ", тип: " << r.type;
            return os;
        }
    };

    static const string availableTimeSlots[6];
    Reservation selected;

    ReservationActivity() = default;

    void select(const string& date, const string& time, int guests, const string& type) {
        bool ok = false;
        for (const auto& slot : availableTimeSlots)
            if (slot == time) { ok = true; break; }
        if (!ok)
            throw invalid_argument("Неверное время: " + time);
        selected = { date, time, guests, type };
        cout << "Бронь выбрана: " << date << " " << time << " (" << type << ")\n";
    }

    void send(const string& contact) const {
        cout << "Отправка брони через " << contact << "...\n";

        cout << selected.date << ' ' << selected.time
            << ", гостей: " << selected.guests
            << ", тип: " << selected.type << '\n';
    }
};

const string ReservationActivity::availableTimeSlots[6] = {
    "11:00", "13:30", "15:00", "17:30", "19:30", "21:00"
};