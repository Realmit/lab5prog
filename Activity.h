#pragma once
#include <iostream>
#include <string>

class Activity {
protected:
    std::string title;

public:
    Activity(const std::string& title) : title(title) {}

    virtual void showTitle() const {
        std::cout << "=== " << title << " ===" << std::endl;
    }

    virtual ~Activity() = default;

    virtual std::ostream& print(std::ostream& os) const {
        os << "Активность: " << title;
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const Activity& activity) {
        return activity.print(os);
    }
};