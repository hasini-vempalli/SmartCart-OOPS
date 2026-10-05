#ifndef UPI_H
#define UPI_H

#include "Payment.h"
#include <string>

using namespace std;

class UPI : public Payment
{
private:
    string upiId;

public:
    UPI();

    bool pay(double amount) override;

    string getPaymentMethod() const override;
};

#endif