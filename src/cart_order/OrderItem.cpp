#include "../../include/cart_order/OrderItem.h"

OrderItem::OrderItem(string id, string name, double p, int q)
{
    productId = id;
    productName = name;
    price = p;
    quantity = q;
}

double OrderItem::getTotal() const
{
    return price * quantity;
}

string OrderItem::getProductId() const
{
    return productId;
}

string OrderItem::getProductName() const
{
    return productName;
}

double OrderItem::getPrice() const
{
    return price;
}

int OrderItem::getQuantity() const
{
    return quantity;
}