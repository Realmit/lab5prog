#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "CafeInfoActivity.h"
using namespace std;

class ReviewActivity : public Activity {
public:
    static const int MAX = 10;

private:
    unique_ptr<string[]> reviews;
    int count = 0;
    string userText;

public:
    ReviewActivity() : Activity("Отзывы") {
        reviews = make_unique<string[]>(MAX);
    }

    ReviewActivity(const ReviewActivity& other)
        : Activity(other), count(other.count), userText(other.userText) {
        reviews = make_unique<string[]>(MAX);
        for (int i = 0; i < count; ++i)
            reviews[i] = other.reviews[i];
    }

    void editReview(const string& text) {
        userText = text;
    }

    void submit() {
        if (userText.empty())
            throw runtime_error("Пустой отзыв!");
        if (count >= MAX)
            throw runtime_error("Хранилище отзывов заполнено!");
        reviews[count++] = userText;
        userText.clear();
    }

    void submitForCafe(const CafeInfoActivity& cafe) {
        if (userText.empty())
            throw runtime_error("Отзыв пуст!");
        reviews[count++] = cafe.cafeDetails.name + ": " + userText;
        userText.clear();
    }

    void showAll() const {
        showTitle();
        for (int i = 0; i < count; ++i)
            cout << "- " << reviews[i] << '\n';
    }

    void execute() const override {
        showAll();
    }

    friend ostream& operator<<(ostream& os, const ReviewActivity& r) {
        os << "Отзывы (" << r.count << "):\n";
        for (int i = 0; i < r.count; ++i)
            os << "- " << r.reviews[i] << '\n';
        return os;
    }
};