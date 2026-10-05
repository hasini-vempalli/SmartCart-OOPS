#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string userId;
    string name;
    string username;
    string password;
    string phone;
    string address;

public:
    User();

    User(string id, string name, string username,
         string password, string phone, string address);

    string getUserId() const;
    string getName() const;
    string getUsername() const;
    string getPassword() const;
    string getPhone() const;
    string getAddress() const;

    void setName(string name);
    void setPhone(string phone);
    void setAddress(string address);

    virtual void displayProfile() const;

    virtual ~User();
};

#endif