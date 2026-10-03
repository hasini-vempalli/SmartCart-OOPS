#include "../../include/cart_order/CartItem.h"

CartItem::CartItem(string id, string name, double p, int q)
{
    productId = id;
    productName = name;
    price = p;
    quantity = q;
}

double CartItem::getTotal() const
{
    return price * quantity;
}

void CartItem::increaseQuantity(int amount)
{
    quantity += amount;
}

void CartItem::decreaseQuantity(int amount)
{
    quantity -= amount;

    if (quantity < 0)
    {
        quantity = 0;
    }
}

string CartItem::getProductId() const
{
    return productId;
}

string CartItem::getProductName() const
{
    return productName;
}

double CartItem::getPrice() const
{
    return price;
}

int CartItem::getQuantity() const
{
    return quantity;
}