#include "auth/User.h"
#include <iostream>

using namespace std;

User::User() {
    userId = "";
    name = "";
    username = "";
    password = "";
    phone = "";
    address = "";
}

User::User(string id, string name, string username,
           string password, string phone, string address) {

    this->userId = id;
    this->name = name;
    this->username = username;
    this->password = password;
    this->phone = phone;
    this->address = address;
}

string User::getUserId() const {
    return userId;
}

string User::getName() const {
    return name;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getPhone() const {
    return phone;
}

string User::getAddress() const {
    return address;
}

void User::setName(string name) {
    this->name = name;
}

void User::setPhone(string phone) {
    this->phone = phone;
}

void User::setAddress(string address) {
    this->address = address;
}

void User::displayProfile() const {
    cout << "User ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Username: " << username << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
}

User::~User() {
}