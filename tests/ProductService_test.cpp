#include <iostream>
#include "product/Product.h"
#include "services/ProductService.h"

using namespace std;

void displayResults(
    const vector<Product>& products
)
{
    for (const auto& product : products)
    {
        product.display();
    }
}

int main()
{
    ProductService service;

    // Add products
    service.addProduct(
        Product(
            101,
            "Laptop",
            55000,
            10,
            "Electronics",
            "HP 15 inch laptop",
            "HP",
            4.5
        )
    );

    service.addProduct(
        Product(
            102,
            "Mouse",
            800,
            20,
            "Electronics",
            "Wireless mouse",
            "Logitech",
            4.2
        )
    );

    service.addProduct(
        Product(
            103,
            "Keyboard",
            1500,
            15,
            "Electronics",
            "Mechanical keyboard",
            "Redragon",
            4.4
        )
    );

    service.addProduct(
        Product(
            104,
            "Phone",
            30000,
            8,
            "Mobiles",
            "Android smartphone",
            "Samsung",
            4.7
        )
    );

    cout << "\n===== SEARCH TEST =====\n";

    vector<Product> searchResult =
        service.searchProducts("lap");

    displayResults(searchResult);


    cout << "\n===== CATEGORY FILTER TEST =====\n";

    vector<Product> categoryResult =
        service.filterByCategory("Electronics");

    displayResults(categoryResult);


    cout << "\n===== PRICE FILTER TEST =====\n";

    vector<Product> priceResult =
        service.filterByPrice(1000, 40000);

    displayResults(priceResult);


    cout << "\n===== PRICE ASCENDING TEST =====\n";

    service.sortByPriceAscending();
    service.displayAllProducts();


    cout << "\n===== PRICE DESCENDING TEST =====\n";

    service.sortByPriceDescending();
    service.displayAllProducts();


    cout << "\n===== RATING DESCENDING TEST =====\n";

    service.sortByRatingDescending();
    service.displayAllProducts();


    cout << "\n===== PRODUCT SERVICE TEST COMPLETED =====\n";

    return 0;
}