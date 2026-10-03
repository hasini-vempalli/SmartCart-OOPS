#ifndef CARD_H
#define CARD_H

#include "Payment.h"
#include <string>

using namespace std;

class Card : public Payment
{
private:
    string cardNumber;
    string cvv;

public:
    Card();

    bool pay(double amount) override;

    string getPaymentMethod() const override;
};

#endif