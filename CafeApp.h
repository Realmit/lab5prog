#pragma once
#include <memory>
#include <stdexcept>
#include "CafeInfoActivity.h"
#include "MenuActivity.h"
#include "ReviewActivity.h"
#include "ReservationActivity.h"
#include "ContactHandler.h"

class CafeApp {
private:
    shared_ptr<CafeInfoActivity> cafe;      // shared_ptr для совместного владения
    unique_ptr<MenuActivity> menu;          // unique_ptr для эксклюзивного владения
    unique_ptr<ReviewActivity> reviews;     // unique_ptr для эксклюзивного владения
    unique_ptr<ReservationActivity> reservation; // unique_ptr для эксклюзивного владения
    unique_ptr<ContactHandler> contacts;    // unique_ptr для эксклюзивного владения

public:
    CafeApp() {
        cafe = std::make_shared<CafeInfoActivity>();
        menu = std::make_unique<MenuActivity>();
        reviews = std::make_unique<ReviewActivity>();
        reservation = std::make_unique<ReservationActivity>();
        contacts = std::make_unique<ContactHandler>(); // теперь auto-конфигурируется
    }
    void run() {
        try {
            // Обновление статуса кафе (14:00 - открыто)
            cafe->updateStatus(14);
            cafe->showInfo();
            CafeInfoActivity::showCafeCount();

            // Отображение владельца через дружественную функцию
            showOwner(*cafe);

            // Установка и отображение меню
            menu->setDailySpecial("Паста с трюфельным соусом");
            menu->showMenu();

            // Демонстрация перегрузки оператора []
            cout << "Первое блюдо меню: " << (*menu)[0] << endl;

            // Отображение контактов
            contacts->showContacts();
            contacts->openContact("WhatsApp"); // Открытие WhatsApp

            // Бронирование столика
            reservation->select("2025-11-15", "19:30", 6, "Семейный ужин");
            reservation->send(contacts->getLastOpenedContact());

            // Работа с отзывами
            reviews->editReview("Идеальное место для встреч с друзьями!");
            reviews->submitForCafe(*cafe);
            reviews->showAll();

            // Демонстрация перегрузки оператора вывода
            cout << "\n" << *reviews << endl;

            // Демонстрация перегрузки оператора ==
            ReviewActivity reviews2 = *reviews;
            if (*reviews == reviews2) {
                cout << "Отзывы идентичны!" << endl;
            }

            // Демонстрация перегрузки оператора +
            MenuActivity menu2;
            menu2.setDailySpecial("Десертный сет");
            MenuActivity combinedMenu = *menu + menu2;
            cout << "\nОбъединенное меню:\n" << combinedMenu << endl;

        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
};