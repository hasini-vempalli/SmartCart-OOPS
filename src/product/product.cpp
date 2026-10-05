#include "product/Product.h"

using namespace std;

// Constructor
Product::Product(
    int id,
    string name,
    double price,
    int stock,
    string category,
    string description,
    string brand,
    double rating
)
{
    this->id = id;
    this->name = name;
    this->price = price;
    this->stock = stock;
    this->category = category;
    this->description = description;
    this->brand = brand;
    this->rating = rating;
}

// Get ID
int Product::getId() const
{
    return id;
}

// Get Name
string Product::getName() const
{
    return name;
}

// Get Price
double Product::getPrice() const
{
    return price;
}

// Get Stock
int Product::getStock() const
{
    return stock;
}

// Get Category
string Product::getCategory() const
{
    return category;
}

// Get Description
string Product::getDescription() const
{
    return description;
}

// Get Brand
string Product::getBrand() const
{
    return brand;
}

// Get Rating
double Product::getRating() const
{
    return rating;
}

// Update product details
void Product::updateDetails(
    const string& name,
    const string& category,
    double price,
    const string& description,
    const string& brand,
    double rating
)
{
    this->name = name;
    this->category = category;
    this->price = price;
    this->description = description;
    this->brand = brand;
    this->rating = rating;
}

// Update stock
bool Product::updateStock(int newStock)
{
    if (newStock < 0)
    {
        return false;
    }

    stock = newStock;
    return true;
}

// Reduce stock
bool Product::reduceStock(int quantity)
{
    if (quantity <= 0)
    {
        return false;
    }

    if (quantity > stock)
    {
        return false;
    }

    stock -= quantity;
    return true;
}

// Display product details
void Product::display() const
{
    cout << "----------------------------------------" << endl;
    cout << "Product ID    : " << id << endl;
    cout << "Name          : " << name << endl;
    cout << "Price         : " << price << endl;
    cout << "Stock         : " << stock << endl;
    cout << "Category      : " << category << endl;
    cout << "Description   : " << description << endl;
    cout << "Brand         : " << brand << endl;
    cout << "Rating        : " << rating << endl;
    cout << "----------------------------------------" << endl;
}