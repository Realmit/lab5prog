#pragma once
#include <memory>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <sstream>
#include "CafeInfoActivity.h"
#include "MenuActivity.h"
#include "ReviewActivity.h"
#include "ReservationActivity.h"
#include "ContactHandler.h"
#include "ReviewContainer.h"
#include "StringReview.h"
#include "RatingReview.h"

class CafeApp {
private:
    std::shared_ptr<CafeInfoActivity> cafe;
    std::unique_ptr<MenuActivity> menu;
    std::unique_ptr<ReviewActivity> reviews;
    std::unique_ptr<ReservationActivity> reservation;
    std::unique_ptr<ContactHandler> contacts;
    std::vector<std::unique_ptr<Activity>> activities;

public:
    CafeApp() {
        cafe = std::make_shared<CafeInfoActivity>();
        menu = std::make_unique<MenuActivity>();
        reviews = std::make_unique<ReviewActivity>();
        reservation = std::make_unique<ReservationActivity>();
        contacts = std::make_unique<ContactHandler>();
    }

    void setupActivities() {
        activities.push_back(std::unique_ptr<Activity>(new CafeInfoActivity()));
        activities.push_back(std::unique_ptr<Activity>(new MenuActivity()));
        activities.push_back(std::unique_ptr<Activity>(new ReviewActivity()));
        activities.push_back(std::unique_ptr<Activity>(new ReservationActivity()));
    }

    void sortActivitiesByName() {
        std::sort(activities.begin(), activities.end(),
            [](const auto& a, const auto& b) {
                std::ostringstream oss_a, oss_b;
                a->print(oss_a);
                b->print(oss_b);
                return oss_a.str() < oss_b.str();
            });
    }

    Activity* findActivityByKeyword(const std::string& keyword) {
        auto it = std::find_if(activities.begin(), activities.end(),
            [&keyword](const auto& act) {
                std::ostringstream oss;
                act->print(oss);
                return oss.str().find(keyword) != std::string::npos;
            });
        return (it != activities.end()) ? it->get() : nullptr;
    }

    void demoTemplateContainers() {
        std::cout << "\n=== Демонстрация шаблонных контейнеров отзывов ===\n";

        ReviewContainer<StringReview> textReviews("Текстовые отзывы");
        textReviews.emplaceReview("Уютно и вкусно!", 4.9);
        textReviews.emplaceReview("Музыка слишком громкая", 3.5);
        textReviews.emplaceReview("Идеально для встреч!", 5.0);

        ReviewContainer<RatingReview> catReviews("Оценки по категориям");
        catReviews.emplaceReview(4.8, "Обслуживание");
        catReviews.emplaceReview(4.6, "Кухня");
        catReviews.emplaceReview(4.2, "Интерьер");
        catReviews.emplaceReview(5.0, "Парковка");

        std::cout << textReviews;
        std::cout << "\nСредний рейтинг (текстовые): "
            << textReviews.calculateAverageRating() << "/5.0\n";

        std::cout << catReviews;
        std::cout << "\nСредний рейтинг (по категориям): "
            << catReviews.calculateAverageRating() << "/5.0\n";

        auto highRated = textReviews.findReviews(
            [](const StringReview& r) { return r.getRating() >= 4.7; }
        );
        std::cout << "\nВысокооценённых отзывов (≥4.7): " << highRated.size() << "\n";
    }

    void run() {
        try {
            setupActivities();
            sortActivitiesByName();

            demoTemplateContainers();

            // Основной сценарий
            cafe->updateStatus(14);
            cafe->showInfo();
            CafeInfoActivity::showCafeCount();
            showOwner(*cafe);

            menu->setDailySpecial("Паста с трюфельным соусом");
            menu->showMenu(); 
            std::cout << "Первое блюдо меню: " << (*menu)[0] << std::endl;

            contacts->showContacts();
            contacts->openContact("WhatsApp");
            reservation->select("2025-11-15", "19:30", 6, "Семейный ужин");
            reservation->send(contacts->getLastOpenedContact());

            reviews->editReview("Идеальное место для встреч с друзьями!");
            reviews->submitForCafe(*cafe);
            reviews->showAll();
            std::cout << "\n" << *reviews << std::endl;

            ReviewActivity reviews2 = *reviews;
            if (*reviews == reviews2) { 
                std::cout << "Отзывы идентичны!" << std::endl;
            }

            MenuActivity menu2;
            menu2.setDailySpecial("Десертный сет");
            MenuActivity combinedMenu = *menu + menu2; 
            std::cout << "\nОбъединенное меню:\n" << combinedMenu << std::endl;

        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        catch (const std::string& s) {
            std::cout << "Ошибка: " << s << std::endl;
        }
    }
};