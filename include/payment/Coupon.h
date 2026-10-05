#ifndef COUPON_H
#define COUPON_H

#include <string>

using namespace std;

class Coupon
{
private:
    string code;
    double discountPercentage;
    double fixedDiscount;
    double minimumAmount;
    string expiryDate;
    bool active;

public:
    Coupon();

    Coupon(
        string code,
        double discountPercentage,
        double fixedDiscount,
        double minimumAmount,
        string expiryDate,
        bool active
    );

    bool isValid(double amount) const;

    double calculateDiscount(double amount) const;

    double applyCoupon(double amount) const;

    string getCode() const;

    double getDiscountPercentage() const;

    double getFixedDiscount() const;

    double getMinimumAmount() const;

    string getExpiryDate() const;

    bool getActive() const;

    void setActive(bool active);
};

#endif