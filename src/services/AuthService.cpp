#include "services/AuthService.h"


// ============================================================
// CONSTRUCTOR
// ============================================================

AuthService::AuthService()
{
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


// ============================================================
// CHECK USERNAME
// ============================================================

bool AuthService::usernameExists(
    const string& username
) const
{
    // Check customers
    for (const Customer& customer : customers)
    {
        if (customer.getUsername() == username)
        {
            return true;
        }
    }

    // Check admins
    for (const Admin& admin : admins)
    {
        if (admin.getUsername() == username)
        {
            return true;
        }
    }

    return false;
}


// ============================================================
// CHECK USER ID
// ============================================================

bool AuthService::userIdExists(
    const string& userId
) const
{
    // Check customer IDs
    for (const Customer& customer : customers)
    {
        if (customer.getUserId() == userId)
        {
            return true;
        }
    }

    // Check admin IDs
    for (const Admin& admin : admins)
    {
        if (admin.getUserId() == userId)
        {
            return true;
        }
    }

    return false;
}


// ============================================================
// REGISTER CUSTOMER
// ============================================================

bool AuthService::registerCustomer(
    const Customer& customer
)
{
    // Check duplicate username
    if (usernameExists(customer.getUsername()))
    {
        return false;
    }

    // Check duplicate user ID
    if (userIdExists(customer.getUserId()))
    {
        return false;
    }

    // Add customer
    customers.push_back(customer);

    return true;
}


// ============================================================
// CUSTOMER LOGIN
// ============================================================

Customer* AuthService::loginCustomer(
    const string& username,
    const string& password
)
{
    for (Customer& customer : customers)
    {
        if (
            customer.getUsername() == username &&
            customer.getPassword() == password
        )
        {
            return &customer;
        }
    }

    return nullptr;
}


// ============================================================
// ADMIN LOGIN
// ============================================================

Admin* AuthService::loginAdmin(
    const string& username,
    const string& password
)
{
    for (Admin& admin : admins)
    {
        if (
            admin.getUsername() == username &&
            admin.getPassword() == password
        )
        {
            return &admin;
        }
    }

    return nullptr;
}