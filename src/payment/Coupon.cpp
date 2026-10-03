#include "../../include/payment/Coupon.h"

using namespace std;

Coupon::Coupon()
{
    code = "";
    discountPercentage = 0;
    fixedDiscount = 0;
    minimumAmount = 0;
    expiryDate = "";
    active = false;
}

Coupon::Coupon(
    string code,
    double discountPercentage,
    double fixedDiscount,
    double minimumAmount,
    string expiryDate,
    bool active
)
{
    this->code = code;
    this->discountPercentage = discountPercentage;
    this->fixedDiscount = fixedDiscount;
    this->minimumAmount = minimumAmount;
    this->expiryDate = expiryDate;
    this->active = active;
}

bool Coupon::isValid(double amount) const
{
    if (!active)
    {
        return false;
    }

    if (amount < minimumAmount)
    {
        return false;
    }

    return true;
}

double Coupon::calculateDiscount(double amount) const
{
    if (!isValid(amount))
    {
        return 0;
    }

    double discount = 0;

    if (discountPercentage > 0)
    {
        discount = amount * discountPercentage / 100.0;
    }
    else if (fixedDiscount > 0)
    {
        discount = fixedDiscount;
    }

    if (discount > amount)
    {
        discount = amount;
    }

    return discount;
}

double Coupon::applyCoupon(double amount) const
{
    double discount = calculateDiscount(amount);

    return amount - discount;
}

string Coupon::getCode() const
{
    return code;
}

double Coupon::getDiscountPercentage() const
{
    return discountPercentage;
}

double Coupon::getFixedDiscount() const
{
    return fixedDiscount;
}

double Coupon::getMinimumAmount() const
{
    return minimumAmount;
}

string Coupon::getExpiryDate() const
{
    return expiryDate;
}

bool Coupon::getActive() const
{
    return active;
}

void Coupon::setActive(bool active)
{
    this->active = active;
}