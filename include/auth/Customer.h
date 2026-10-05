#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "auth/User.h"

class Customer : public User {
public:
    Customer();

    Customer(string id, string name, string username,
             string password, string phone, string address);

    void displayProfile() const override;
};

#endif