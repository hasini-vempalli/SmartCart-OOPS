#ifndef CART_H
#define CART_H

#include <vector>
#include "CartItem.h"

using namespace std;

class Cart
{
private:
    vector<CartItem> items;

public:
    void addProduct(string productId, string productName,
                    double price, int quantity);

    void removeProduct(string productId);

    void increaseQuantity(string productId, int amount);

    void decreaseQuantity(string productId, int amount);

    void clearCart();

    void displayCart() const;

    double calculateSubtotal() const;

    bool isEmpty() const;

    vector<CartItem> getItems() const;
};

#endif