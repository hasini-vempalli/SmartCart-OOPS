

#include <iostream>
#include <string>
#include <cctype>

#include "services/AuthService.h"

#include "payment/Payment.h"
#include "payment/Card.h"
#include "payment/UPI.h"
#include "payment/CashOnDelivery.h"
#include "payment/Coupon.h"

using namespace std;


// ======================================================
// PHONE VALIDATION
// ======================================================

bool isValidPhone(const string& phone)
{
    if (phone.length() != 10)
    {
        return false;
    }

    for (char ch : phone)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    return true;
}


// ======================================================
// PAYMENT MENU - MEMBER 4
// ======================================================

void paymentMenu()
{
    double amount;

    cout << "\n========================================" << endl;
    cout << "          SMARTCART PAYMENT             " << endl;
    cout << "========================================" << endl;

    cout << "Enter order amount: Rs. ";
    cin >> amount;


    // Check amount
    if (amount <= 0)
    {
        cout << "Invalid amount!" << endl;
        return;
    }


    // ==================================================
    // COUPON
    // ==================================================

    char useCoupon;

    cout << "\nDo you have a coupon? (y/n): ";
    cin >> useCoupon;


    if (useCoupon == 'y' || useCoupon == 'Y')
    {
        string couponCode;

        cout << "Enter coupon code: ";
        cin >> couponCode;


        // Demo coupon
        Coupon coupon(
            "SAVE10",
            10.0,
            0.0,
            500.0,
            "31-12-2026",
            true
        );


        if (couponCode == coupon.getCode() &&
            coupon.isValid(amount))
        {
            double discount =
                coupon.calculateDiscount(amount);

            cout << "\nCoupon applied successfully!" << endl;

            cout << "Coupon   : "
                 << coupon.getCode() << endl;

            cout << "Discount : Rs. "
                 << discount << endl;

            amount =
                coupon.applyCoupon(amount);

            cout << "Final Amount: Rs. "
                 << amount << endl;
        }
        else
        {
            cout << "Invalid or expired coupon!" << endl;
        }
    }


    // ==================================================
    // PAYMENT METHOD
    // ==================================================

    cout << "\n===== PAYMENT METHOD =====" << endl;

    cout << "1. Card" << endl;
    cout << "2. UPI" << endl;
    cout << "3. Cash on Delivery" << endl;
    cout << "4. Cancel" << endl;

    cout << "Enter choice: ";

    int paymentChoice;
    cin >> paymentChoice;


    Payment* payment = nullptr;


    // ==================================================
    // CARD
    // ==================================================

    if (paymentChoice == 1)
    {
        payment = new Card();
    }


    // ==================================================
    // UPI
    // ==================================================

    else if (paymentChoice == 2)
    {
        payment = new UPI();
    }


    // ==================================================
    // CASH ON DELIVERY
    // ==================================================

    else if (paymentChoice == 3)
    {
        payment = new CashOnDelivery();
    }


    // ==================================================
    // CANCEL
    // ==================================================

    else if (paymentChoice == 4)
    {
        cout << "\nPayment cancelled." << endl;
        return;
    }


    else
    {
        cout << "\nInvalid payment choice!" << endl;
        return;
    }


    // ==================================================
    // PROCESS PAYMENT
    // ==================================================

    cout << "\n===== PROCESSING PAYMENT =====" << endl;

    bool success = payment->pay(amount);


    if (success)
    {
        cout << "\n========================================" << endl;
        cout << "         PAYMENT SUCCESSFUL             " << endl;
        cout << "========================================" << endl;

        cout << "Payment Method : "
             << payment->getPaymentMethod()
             << endl;

        cout << "Amount Paid    : Rs. "
             << amount
             << endl;

        cout << "Status         : SUCCESS"
             << endl;

        cout << "========================================" << endl;
    }
    else
    {
        cout << "\nPayment failed!" << endl;
    }


    delete payment;
}


// ======================================================
// MAIN
// ======================================================

