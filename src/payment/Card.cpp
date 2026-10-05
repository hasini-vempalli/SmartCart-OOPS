#include "../../include/payment/Card.h"

#include <iostream>

using namespace std;

Card::Card()
{
    cout << "\n========== CARD PAYMENT ==========\n";

    cout << "Enter card number: ";
    cin >> cardNumber;

    cout << "Enter CVV: ";
    cin >> cvv;
}

bool Card::pay(double amount)
{
    cout << "\nAmount: Rs. " << amount << endl;

    cout << "Processing card payment...\n";

    cout << "Card payment successful!\n";

    return true;
}

string Card::getPaymentMethod() const
{
    return "Card";
}