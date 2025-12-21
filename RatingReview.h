#pragma once
#include "ReviewBase.h"
#include <string>

class RatingReview : public IReviewable {
    double rating;

    std::string category;

public:
    RatingReview(double rating, const std::string& category)
        : rating(rating), category(category) {}

    std::string getReviewText() const override { return category; }
    double getRating() const override { return rating; }
    void display() const override {
        std::cout << "Категория: \"" << category << "\", Рейтинг: " << rating << "/5.0" << std::endl;
    }
};