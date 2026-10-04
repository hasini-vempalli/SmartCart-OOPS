#include "services/ProductService.h"

#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Convert string to lowercase

string toLowerCase(string text) {

    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        }
    );

    return text;
}

// Add product

bool ProductService::addProduct(const Product& product) {

    // Check duplicate product ID

    if (findProductById(product.getId()) != nullptr) {
        return false;
    }

    products.push_back(product);

    return true;
}

// Remove product

bool ProductService::removeProduct(int productId) {

    auto it = find_if(
        products.begin(),
        products.end(),
        [productId](const Product& product) {
            return product.getId() == productId;
        }
    );

    if (it == products.end()) {
        return false;
    }

    products.erase(it);

    return true;
}

// Find product by ID

Product* ProductService::findProductById(int productId) {

    for (auto& product : products) {

        if (product.getId() == productId) {
            return &product;
        }
    }

    return nullptr;
}

// Search products

vector<Product> ProductService::searchProducts(
    string keyword
) const {

    vector<Product> result;

    keyword = toLowerCase(keyword);

    for (const auto& product : products) {

        string name = toLowerCase(product.getName());
        string category = toLowerCase(product.getCategory());
        string brand = toLowerCase(product.getBrand());

        if (
            name.find(keyword) != string::npos ||
            category.find(keyword) != string::npos ||
            brand.find(keyword) != string::npos
        ) {
            result.push_back(product);
        }
    }

    return result;
}

// Filter by category

vector<Product> ProductService::filterByCategory(
    string category
) const {

    vector<Product> result;

    category = toLowerCase(category);

    for (const auto& product : products) {

        if (
            toLowerCase(product.getCategory())
            == category
        ) {
            result.push_back(product);
        }
    }

    return result;
}

// Filter by price

vector<Product> ProductService::filterByPrice(
    double minPrice,
    double maxPrice
) const {

    vector<Product> result;

    for (const auto& product : products) {

        if (
            product.getPrice() >= minPrice &&
            product.getPrice() <= maxPrice
        ) {
            result.push_back(product);
        }
    }

    return result;
}

// Sort by price - low to high

void ProductService::sortByPriceAscending() {

    sort(
        products.begin(),
        products.end(),
        [](const Product& a, const Product& b) {

            return a.getPrice() < b.getPrice();

        }
    );
}

// Sort by price - high to low

void ProductService::sortByPriceDescending() {

    sort(
        products.begin(),
        products.end(),
        [](const Product& a, const Product& b) {

            return a.getPrice() > b.getPrice();

        }
    );
}

// Sort by rating - high to low

void ProductService::sortByRatingDescending() {

    sort(
        products.begin(),
        products.end(),
        [](const Product& a, const Product& b) {

            return a.getRating() > b.getRating();

        }
    );
}

// Update product

bool ProductService::updateProduct(
    int productId,
    string name,
    string category,
    double price,
    string description,
    string brand,
    double rating
) {

    Product* product = findProductById(productId);

    if (product == nullptr) {
        return false;
    }

    product->updateDetails(
        name,
        category,
        price,
        description,
        brand,
        rating
    );

    return true;
}

// Update stock

bool ProductService::updateStock(
    int productId,
    int newStock
) {

    Product* product = findProductById(productId);

    if (product == nullptr) {
        return false;
    }

    return product->updateStock(newStock);
}

// Display all products

void ProductService::displayAllProducts() const {

    if (products.empty()) {

        cout << "\nNo products available.\n";

        return;
    }

    cout << "\n========== ALL PRODUCTS ==========\n";

    for (const auto& product : products) {
        product.display();
    }

    cout << "==================================\n";
}

// Get all products

const vector<Product>& ProductService::getProducts() const {

    return products;
}