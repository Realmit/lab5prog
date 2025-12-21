#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Activity.h"
#include "ReviewBase.h"
#include <sstream>

template<typename T>
class ReviewContainer : public Activity {
    static_assert(std::is_base_of_v<IReviewable, T>, "T must inherit from IReviewable");

private:
    std::vector<std::unique_ptr<T>> reviews;
    size_t maxCapacity;

public:
    ReviewContainer(const std::string& title, size_t capacity = 10)
        : Activity(title), maxCapacity(capacity) {}

    template<typename... Args>
    void emplaceReview(Args&&... args) {
        if (reviews.size() >= maxCapacity)
            throw std::runtime_error("Container capacity exceeded");
        reviews.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void showAllReviews() const {
        showTitle();
        if (reviews.empty()) {
            std::cout << "(Нет отзывов)\n";
            return;
        }
        for (const auto& r : reviews) {
            r->display();
        }
    }

    template<typename Predicate>
    std::vector<const T*> findReviews(Predicate pred) const {
        std::vector<const T*> res;
        for (const auto& r : reviews) {
            if (pred(*r)) res.push_back(r.get());
        }

        return res;
    }

    double calculateAverageRating() const {
        if (reviews.empty()) return 0.0;
        double sum = 0.0;
        for (const auto& r : reviews) sum += r->getRating();
        return sum / reviews.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const ReviewContainer<T>& rc) {
        os << rc.title << " (" << rc.reviews.size() << "/" << rc.maxCapacity << ")\n";
        for (const auto& r : rc.reviews) {
            os << "  ";
            r->display();
        }
        return os;
    }
};