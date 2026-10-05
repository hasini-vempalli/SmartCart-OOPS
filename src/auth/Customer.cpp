#include "auth/Customer.h"
#include <iostream>

using namespace std;

Customer::Customer() : User() {
}

Customer::Customer(string id, string name, string username,
                   string password, string phone, string address)
    : User(id, name, username, password, phone, address) {
}

void Customer::displayProfile() const {
    cout << "===== CUSTOMER PROFILE =====" << endl;

    cout << "Customer ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Username: " << username << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
}