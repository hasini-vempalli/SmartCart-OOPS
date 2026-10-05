#ifndef ADMIN_H
#define ADMIN_H

#include "auth/User.h"

class Admin : public User {
public:
    Admin();

    Admin(string id, string name, string username,
          string password, string phone, string address);

    void displayProfile() const override;
};

#endif