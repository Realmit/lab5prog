#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include "Activity.h" 

class ReservationActivity : public Activity {  
public:
    struct Reservation {
        std::string date;
        std::string time;
        int guests;
        std::string type;

        friend bool operator==(const Reservation& a, const Reservation& b) {
            return a.date == b.date && a.time == b.time &&
                a.guests == b.guests && a.type == b.type;
        }

        friend std::ostream& operator<<(std::ostream& os, const Reservation& r) {
            os << r.date << " " << r.time
                << ", гостей: " << r.guests
                << ", тип: " << r.type;
            return os;
        }
    };

    static const std::string availableTimeSlots[6];
    Reservation selected;

    ReservationActivity() : Activity("Бронирование") {} 

    void select(const std::string& date,
        const std::string& time,
        int guests,
        const std::string& type) {
        bool validTime = false;
        for (const auto& slot : availableTimeSlots) {
            if (slot == time) {
                validTime = true;
                break;
            }
        }

        if (!validTime)
            throw std::invalid_argument("Неверное время: " + time);

        selected = { date, time, guests, type };
        std::cout << "Бронь выбрана: " << date << " " << time << " (" << type << ")" << std::endl;
    }

    void send(const std::string& contact) const {
        std::cout << "Отправляем бронь через " << contact << "..." << std::endl;
        std::cout << "Дата: " << selected.date << std::endl;
        std::cout << "Время: " << selected.time << std::endl;
        std::cout << "Гостей: " << selected.guests << std::endl;
        std::cout << "Тип: " << selected.type << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const ReservationActivity& r) {
        os << "Текущая бронь:\n" << r.selected;
        return os;
    }
};

const std::string ReservationActivity::availableTimeSlots[6] = {
    "11:00", "13:30", "15:00", "17:30", "19:30", "21:00"
};