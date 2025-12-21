#pragma once
#include "ReviewBase.h"
#include <string>

class StringReview : public IReviewable {
    std::string text;
    double rating;

public:
    StringReview(const std::string& text, double rating)
        : text(text), rating(rating) {}

    std::string getReviewText() const override { return text; }
    double getRating() const override { return rating; }
    void display() const override {
        std::cout << "Текст: \"" << text << "\", Рейтинг: " << rating << "/5.0" << std::endl;
    }
};