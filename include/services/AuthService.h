#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <vector>
#include <string>
#include "auth/Customer.h"
#include "auth/Admin.h"

using namespace std;

class AuthService {
private:
    vector<Customer> customers;
    vector<Admin> admins;

public:
    AuthService();
    
    bool usernameExists(const string& username) const;

    bool registerCustomer(const Customer& customer);

    Customer* loginCustomer(const string& username,
                            const string& password);

    Admin* loginAdmin(const string& username,
                      const string& password);
};

#endif