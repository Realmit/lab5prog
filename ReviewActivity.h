#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "CafeInfoActivity.h"
using namespace std;

class ReviewActivity : public Activity {
public:
    static const int MAX = 10;
    static const string templates[5];

private:
    unique_ptr<string[]> reviews; // Использование unique_ptr для управления памятью

public:
    int count;
    string userText;

    // Конструктор по умолчанию
    ReviewActivity()
        : Activity("Отзывы"), count(0), userText("") {
        reviews = make_unique<string[]>(MAX);
    }

    // Конструктор копирования с использованием смарт-указателей
    ReviewActivity(const ReviewActivity& other)
        : Activity(other.title),
        count(other.count),
        userText(other.userText) {
        reviews = make_unique<string[]>(MAX);
        for (int i = 0; i < other.count; i++)
            reviews[i] = other.reviews[i];
    }

    // Редактирование отзыва
    void editReview(const string& text) {
        this->userText = text;
    }

    // Отправка отзыва
    void submit() {
        if (userText.empty())
            throw string("Пустой отзыв!");

        if (count >= MAX)
            throw string("Хранилище отзывов заполнено!");

        reviews[count++] = userText;
        userText = "";
    }

    // Отправка отзыва для конкретного кафе
    void submitForCafe(const CafeInfoActivity& cafe) {
        if (userText.empty())
            throw string("Отзыв пуст!");

        reviews[count++] = cafe.cafeDetails.name + ": " + userText;
        userText = "";
    }

    // Отображение всех отзывов
    void showAll() const {
        showTitle();
        for (int i = 0; i < count; i++)
            cout << "- " << reviews[i] << endl;
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const ReviewActivity& r) {
        os << "Отзывы (" << r.count << "):\n";
        for (int i = 0; i < r.count; i++)
            os << "- " << r.reviews[i] << endl;
        return os;
    }

    // Перегрузка оператора += для добавления отзыва
    ReviewActivity& operator+=(const string& review) {
        if (count < MAX) {
            reviews[count++] = review;
        }
        return *this;
    }

    // Перегрузка оператора == для сравнения отзывов
    bool operator==(const ReviewActivity& other) const {
        if (count != other.count) return false;
        for (int i = 0; i < count; i++) {
            if (reviews[i] != other.reviews[i]) return false;
        }
        return true;
    }
};

// Инициализация статического массива шаблонов
const string ReviewActivity::templates[5] = {
    "Отлично!",
    "Вкусно!",
    "Медленно",
    "Хорошо",
    "Уютно"
};