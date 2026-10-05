

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

using namespace std;

class Product
{
private:
    int id;
    string name;
    double price;
    int stock;
    string category;
    string description;
    string brand;
    double rating;

public:

    // Constructor
    Product(
        int id,
        string name,
        double price,
        int stock,
        string category,
        string description,
        string brand,
        double rating
    );

    // Getters
    int getId() const;
    string getName() const;
    double getPrice() const;
    int getStock() const;
    string getCategory() const;
    string getDescription() const;
    string getBrand() const;
    double getRating() const;

    // Setters / Update functions
    void updateDetails(
        const string& name,
        const string& category,
        double price,
        const string& description,
        const string& brand,
        double rating
    );

    // Stock management
    bool updateStock(int newStock);
    bool reduceStock(int quantity);

    // Display product details
    void display() const;
};

#endif