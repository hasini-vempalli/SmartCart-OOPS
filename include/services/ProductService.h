#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

#include "product/Product.h"
#include <vector>
#include <string>

using namespace std;

class ProductService {
private:
    vector<Product> products;

public:
    // Add product
    bool addProduct(const Product& product);

    // Remove product
    bool removeProduct(int productId);

    // Find product
    Product* findProductById(int productId);

    // Search product
    vector<Product> searchProducts(string keyword) const;

    // Filter products
    vector<Product> filterByCategory(string category) const;

    vector<Product> filterByPrice(
        double minPrice,
        double maxPrice
    ) const;

    // Sorting
    void sortByPriceAscending();
    void sortByPriceDescending();
    void sortByRatingDescending();

    // Update product
    bool updateProduct(
        int productId,
        string name,
        string category,
        double price,
        string description,
        string brand,
        double rating
    );

    // Stock management
    bool updateStock(int productId, int newStock);

    // Display
    void displayAllProducts() const;

    // Access products
    const vector<Product>& getProducts() const;
};

#endif