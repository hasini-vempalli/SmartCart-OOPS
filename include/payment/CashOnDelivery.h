#ifndef CASH_ON_DELIVERY_H
#define CASH_ON_DELIVERY_H

#include "Payment.h"
#include <string>

using namespace std;

class CashOnDelivery : public Payment
{
public:
    bool pay(double amount) override;

    string getPaymentMethod() const override;
};

#endif