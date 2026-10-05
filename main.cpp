#include <iostream>
#include <string>
#include <cctype>
#include "services/AuthService.h"

using namespace std;

bool isValidPhone(const string& phone) {

    if (phone.length() != 10) {
        return false;
    }

    for (char ch : phone) {
        if (!isdigit(ch)) {
            return false;
        }
    }

    return true;
}

int main() {

    AuthService auth;

    int choice;

    while (true) {

        cout << "\n===== SMARTCART =====" << endl;
        cout << "1. Register Customer" << endl;
        cout << "2. Customer Login" << endl;
        cout << "3. Admin Login" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {

            string id, name, username, password, phone, address;

            cout << "\n===== CUSTOMER REGISTRATION =====" << endl;

            cout << "Enter Customer ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Username: ";
            cin >> username;

            if (auth.usernameExists(username)) {
                cout << "Username already exists!" << endl;
                continue;
            }

            while (true) {

            cout << "Enter Password: ";
            cin >> password;

            if (!password.empty()) {
                break;
            }

            cout << "Password cannot be empty!\n";
            }

            while (true) {

            cout << "Enter Phone: ";
            cin >> phone;

            if (isValidPhone(phone)) {
                break;
            }

            cout << "Invalid phone number! "
                << "Enter exactly 10 digits.\n";
            }

            cout << "Enter Address: ";
            cin >> address;

            Customer customer(
                id,
                name,
                username,
                password,
                phone,
                address
            );

            if (auth.registerCustomer(customer)) {
                cout << "\nRegistration successful!" << endl;
            }
            else {
                cout << "\nRegistration failed!" << endl;
            }
        }

        else if (choice == 2) {

            string username, password;

            cout << "\n===== CUSTOMER LOGIN =====" << endl;

            cout << "Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            Customer* customer =
                auth.loginCustomer(username, password);

            if (customer != nullptr) {

                cout << "\nLogin successful!" << endl;

                int customerChoice;

                while (true) {

    cout << "\n===== CUSTOMER MENU =====" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. Update Profile" << endl;
    cout << "3. Logout" << endl;
    cout << "Enter choice: ";

    int customerChoice;
    cin >> customerChoice;

    if (customerChoice == 1) {

        customer->displayProfile();
    }

    else if (customerChoice == 2) {

        int updateChoice;

        cout << "\n===== UPDATE PROFILE =====" << endl;
        cout << "1. Update Name" << endl;
        cout << "2. Update Phone" << endl;
        cout << "3. Update Address" << endl;
        cout << "Enter choice: ";
        cin >> updateChoice;

        if (updateChoice == 1) {

            string newName;

            cout << "Enter new name: ";
            cin >> newName;

            customer->setName(newName);

            cout << "Name updated successfully!" << endl;
        }

        else if (updateChoice == 2) {

            string newPhone;

            cout << "Enter new phone: ";
            cin >> newPhone;

            customer->setPhone(newPhone);

            cout << "Phone updated successfully!" << endl;
        }

        else if (updateChoice == 3) {

            string newAddress;

            cout << "Enter new address: ";
            cin >> newAddress;

            customer->setAddress(newAddress);

            cout << "Address updated successfully!" << endl;
        }

        else {

            cout << "Invalid choice!" << endl;
        }
    }

    else if (customerChoice == 3) {

        cout << "Logged out successfully." << endl;
        break;
    }

    else {

        cout << "Invalid choice!" << endl;
    }
}

            }
            else {
                cout << "\nInvalid username or password!" << endl;
            }
        }

        else if (choice == 3) {

            string username, password;

            cout << "\n===== ADMIN LOGIN =====" << endl;

            cout << "Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            Admin* admin =
                auth.loginAdmin(username, password);

            if (admin != nullptr) {
                cout << "\nAdmin login successful!" << endl;
                admin->displayProfile();
            }
            else {
                cout << "\nInvalid admin username or password!" << endl;
            }
        }

        else if (choice == 4) {

            cout << "Thank you for using SmartCart!" << endl;
            break;
        }

        else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}