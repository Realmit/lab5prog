#pragma once
#include <string>
#include <iostream>

class IReviewable {
public:
    virtual ~IReviewable() = default;
    virtual std::string getReviewText() const = 0;
    virtual double getRating() const = 0;
    virtual void display() const = 0;
};