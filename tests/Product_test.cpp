#include "services/ProductService.h"

#include <iostream>
#include<vector>

using namespace std;

int main() {

    ProductService service;

    // ------------------------------------
    // 1. Add products
    // ------------------------------------

    Product laptop(
        101,
        "Laptop",
        55000,
        10,
        "Electronics",
        "HP 15 inch laptop",
        "HP",
        4.5
    );

    Product headphones(
        102,
        "Headphones",
        2000,
        25,
        "Electronics",
        "Wireless headphones",
        "Sony",
        4.2
    );

    Product notebook(
        103,
        "Notebook",
        100,
        50,
        "Stationery",
        "Ruled notebook",
        "Classmate",
        4.0
    );

    cout << "\nAdding products...\n";

    cout << service.addProduct(laptop) << endl;
    cout << service.addProduct(headphones) << endl;
    cout << service.addProduct(notebook) << endl;


    // ------------------------------------
    // 2. Display all products
    // ------------------------------------

    service.displayAllProducts();


    // ------------------------------------
    // 3. Find product
    // ------------------------------------

    cout << "\nFinding product 101...\n";

    Product* product =
        service.findProductById(101);

    if (product != nullptr) {
        product->display();
    }
    else {
        cout << "Product not found.\n";
    }


    // ------------------------------------
    // 4. Search
    // ------------------------------------

    cout << "\nSearching for laptop...\n";

    vector<Product> searchResult =
        service.searchProducts("laptop");

    for (const auto& p : searchResult) {
        p.display();
    }


    // ------------------------------------
    // 5. Category filter
    // ------------------------------------

    cout << "\nElectronics products...\n";

    vector<Product> electronics =
        service.filterByCategory("Electronics");

    for (const auto& p : electronics) {
        p.display();
    }


    // ------------------------------------
    // 6. Price filter
    // ------------------------------------

    cout << "\nProducts between Rs. 0 and Rs. 5000...\n";

    vector<Product> affordable =
        service.filterByPrice(0, 5000);

    for (const auto& p : affordable) {
        p.display();
    }


    // ------------------------------------
    // 7. Sort by price
    // ------------------------------------

    cout << "\nSorted by price: LOW to HIGH\n";

    service.sortByPriceAscending();

    service.displayAllProducts();


    cout << "\nSorted by price: HIGH to LOW\n";

    service.sortByPriceDescending();

    service.displayAllProducts();


    // ------------------------------------
    // 8. Sort by rating
    // ------------------------------------

    cout << "\nSorted by rating: HIGH to LOW\n";

    service.sortByRatingDescending();

    service.displayAllProducts();


    // ------------------------------------
    // 9. Update stock
    // ------------------------------------

    cout << "\nUpdating laptop stock to 20...\n";

    if (service.updateStock(101, 20)) {
        cout << "Stock updated successfully.\n";
    }
    else {
        cout << "Product not found.\n";
    }


    // ------------------------------------
    // 10. Reduce stock
    // ------------------------------------

    cout << "\nReducing laptop stock by 3...\n";

    product = service.findProductById(101);

    if (product != nullptr) {

        if (product->reduceStock(3)) {
            cout << "Stock reduced successfully.\n";
        }
        else {
            cout << "Unable to reduce stock.\n";
        }
    }


    // ------------------------------------
    // 11. Display updated product
    // ------------------------------------

    cout << "\nUpdated laptop:\n";

    product = service.findProductById(101);

    if (product != nullptr) {
        product->display();
    }


    // ------------------------------------
    // 12. Remove product
    // ------------------------------------

    cout << "\nRemoving notebook...\n";

    if (service.removeProduct(103)) {
        cout << "Product removed successfully.\n";
    }
    else {
        cout << "Product not found.\n";
    }


    // ------------------------------------
    // Final products
    // ------------------------------------

    cout << "\nFinal product list:\n";

    service.displayAllProducts();


    cout << "\nProduct module test completed.\n";

    return 0;
}