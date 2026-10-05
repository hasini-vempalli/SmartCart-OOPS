#include "auth/Admin.h"
#include <iostream>

using namespace std;

Admin::Admin() : User() {
}

Admin::Admin(string id, string name, string username,
             string password, string phone, string address)
    : User(id, name, username, password, phone, address) {
}

void Admin::displayProfile() const {
    cout << "===== ADMIN PROFILE =====" << endl;

    cout << "Admin ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Username: " << username << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
}