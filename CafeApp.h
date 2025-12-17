#pragma once
#include <memory>
#include <stdexcept>
#include "CafeInfoActivity.h"
#include "MenuActivity.h"
#include "PremiumMenuActivity.h"
#include "ReviewActivity.h"
#include "ReservationActivity.h"
#include "ContactHandler.h"

class CafeApp {
private:
    shared_ptr<CafeInfoActivity> cafe;
    unique_ptr<MenuActivity> menu;
    unique_ptr<ReviewActivity> reviews;
    unique_ptr<ReservationActivity> reservation;
    unique_ptr<ContactHandler> contacts;

public:
    CafeApp() {
        cafe = make_shared<CafeInfoActivity>();
        menu = make_unique<MenuActivity>();
        reviews = make_unique<ReviewActivity>();
        reservation = make_unique<ReservationActivity>();
        contacts = make_unique<ContactHandler>();
    }

    void run() {
        try {
            cafe->updateStatus(14);
            cafe->showInfo();
            CafeInfoActivity::showCafeCount();
            showOwner(*cafe);

            // Демонстрация полиморфизма через указатели базового типа.
            unique_ptr<Activity> stdMenu = make_unique<MenuActivity>("Стандартное меню", "Паста с трюфелем");
            unique_ptr<Activity> premMenu = make_unique<PremiumMenuActivity>("Премиум-меню", "Шеф Иванов", "Омар в вине");

            // Вызов через базовый указатель: в runtime вызываются методы производных классов.
            stdMenu->runSafely();   // → MenuActivity::showTitle() + execute()
            premMenu->runSafely();  // → PremiumMenuActivity::showTitle() + execute()

            // Клонирование: демонстрация shallow vs deep.
            // MenuActivity::clone() → shallow (поля trivial), PremiumMenuActivity::clone() → deep (копирует chefSignature).
            auto clonedMenu = menu->clone();
            clonedMenu->setDailySpecial("Клон: Трюфельная паста");
            cout << "Оригинал:\n";
            menu->execute();
            cout << "Клон:\n";
            clonedMenu->execute();

            contacts->showContacts();
            contacts->openContact("WhatsApp");

            reservation->select("2025-11-15", "19:30", 6, "Семейный ужин");
            reservation->send(contacts->getLastOpenedContact());

            reviews->editReview("Идеальное место!");
            reviews->submitForCafe(*cafe);
            reviews->showAll();
            cout << "\n" << *reviews << endl;

        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
};