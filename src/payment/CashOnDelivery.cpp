#include "../../include/payment/CashOnDelivery.h"

#include <iostream>

using namespace std;

bool CashOnDelivery::pay(double amount)
{
    cout << "\n========== CASH ON DELIVERY ==========\n";

    cout << "Amount: Rs. " << amount << endl;

    cout << "Cash on Delivery selected.\n";

    cout << "Payment will be collected upon delivery.\n";

    return true;
}

string CashOnDelivery::getPaymentMethod() const
{
    return "Cash on Delivery";
}