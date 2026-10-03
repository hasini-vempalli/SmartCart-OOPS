#include "../../include/cart_order/Cart.h"
#include <iostream>

using namespace std;

void Cart::addProduct(string productId, string productName,
                      double price, int quantity)
{
    // Check if product is already in the cart
    for (CartItem &item : items)
    {
        if (item.getProductId() == productId)
        {
            item.increaseQuantity(quantity);
            return;
        }
    }

    // Product is not already in the cart
    CartItem newItem(productId, productName, price, quantity);
    items.push_back(newItem);
}

void Cart::removeProduct(string productId)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (it->getProductId() == productId)
        {
            items.erase(it);
            return;
        }
    }
}

void Cart::increaseQuantity(string productId, int amount)
{
    for (CartItem &item : items)
    {
        if (item.getProductId() == productId)
        {
            item.increaseQuantity(amount);
            return;
        }
    }
}

void Cart::decreaseQuantity(string productId, int amount)
{
    for (CartItem &item : items)
    {
        if (item.getProductId() == productId)
        {
            item.decreaseQuantity(amount);

            if (item.getQuantity() == 0)
            {
                removeProduct(productId);
            }

            return;
        }
    }
}

void Cart::clearCart()
{
    items.clear();
}

void Cart::displayCart() const
{
    if (items.empty())
    {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "\n----- YOUR CART -----\n";

    for (const CartItem &item : items)
    {
        cout << "Product ID: " << item.getProductId() << endl;
        cout << "Product Name: " << item.getProductName() << endl;
        cout << "Price: " << item.getPrice() << endl;
        cout << "Quantity: " << item.getQuantity() << endl;
        cout << "Total: " << item.getTotal() << endl;
        cout << "---------------------\n";
    }

    cout << "Subtotal: " << calculateSubtotal() << endl;
}

double Cart::calculateSubtotal() const
{
    double subtotal = 0;

    for (const CartItem &item : items)
    {
        subtotal += item.getTotal();
    }

    return subtotal;
}

bool Cart::isEmpty() const
{
    return items.empty();
}

vector<CartItem> Cart::getItems() const
{
    return items;
}