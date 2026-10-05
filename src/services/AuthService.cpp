#include "services/AuthService.h"

AuthService::AuthService() {

    Admin admin(
        "A001",
        "Administrator",
        "admin",
        "admin123",
        "9999999999",
        "SmartCart"
    );

    admins.push_back(admin);
}

bool AuthService::usernameExists(const string& username) const {

    for (const Customer& customer : customers) {
        if (customer.getUsername() == username) {
            return true;
        }
    }

    for (const Admin& admin : admins) {
        if (admin.getUsername() == username) {
            return true;
        }
    }

    return false;
}


bool AuthService::registerCustomer(const Customer& customer) {

    if (usernameExists(customer.getUsername())) {
        return false;
    }

    customers.push_back(customer);

    return true;
}


Customer* AuthService::loginCustomer(const string& username,
                                     const string& password) {

    for (Customer& customer : customers) {

        if (customer.getUsername() == username &&
            customer.getPassword() == password) {

            return &customer;
        }
    }

    return nullptr;
}


Admin* AuthService::loginAdmin(const string& username,
                               const string& password) {

    for (Admin& admin : admins) {

        if (admin.getUsername() == username &&
            admin.getPassword() == password) {

            return &admin;
        }
    }

    return nullptr;
}