// ReviewActivity.h
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "CafeInfoActivity.h"

class ReviewActivity : public Activity {
public:
    static const int MAX = 10;
    static const std::string templates[5];

private:
    std::unique_ptr<std::string[]> reviews;

public:
    int count;
    std::string userText;

    ReviewActivity()
        : Activity("Отзывы"), count(0), userText("") {
        reviews = std::make_unique<std::string[]>(MAX);
    }

    ReviewActivity(const ReviewActivity& other)
        : Activity(other.title), count(other.count), userText(other.userText) {
        reviews = std::make_unique<std::string[]>(MAX);
        for (int i = 0; i < other.count; i++)
            reviews[i] = other.reviews[i];
    }

    void editReview(const std::string& text) {
        userText = text;
    }

    void submit() {
        if (userText.empty())
            throw std::string("Пустой отзыв!");
        if (count >= MAX)
            throw std::string("Хранилище отзывов заполнено!");
        reviews[count++] = userText;
        userText = "";
    }

    void submitForCafe(const CafeInfoActivity& cafe) {
        if (userText.empty())
            throw std::string("Отзыв пуст!");
        reviews[count++] = cafe.cafeDetails.name + ": " + userText;
        userText = "";
    }

    void showAll() const {
        showTitle();
        for (int i = 0; i < count; i++)
            std::cout << "- " << reviews[i] << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const ReviewActivity& r) {
        os << "Отзывы (" << r.count << "):\n";
        for (int i = 0; i < r.count; i++)
            os << "- " << r.reviews[i] << std::endl;
        return os;
    }

    ReviewActivity& operator+=(const std::string& review) {
        if (count < MAX) reviews[count++] = review;
        return *this;
    }


    bool operator==(const ReviewActivity& other) const {
        if (count != other.count) return false;
        for (int i = 0; i < count; i++) {
            if (reviews[i] != other.reviews[i]) return false;
        }
        return true;
    }
};

const std::string ReviewActivity::templates[5] = {
    "Отлично!",
    "Вкусно!",
    "Медленно",
    "Хорошо",
    "Уютно"
};