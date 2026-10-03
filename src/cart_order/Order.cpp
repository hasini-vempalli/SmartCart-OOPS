#include "../../include/cart_order/Order.h"
#include <iostream>

using namespace std;

Order::Order(string id, string custId,
             vector<OrderItem> orderItems,
             double sub,
             double disc,
             double finalAmt,
             string payment,
             string date)
{
    orderId = id;
    customerId = custId;
    items = orderItems;

    subtotal = sub;
    discount = disc;
    finalAmount = finalAmt;

    paymentMethod = payment;
    orderDate = date;

    status = OrderStatus::PLACED;
}

double Order::calculateTotal() const
{
    return subtotal - discount;
}

bool Order::canCancel() const
{
    return status == OrderStatus::PLACED ||
           status == OrderStatus::CONFIRMED;
}

void Order::cancel()
{
    if (canCancel())
    {
        status = OrderStatus::CANCELLED;
    }
    else
    {
        cout << "Order cannot be cancelled." << endl;
    }
}

void Order::updateStatus(OrderStatus newStatus)
{
    status = newStatus;
}

void Order::displayOrder() const
{
    cout << "\n========== ORDER ==========\n";

    cout << "Order ID: " << orderId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Order Date: " << orderDate << endl;

    cout << "\nItems:\n";

    for (const OrderItem &item : items)
    {
        cout << item.getProductName()
             << " x " << item.getQuantity()
             << " = Rs. " << item.getTotal()
             << endl;
    }

    cout << "\nSubtotal: Rs. " << subtotal << endl;
    cout << "Discount: Rs. " << discount << endl;
    cout << "Final Amount: Rs. " << finalAmount << endl;

    cout << "Payment Method: " << paymentMethod << endl;

    cout << "Status: ";

    switch (status)
    {
        case OrderStatus::PLACED:
            cout << "PLACED";
            break;

        case OrderStatus::CONFIRMED:
            cout << "CONFIRMED";
            break;

        case OrderStatus::SHIPPED:
            cout << "SHIPPED";
            break;

        case OrderStatus::OUT_FOR_DELIVERY:
            cout << "OUT FOR DELIVERY";
            break;

        case OrderStatus::DELIVERED:
            cout << "DELIVERED";
            break;

        case OrderStatus::CANCELLED:
            cout << "CANCELLED";
            break;
    }

    cout << "\n===========================\n";
}

string Order::getOrderId() const
{
    return orderId;
}

string Order::getCustomerId() const
{
    return customerId;
}

OrderStatus Order::getStatus() const
{
    return status;
}

vector<OrderItem> Order::getItems() const
{
    return items;
}

double Order::getSubtotal() const
{
    return subtotal;
}

double Order::getDiscount() const
{
    return discount;
}

double Order::getFinalAmount() const
{
    return finalAmount;
}

string Order::getPaymentMethod() const
{
    return paymentMethod;
}

string Order::getOrderDate() const
{
    return orderDate;
}