int main()
{
    AuthService auth;

    int choice;


    while (true)
    {
        cout << "\n========================================" << endl;
        cout << "              SMARTCART                " << endl;
        cout << "========================================" << endl;

        cout << "1. Register Customer" << endl;
        cout << "2. Customer Login" << endl;
        cout << "3. Admin Login" << endl;
        cout << "4. Payment" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;


        // ==================================================
        // 1. CUSTOMER REGISTRATION
        // ==================================================

        if (choice == 1)
        {
            string id;
            string name;
            string username;
            string password;
            string phone;
            string address;


            cout << "\n===== CUSTOMER REGISTRATION ====="
                 << endl;


            cout << "Enter Customer ID: ";
            cin >> id;


            cout << "Enter Name: ";
            cin >> name;


            cout << "Enter Username: ";
            cin >> username;


            // Check username
            if (auth.usernameExists(username))
            {
                cout << "Username already exists!"
                     << endl;

                continue;
            }


            // Password
            while (true)
            {
                cout << "Enter Password: ";
                cin >> password;


                if (!password.empty())
                {
                    break;
                }


                cout << "Password cannot be empty!"
                     << endl;
            }


            // Phone
            while (true)
            {
                cout << "Enter Phone: ";
                cin >> phone;


                if (isValidPhone(phone))
                {
                    break;
                }


                cout << "Invalid phone number! "
                     << "Enter exactly 10 digits."
                     << endl;
            }


            cout << "Enter Address: ";
            cin >> address;


            // Create customer
            Customer customer(
                id,
                name,
                username,
                password,
                phone,
                address
            );


            // Register
            if (auth.registerCustomer(customer))
            {
                cout << "\nRegistration successful!"
                     << endl;
            }
            else
            {
                cout << "\nRegistration failed!"
                     << endl;
            }
        }


        // ==================================================
        // 2. CUSTOMER LOGIN
        // ==================================================

        else if (choice == 2)
        {
            string username;
            string password;


            cout << "\n===== CUSTOMER LOGIN ====="
                 << endl;


            cout << "Username: ";
            cin >> username;


            cout << "Password: ";
            cin >> password;


            Customer* customer =
                auth.loginCustomer(
                    username,
                    password
                );


            if (customer != nullptr)
            {
                cout << "\nLogin successful!"
                     << endl;


                // ==========================================
                // CUSTOMER MENU
                // ==========================================

                while (true)
                {
                    cout << "\n===== CUSTOMER MENU ====="
                         << endl;

                    cout << "1. View Profile"
                         << endl;

                    cout << "2. Update Profile"
                         << endl;

                    cout << "3. Logout"
                         << endl;

                    cout << "Enter choice: ";


                    int customerChoice;
                    cin >> customerChoice;


                    // --------------------------------------
                    // VIEW PROFILE
                    // --------------------------------------

                    if (customerChoice == 1)
                    {
                        customer->displayProfile();
                    }


                    // --------------------------------------
                    // UPDATE PROFILE
                    // --------------------------------------

                    else if (customerChoice == 2)
                    {
                        int updateChoice;


                        cout << "\n===== UPDATE PROFILE ====="
                             << endl;

                        cout << "1. Update Name"
                             << endl;

                        cout << "2. Update Phone"
                             << endl;

                        cout << "3. Update Address"
                             << endl;

                        cout << "Enter choice: ";

                        cin >> updateChoice;


                        // Update Name
                        if (updateChoice == 1)
                        {
                            string newName;


                            cout << "Enter new name: ";
                            cin >> newName;


                            customer->setName(newName);


                            cout << "Name updated successfully!"
                                 << endl;
                        }


                        // Update Phone
                        else if (updateChoice == 2)
                        {
                            string newPhone;


                            cout << "Enter new phone: ";
                            cin >> newPhone;


                            if (isValidPhone(newPhone))
                            {
                                customer->setPhone(newPhone);


                                cout << "Phone updated successfully!"
                                     << endl;
                            }
                            else
                            {
                                cout << "Invalid phone number!"
                                     << endl;
                            }
                        }


                        // Update Address
                        else if (updateChoice == 3)
                        {
                            string newAddress;


                            cout << "Enter new address: ";
                            cin >> newAddress;


                            customer->setAddress(newAddress);


                            cout << "Address updated successfully!"
                                 << endl;
                        }


                        else
                        {
                            cout << "Invalid choice!"
                                 << endl;
                        }
                    }


                    // --------------------------------------
                    // LOGOUT
                    // --------------------------------------

                    else if (customerChoice == 3)
                    {
                        cout << "Logged out successfully."
                             << endl;

                        break;
                    }


                    else
                    {
                        cout << "Invalid choice!"
                             << endl;
                    }
                }
            }


            else
            {
                cout << "\nInvalid username or password!"
                     << endl;
            }
        }


        // ==================================================
        // 3. ADMIN LOGIN
        // ==================================================

        else if (choice == 3)
        {
            string username;
            string password;


            cout << "\n===== ADMIN LOGIN ====="
                 << endl;


            cout << "Username: ";
            cin >> username;


            cout << "Password: ";
            cin >> password;


            Admin* admin =
                auth.loginAdmin(
                    username,
                    password
                );


            if (admin != nullptr)
            {
                cout << "\nAdmin login successful!"
                     << endl;

                admin->displayProfile();
            }
            else
            {
                cout << "\nInvalid admin username or password!"
                     << endl;
            }
        }


        // ==================================================
        // 4. PAYMENT
        // ==================================================

        else if (choice == 4)
        {
            paymentMenu();
        }


        // ==================================================
        // 5. EXIT
        // ==================================================

        else if (choice == 5)
        {
            cout << "\nThank you for using SmartCart!"
                 << endl;

            break;
        }


        // ==================================================
        // INVALID CHOICE
        // ==================================================

        else
        {
            cout << "\nInvalid choice!"
                 << endl;
        }
    }


    return 0;
}