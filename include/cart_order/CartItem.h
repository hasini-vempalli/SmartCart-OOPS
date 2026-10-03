#ifndef CARTITEM_H
#define CARTITEM_H

#include <string>

using namespace std;

class CartItem
{
private:
    string productId;
    string productName;
    double price;
    int quantity;

public:
    CartItem(string id, string name, double p, int q);

    double getTotal() const;

    void increaseQuantity(int amount);
    void decreaseQuantity(int amount);

    string getProductId() const;
    string getProductName() const;
    double getPrice() const;
    int getQuantity() const;
};

#endif