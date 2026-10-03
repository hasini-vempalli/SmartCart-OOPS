#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "OrderItem.h"

using namespace std;

enum class OrderStatus
{
    PLACED,
    CONFIRMED,
    SHIPPED,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};

class Order
{
private:
    string orderId;
    string customerId;

    vector<OrderItem> items;

    double subtotal;
    double discount;
    double finalAmount;

    string paymentMethod;
    string orderDate;

    OrderStatus status;

public:
    Order(string id, string custId,
          vector<OrderItem> orderItems,
          double sub,
          double disc,
          double finalAmt,
          string payment,
          string date);

    void displayOrder() const;

    void updateStatus(OrderStatus newStatus);

    bool canCancel() const;

    void cancel();

    double calculateTotal() const;

    string getOrderId() const;
    string getCustomerId() const;

    OrderStatus getStatus() const;

    vector<OrderItem> getItems() const;

    double getSubtotal() const;
    double getDiscount() const;
    double getFinalAmount() const;

    string getPaymentMethod() const;
    string getOrderDate() const;
};

#endif