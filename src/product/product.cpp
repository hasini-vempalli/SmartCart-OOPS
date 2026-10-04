#include "product/Product.h"
#include <iostream>

using namespace std;

Product::Product(
    int id,
    string name,
    double price,
    int stock,
    string category,
    string description,
    string brand,
    double rating
) {
    this->id = id;
    this->name = name;
    this->price = price;
    this->stock = stock;
    this->category = category;
    this->description = description;
    this->brand = brand;
    this->rating = rating;
}

// Getters

int Product::getId() const {
    return id;
}

string Product::getName() const {
    return name;
}

string Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getStock() const {
    return stock;
}

string Product::getDescription() const {
    return description;
}

string Product::getBrand() const {
    return brand;
}

double Product::getRating() const {
    return rating;
}

// Update product details

void Product::updateDetails(
    string name,
    string category,
    double price,
    string description,
    string brand,
    double rating
) {
    this->name = name;
    this->category = category;
    this->price = price;
    this->description = description;
    this->brand = brand;
    this->rating = rating;
}

// Reduce stock

bool Product::reduceStock(int quantity) {

    if (quantity <= 0) {
        return false;
    }

    if (quantity > stock) {
        return false;
    }

    stock -= quantity;

    return true;
}

// Increase stock

void Product::increaseStock(int quantity) {

    if (quantity > 0) {
        stock += quantity;
    }
}

// Update stock directly

bool Product::updateStock(int newStock) {

    if (newStock < 0) {
        return false;
    }

    stock = newStock;

    return true;
}

// Display product

void Product::display() const {

    cout << id << " | "
         << name << " | "
         << category << " | Rs. "
         << price << " | Stock: "
         << stock << " | "
         << brand << " | Rating: "
         << rating << "/5"
         << endl;
}