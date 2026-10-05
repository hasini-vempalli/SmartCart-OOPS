#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {
private:
    string productId;
    string name;
    string category;
    double price;
    int stock;
    string description;
    string brand;
    double rating;

public:
    // Constructor
    Product(
        const string& productId,
        const string& name,
        const string& category,
        double price,
        int stock,
        const string& description,
        const string& brand,
        double rating
    );

    // Display product details
    void displayProduct() const;

    // Update product details
    void updateDetails(
        const string& name,
        const string& category,
        double price,
        const string& description,
        const string& brand,
        double rating
    );

    // Stock management
    void updateStock(int newStock);
    void reduceStock(int quantity);
    void increaseStock(int quantity);

    // Getters
    string getProductId() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    int getStock() const;
    string getDescription() const;
    string getBrand() const;
    double getRating() const;
};

#endif