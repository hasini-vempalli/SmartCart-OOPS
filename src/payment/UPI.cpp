#include "../../include/payment/UPI.h"

#include <iostream>

using namespace std;

UPI::UPI()
{
    cout << "\n========== UPI PAYMENT ==========\n";

    cout << "Enter UPI ID: ";
    cin >> upiId;
}

bool UPI::pay(double amount)
{
    cout << "\nAmount: Rs. " << amount << endl;

    cout << "Processing UPI payment...\n";

    cout << "UPI payment successful!\n";

    return true;
}

string UPI::getPaymentMethod() const
{
    return "UPI";
}