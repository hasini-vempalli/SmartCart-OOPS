#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

using namespace std;

class Payment
{
public:
    virtual bool pay(double amount) = 0;

    virtual string getPaymentMethod() const = 0;

    virtual ~Payment() = default;
};

#endif