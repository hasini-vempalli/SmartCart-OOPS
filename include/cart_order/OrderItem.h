#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>

using namespace std;

class OrderItem
{
private:
    string productId;
    string productName;
    double price;
    int quantity;

public:
    OrderItem(string id, string name, double p, int q);

    double getTotal() const;

    string getProductId() const;
    string getProductName() const;
    double getPrice() const;
    int getQuantity() const;
};

#endif