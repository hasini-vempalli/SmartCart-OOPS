#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <limits>

#include "auth/Customer.h"
#include "auth/Admin.h"

#include "services/AuthService.h"
#include "services/ProductService.h"

#include "product/Product.h"

#include "cart_order/Cart.h"
#include "cart_order/CartItem.h"
#include "cart_order/Order.h"
#include "cart_order/OrderItem.h"

#include "payment/Payment.h"
#include "payment/Card.h"
#include "payment/UPI.h"
#include "payment/CashOnDelivery.h"
#include "payment/Coupon.h"

using namespace std;


// ============================================================
// GLOBAL ORDER STORAGE
// ============================================================

vector<Order> allOrders;


// ============================================================
// PHONE VALIDATION
// ============================================================

bool isValidPhone(const string& phone)
{
    if (phone.length() != 10)
        return false;

    for (char ch : phone)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
            return false;
    }

    return true;
}


// ============================================================
// DATE
// ============================================================

string getCurrentDate()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[20];

    strftime(
        buffer,
        sizeof(buffer),
        "%d-%m-%Y",
        localTime
    );

    return string(buffer);
}


// ============================================================
// DEMO PRODUCTS
// ============================================================

void loadProducts(ProductService& productService)
{
    productService.addProduct(
        Product(
            101,
            "Laptop",
            55000,
            10,
            "Electronics",
            "High performance laptop",
            "HP",
            4.5
        )
    );

    productService.addProduct(
        Product(
            102,
            "Smartphone",
            25000,
            15,
            "Electronics",
            "Latest smartphone",
            "Samsung",
            4.4
        )
    );

    productService.addProduct(
        Product(
            103,
            "Headphones",
            2500,
            20,
            "Electronics",
            "Wireless headphones",
            "Boat",
            4.2
        )
    );

    productService.addProduct(
        Product(
            104,
            "Backpack",
            1800,
            25,
            "Accessories",
            "College backpack",
            "American Tourister",
            4.3
        )
    );

    productService.addProduct(
        Product(
            105,
            "Smart Watch",
            3500,
            12,
            "Accessories",
            "Smart watch",
            "Noise",
            4.1
        )
    );
}


// ============================================================
// DISPLAY PRODUCTS
// ============================================================

void displayProducts(ProductService& productService)
{
    cout << "\n";
    cout << "============================================\n";
    cout << "              AVAILABLE PRODUCTS\n";
    cout << "============================================\n";

    productService.displayAllProducts();

    cout << "============================================\n";
}


// ============================================================
// PAYMENT PROCESSING
// ============================================================

bool processPayment(
    double amount,
    string& paymentMethod
)
{
    if (amount <= 0)
    {
        cout << "\nInvalid payment amount!\n";
        return false;
    }

    cout << "\n";
    cout << "============================================\n";
    cout << "               PAYMENT METHOD\n";
    cout << "============================================\n";

    cout << "Amount to Pay : Rs. " << amount << "\n\n";

    cout << "1. Card\n";
    cout << "2. UPI\n";
    cout << "3. Cash on Delivery\n";
    cout << "4. Cancel\n";

    cout << "\nEnter choice: ";

    int choice;
    cin >> choice;

    Payment* payment = nullptr;


    // --------------------------------------------------------
    // CARD
    // --------------------------------------------------------

    if (choice == 1)
    {
        payment = new Card();
    }


    // --------------------------------------------------------
    // UPI
    // --------------------------------------------------------

    else if (choice == 2)
    {
        payment = new UPI();
    }


    // --------------------------------------------------------
    // COD
    // --------------------------------------------------------

    else if (choice == 3)
    {
        payment = new CashOnDelivery();
    }


    // --------------------------------------------------------
    // CANCEL
    // --------------------------------------------------------

    else if (choice == 4)
    {
        cout << "\nPayment cancelled.\n";
        return false;
    }


    else
    {
        cout << "\nInvalid payment choice!\n";
        return false;
    }


    // --------------------------------------------------------
    // PAY
    // --------------------------------------------------------

    bool success = payment->pay(amount);


    if (success)
    {
        paymentMethod =
            payment->getPaymentMethod();

        cout << "\n";
        cout << "============================================\n";
        cout << "             PAYMENT SUCCESSFUL\n";
        cout << "============================================\n";

        cout << "Payment Method : "
             << paymentMethod << "\n";

        cout << "Amount Paid    : Rs. "
             << amount << "\n";

        cout << "Status         : SUCCESS\n";

        cout << "============================================\n";
    }
    else
    {
        cout << "\nPayment failed!\n";
    }


    delete payment;

    return success;
}


// ============================================================
// COUPON PROCESSING
// ============================================================

double applyCoupon(
    double subtotal,
    double& discount
)
{
    discount = 0;

    char choice;

    cout << "\nDo you have a coupon? (y/n): ";
    cin >> choice;


    if (choice != 'y' && choice != 'Y')
    {
        return subtotal;
    }


    string code;

    cout << "Enter coupon code: ";
    cin >> code;


    // Demo coupon
    Coupon coupon(
        "SAVE10",
        10.0,
        0.0,
        500.0,
        "31-12-2026",
        true
    );


    if (
        code == coupon.getCode() &&
        coupon.isValid(subtotal)
    )
    {
        discount =
            coupon.calculateDiscount(subtotal);

        double finalAmount =
            coupon.applyCoupon(subtotal);


        cout << "\n";
        cout << "Coupon applied successfully!\n";

        cout << "Coupon   : "
             << coupon.getCode() << "\n";

        cout << "Discount : Rs. "
             << discount << "\n";

        cout << "Final Amount : Rs. "
             << finalAmount << "\n";


        return finalAmount;
    }


    cout << "\nInvalid or unavailable coupon!\n";

    return subtotal;
}


// ============================================================
// ADD PRODUCT TO CART
// ============================================================

void addToCart(
    Cart& cart,
    ProductService& productService
)
{
    displayProducts(productService);


    int productId;
    int quantity;


    cout << "\nEnter Product ID: ";
    cin >> productId;


    Product* product =
        productService.findProductById(productId);


    if (product == nullptr)
    {
        cout << "\nProduct not found!\n";
        return;
    }


    cout << "\n";
    cout << "Product Name : "
         << product->getName() << "\n";

    cout << "Price        : Rs. "
         << product->getPrice() << "\n";

    cout << "Stock        : "
         << product->getStock() << "\n";


    cout << "\nEnter Quantity: ";
    cin >> quantity;


    if (quantity <= 0)
    {
        cout << "\nInvalid quantity!\n";
        return;
    }


    if (quantity > product->getStock())
    {
        cout << "\nNot enough stock!\n";
        return;
    }


    cart.addProduct(
        to_string(product->getId()),
        product->getName(),
        product->getPrice(),
        quantity
    );


    cout << "\n";
    cout << "Product added to cart successfully!\n";
}


// ============================================================
// SHOPPING CART MENU
// ============================================================

void cartMenu(
    Cart& cart,
    ProductService& productService
)
{
    while (true)
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "               SHOPPING CART\n";
        cout << "============================================\n";

        cout << "1. View Available Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Increase Quantity\n";
        cout << "5. Decrease Quantity\n";
        cout << "6. Remove Product\n";
        cout << "7. Clear Cart\n";
        cout << "8. View Cart Total\n";
        cout << "9. Back\n";

        cout << "\nEnter choice: ";

        int choice;
        cin >> choice;


        // ----------------------------------------------------
        // VIEW PRODUCTS
        // ----------------------------------------------------

        if (choice == 1)
        {
            displayProducts(productService);
        }


        // ----------------------------------------------------
        // ADD PRODUCT
        // ----------------------------------------------------

        else if (choice == 2)
        {
            addToCart(
                cart,
                productService
            );
        }


        // ----------------------------------------------------
        // VIEW CART
        // ----------------------------------------------------

        else if (choice == 3)
        {
            if (cart.isEmpty())
            {
                cout << "\nYour cart is empty!\n";
            }
            else
            {
                cart.displayCart();
            }
        }


        // ----------------------------------------------------
        // INCREASE
        // ----------------------------------------------------

        else if (choice == 4)
        {
            if (cart.isEmpty())
            {
                cout << "\nYour cart is empty!\n";
                continue;
            }


            string productId;
            int amount;


            cout << "\nEnter Product ID: ";
            cin >> productId;


            cout << "Enter quantity to increase: ";
            cin >> amount;


            if (amount <= 0)
            {
                cout << "\nInvalid quantity!\n";
                continue;
            }


            cart.increaseQuantity(
                productId,
                amount
            );


            cout << "\nQuantity increased!\n";
        }


        // ----------------------------------------------------
        // DECREASE
        // ----------------------------------------------------

        else if (choice == 5)
        {
            if (cart.isEmpty())
            {
                cout << "\nYour cart is empty!\n";
                continue;
            }


            string productId;
            int amount;


            cout << "\nEnter Product ID: ";
            cin >> productId;


            cout << "Enter quantity to decrease: ";
            cin >> amount;


            if (amount <= 0)
            {
                cout << "\nInvalid quantity!\n";
                continue;
            }


            cart.decreaseQuantity(
                productId,
                amount
            );


            cout << "\nQuantity decreased!\n";
        }


        // ----------------------------------------------------
        // REMOVE
        // ----------------------------------------------------

        else if (choice == 6)
        {
            if (cart.isEmpty())
            {
                cout << "\nYour cart is empty!\n";
                continue;
            }


            string productId;


            cout << "\nEnter Product ID: ";
            cin >> productId;


            cart.removeProduct(productId);


            cout << "\nProduct removed from cart!\n";
        }


        // ----------------------------------------------------
        // CLEAR
        // ----------------------------------------------------

        else if (choice == 7)
        {
            cart.clearCart();

            cout << "\nCart cleared successfully!\n";
        }


        // ----------------------------------------------------
        // TOTAL
        // ----------------------------------------------------

        else if (choice == 8)
        {
            double total =
                cart.calculateSubtotal();


            cout << "\n";
            cout << "============================================\n";
            cout << "Cart Total : Rs. "
                 << total << "\n";
            cout << "============================================\n";
        }


        // ----------------------------------------------------
        // BACK
        // ----------------------------------------------------

        else if (choice == 9)
        {
            break;
        }


        else
        {
            cout << "\nInvalid choice!\n";
        }
    }
}


// ============================================================
// PLACE ORDER
// ============================================================

void placeOrder(
    Cart& cart,
    ProductService& productService,
    Customer* customer
)
{
    if (cart.isEmpty())
    {
        cout << "\nYour cart is empty!\n";
        cout << "Add products before placing an order.\n";
        return;
    }


    cout << "\n";
    cout << "============================================\n";
    cout << "                CHECKOUT\n";
    cout << "============================================\n";


    double subtotal =
        cart.calculateSubtotal();


    cout << "Subtotal : Rs. "
         << subtotal << "\n";


    // --------------------------------------------------------
    // COUPON
    // --------------------------------------------------------

    double discount = 0;


    double finalAmount =
        applyCoupon(
            subtotal,
            discount
        );


    cout << "\nAmount to Pay : Rs. "
         << finalAmount << "\n";


    // --------------------------------------------------------
    // PAYMENT
    // --------------------------------------------------------

    string paymentMethod;


    bool paymentSuccess =
        processPayment(
            finalAmount,
            paymentMethod
        );


    if (!paymentSuccess)
    {
        cout << "\nOrder was not placed.\n";
        return;
    }


    // --------------------------------------------------------
    // CHECK STOCK AGAIN
    // --------------------------------------------------------

    vector<CartItem> cartItems =
        cart.getItems();


    for (const CartItem& item : cartItems)
    {
        int productId =
            stoi(item.getProductId());


        Product* product =
            productService.findProductById(
                productId
            );


        if (product == nullptr)
        {
            cout << "\nProduct no longer exists.\n";
            return;
        }


        if (item.getQuantity() >
            product->getStock())
        {
            cout << "\nNot enough stock for "
                 << product->getName()
                 << ".\n";

            return;
        }
    }


    // --------------------------------------------------------
    // CREATE ORDER ITEMS
    // --------------------------------------------------------

    vector<OrderItem> orderItems;


    for (const CartItem& item : cartItems)
    {
        OrderItem orderItem(
            item.getProductId(),
            item.getProductName(),
            item.getPrice(),
            item.getQuantity()
        );


        orderItems.push_back(
            orderItem
        );
    }


    // --------------------------------------------------------
    // GENERATE ORDER ID
    // --------------------------------------------------------

    static int orderNumber = 1001;


    string orderId =
        "ORD" +
        to_string(orderNumber++);


    // --------------------------------------------------------
    // CUSTOMER ID
    // --------------------------------------------------------

    string customerId =
        customer->getUserId();


    // --------------------------------------------------------
    // CREATE ORDER
    // --------------------------------------------------------

    Order order(
        orderId,
        customerId,
        orderItems,
        subtotal,
        discount,
        finalAmount,
        paymentMethod,
        getCurrentDate()
    );


    // --------------------------------------------------------
    // REDUCE STOCK
    // --------------------------------------------------------

    for (const CartItem& item : cartItems)
    {
        int productId =
            stoi(item.getProductId());


        Product* product =
            productService.findProductById(
                productId
            );


        if (product != nullptr)
        {
            product->reduceStock(
                item.getQuantity()
            );
        }
    }


    // --------------------------------------------------------
    // SAVE ORDER
    // --------------------------------------------------------

    allOrders.push_back(order);


    // --------------------------------------------------------
    // CLEAR CART
    // --------------------------------------------------------

    cart.clearCart();


    // --------------------------------------------------------
    // DISPLAY ORDER
    // --------------------------------------------------------

    cout << "\n";
    cout << "============================================\n";
    cout << "          ORDER PLACED SUCCESSFULLY\n";
    cout << "============================================\n";


    order.displayOrder();


    cout << "\nYour cart has been cleared.\n";

    cout << "Thank you for shopping with SmartCart!\n";
}


// ============================================================
// VIEW CUSTOMER ORDERS
// ============================================================

void viewOrders(Customer* customer)
{
    string customerId =
        customer->getUserId();


    bool found = false;


    cout << "\n";
    cout << "============================================\n";
    cout << "                MY ORDERS\n";
    cout << "============================================\n";


    for (Order& order : allOrders)
    {
        if (order.getCustomerId() ==
            customerId)
        {
            found = true;

            order.displayOrder();
        }
    }


    if (!found)
    {
        cout << "\nYou have no orders yet.\n";
    }
}


// ============================================================
// CANCEL ORDER
// ============================================================

void cancelOrder(Customer* customer)
{
    string customerId =
        customer->getUserId();


    vector<int> indexes;


    for (int i = 0;
         i < static_cast<int>(allOrders.size());
         i++)
    {
        if (
            allOrders[i].getCustomerId()
            == customerId
        )
        {
            indexes.push_back(i);
        }
    }


    if (indexes.empty())
    {
        cout << "\nYou have no orders.\n";
        return;
    }


    cout << "\n";
    cout << "============================================\n";
    cout << "             CANCEL ORDER\n";
    cout << "============================================\n";


    for (int index : indexes)
    {
        cout << "\nOrder ID : "
             << allOrders[index].getOrderId();

        cout << "\nAmount   : Rs. "
             << allOrders[index].getFinalAmount();

        cout << "\nStatus   : ";


        OrderStatus status =
            allOrders[index].getStatus();


        if (status == OrderStatus::PLACED)
            cout << "PLACED";

        else if (status == OrderStatus::CONFIRMED)
            cout << "CONFIRMED";

        else if (status == OrderStatus::SHIPPED)
            cout << "SHIPPED";

        else if (status == OrderStatus::OUT_FOR_DELIVERY)
            cout << "OUT FOR DELIVERY";

        else if (status == OrderStatus::DELIVERED)
            cout << "DELIVERED";

        else
            cout << "CANCELLED";


        cout << "\n";
    }


    string orderId;


    cout << "\nEnter Order ID to cancel: ";
    cin >> orderId;


    for (Order& order : allOrders)
    {
        if (
            order.getOrderId() ==
            orderId &&
            order.getCustomerId() ==
            customerId
        )
        {
            if (order.canCancel())
            {
                order.cancel();


                cout << "\nOrder "
                     << orderId
                     << " cancelled successfully!\n";
            }
            else
            {
                cout << "\nThis order cannot be cancelled.\n";
            }


            return;
        }
    }


    cout << "\nOrder not found!\n";
}


// ============================================================
// CUSTOMER MENU
// ============================================================

void customerMenu(
    Customer* customer,
    ProductService& productService
)
{
    Cart customerCart;

    while (true)
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "              CUSTOMER MENU\n";
        cout << "============================================\n";
        cout << "1. View Profile\n";
        cout << "2. Update Profile\n";
        cout << "3. View All Products\n";
        cout << "4. Search Products\n";
        cout << "5. Filter Products\n";
        cout << "6. Sort Products\n";
        cout << "7. Shopping Cart\n";
        cout << "8. Place Order\n";
        cout << "9. My Orders\n";
        cout << "10. Cancel Order\n";
        cout << "11. Logout\n";

        cout << "\nEnter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            customer->displayProfile();
        }
        else if (choice == 2)
        {
            cout << "\n";
            cout << "============================================\n";
            cout << "             UPDATE PROFILE\n";
            cout << "============================================\n";
            cout << "1. Update Name\n";
            cout << "2. Update Phone\n";
            cout << "3. Update Address\n";
            cout << "\nEnter choice: ";

            int updateChoice;
            cin >> updateChoice;

            if (updateChoice == 1)
            {
                string name;
                cout << "Enter new name: ";
                cin >> name;
                customer->setName(name);
                cout << "\nName updated successfully!\n";
            }
            else if (updateChoice == 2)
            {
                string phone;
                cout << "Enter new phone: ";
                cin >> phone;

                if (isValidPhone(phone))
                {
                    customer->setPhone(phone);
                    cout << "\nPhone updated successfully!\n";
                }
                else
                {
                    cout << "\nInvalid phone number!\n";
                }
            }
            else if (updateChoice == 3)
            {
                string address;
                cout << "Enter new address: ";
                cin >> address;
                customer->setAddress(address);
                cout << "\nAddress updated successfully!\n";
            }
            else
            {
                cout << "\nInvalid choice!\n";
            }
        }
        else if (choice == 3)
        {
            displayProducts(productService);
        }
        else if (choice == 4)
        {
            string keyword;

            cout << "\n============================================\n";
            cout << "             SEARCH PRODUCTS\n";
            cout << "============================================\n";
            cout << "Enter product name, category or brand: ";
            cin >> keyword;

            vector<Product> results =
                productService.searchProducts(keyword);

            cout << "\n========== SEARCH RESULTS ==========\n";

            if (results.empty())
            {
                cout << "No products found.\n";
            }
            else
            {
                for (const Product& product : results)
                {
                    product.display();
                }
            }

            cout << "====================================\n";
        }
        else if (choice == 5)
        {
            cout << "\n============================================\n";
            cout << "             FILTER PRODUCTS\n";
            cout << "============================================\n";
            cout << "1. Filter by Category\n";
            cout << "2. Filter by Price Range\n";
            cout << "3. Back\n";
            cout << "\nEnter choice: ";

            int filterChoice;
            cin >> filterChoice;

            if (filterChoice == 1)
            {
                string category;
                cout << "\nEnter category: ";
                cin >> category;

                vector<Product> results =
                    productService.filterByCategory(category);

                cout << "\n========== FILTER RESULTS ==========\n";

                if (results.empty())
                {
                    cout << "No products found in this category.\n";
                }
                else
                {
                    for (const Product& product : results)
                    {
                        product.display();
                    }
                }

                cout << "====================================\n";
            }
            else if (filterChoice == 2)
            {
                double minPrice, maxPrice;

                cout << "\nEnter minimum price: ";
                cin >> minPrice;
                cout << "Enter maximum price: ";
                cin >> maxPrice;

                if (minPrice > maxPrice)
                {
                    cout << "\nInvalid price range!\n";
                }
                else
                {
                    vector<Product> results =
                        productService.filterByPrice(minPrice, maxPrice);

                    cout << "\n========== FILTER RESULTS ==========\n";

                    if (results.empty())
                    {
                        cout << "No products found in this price range.\n";
                    }
                    else
                    {
                        for (const Product& product : results)
                        {
                            product.display();
                        }
                    }

                    cout << "====================================\n";
                }
            }
            else if (filterChoice != 3)
            {
                cout << "\nInvalid choice!\n";
            }
        }
        else if (choice == 6)
        {
            cout << "\n============================================\n";
            cout << "             SORT PRODUCTS\n";
            cout << "============================================\n";
            cout << "1. Price - Low to High\n";
            cout << "2. Price - High to Low\n";
            cout << "3. Rating - High to Low\n";
            cout << "4. Back\n";
            cout << "\nEnter choice: ";

            int sortChoice;
            cin >> sortChoice;

            if (sortChoice == 1)
            {
                productService.sortByPriceAscending();
                cout << "\nProducts sorted by price: Low to High\n";
                displayProducts(productService);
            }
            else if (sortChoice == 2)
            {
                productService.sortByPriceDescending();
                cout << "\nProducts sorted by price: High to Low\n";
                displayProducts(productService);
            }
            else if (sortChoice == 3)
            {
                productService.sortByRatingDescending();
                cout << "\nProducts sorted by rating: High to Low\n";
                displayProducts(productService);
            }
            else if (sortChoice != 4)
            {
                cout << "\nInvalid choice!\n";
            }
        }
        else if (choice == 7)
        {
            cartMenu(customerCart, productService);
        }
        else if (choice == 8)
        {
            placeOrder(customerCart, productService, customer);
        }
        else if (choice == 9)
        {
            viewOrders(customer);
        }
        else if (choice == 10)
        {
            cancelOrder(customer);
        }
        else if (choice == 11)
        {
            cout << "\nLogged out successfully.\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
    }
}


// ============================================================
// ADMIN PRODUCT MENU
// ============================================================

void adminProductMenu(
    ProductService& productService
)
{
    while (true)
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "             ADMIN PRODUCT MENU\n";
        cout << "============================================\n";

        cout << "1. View All Products\n";
        cout << "2. Add Product\n";
        cout << "3. Remove Product\n";
        cout << "4. Update Product\n";
        cout << "5. Update Stock\n";
        cout << "6. Search Product\n";
        cout << "7. Sort by Price - Low to High\n";
        cout << "8. Sort by Price - High to Low\n";
        cout << "9. Sort by Rating\n";
        cout << "10. Back\n";


        cout << "\nEnter choice: ";


        int choice;
        cin >> choice;


        // ----------------------------------------------------
        // VIEW
        // ----------------------------------------------------

        if (choice == 1)
        {
            displayProducts(
                productService
            );
        }


        // ----------------------------------------------------
        // ADD
        // ----------------------------------------------------

        else if (choice == 2)
        {
            int id;
            string name;
            double price;
            int stock;
            string category;
            string description;
            string brand;
            double rating;


            cout << "\nProduct ID: ";
            cin >> id;


            cout << "Name: ";
            cin >> name;


            cout << "Price: ";
            cin >> price;


            cout << "Stock: ";
            cin >> stock;


            cout << "Category: ";
            cin >> category;


            cout << "Description: ";
            cin >> description;


            cout << "Brand: ";
            cin >> brand;


            cout << "Rating: ";
            cin >> rating;


            Product product(
                id,
                name,
                price,
                stock,
                category,
                description,
                brand,
                rating
            );


            if (
                productService.addProduct(product)
            )
            {
                cout << "\nProduct added successfully!\n";
            }
            else
            {
                cout << "\nProduct ID already exists!\n";
            }
        }


        // ----------------------------------------------------
        // REMOVE
        // ----------------------------------------------------

        else if (choice == 3)
        {
            int id;


            cout << "\nEnter Product ID: ";
            cin >> id;


            if (
                productService.removeProduct(id)
            )
            {
                cout << "\nProduct removed successfully!\n";
            }
            else
            {
                cout << "\nProduct not found!\n";
            }
        }


        // ----------------------------------------------------
        // UPDATE PRODUCT
        // ----------------------------------------------------

        else if (choice == 4)
        {
            int id;
            string name;
            string category;
            double price;
            string description;
            string brand;
            double rating;


            cout << "\nProduct ID: ";
            cin >> id;


            cout << "New Name: ";
            cin >> name;


            cout << "New Category: ";
            cin >> category;


            cout << "New Price: ";
            cin >> price;


            cout << "New Description: ";
            cin >> description;


            cout << "New Brand: ";
            cin >> brand;


            cout << "New Rating: ";
            cin >> rating;


            if (
                productService.updateProduct(
                    id,
                    name,
                    category,
                    price,
                    description,
                    brand,
                    rating
                )
            )
            {
                cout << "\nProduct updated successfully!\n";
            }
            else
            {
                cout << "\nProduct not found!\n";
            }
        }


        // ----------------------------------------------------
        // STOCK
        // ----------------------------------------------------

        else if (choice == 5)
        {
            int id;
            int stock;


            cout << "\nProduct ID: ";
            cin >> id;


            cout << "New Stock: ";
            cin >> stock;


            if (
                productService.updateStock(
                    id,
                    stock
                )
            )
            {
                cout << "\nStock updated successfully!\n";
            }
            else
            {
                cout << "\nUnable to update stock!\n";
            }
        }


        // ----------------------------------------------------
        // SEARCH
        // ----------------------------------------------------

        else if (choice == 6)
        {
            string keyword;


            cout << "\nEnter search keyword: ";
            cin >> keyword;


            vector<Product> results =
                productService.searchProducts(
                    keyword
                );


            cout << "\n";
            cout << "========== SEARCH RESULTS ==========\n";


            if (results.empty())
            {
                cout << "No products found.\n";
            }
            else
            {
                for (const Product& product : results)
                {
                    product.display();
                }
            }


            cout << "====================================\n";
        }


        // ----------------------------------------------------
        // SORT ASCENDING
        // ----------------------------------------------------

        else if (choice == 7)
        {
            productService.sortByPriceAscending();

            cout << "\nProducts sorted by price!\n";

            displayProducts(productService);
        }


        // ----------------------------------------------------
        // SORT DESCENDING
        // ----------------------------------------------------

        else if (choice == 8)
        {
            productService.sortByPriceDescending();

            cout << "\nProducts sorted by price!\n";

            displayProducts(productService);
        }


        // ----------------------------------------------------
        // SORT RATING
        // ----------------------------------------------------

        else if (choice == 9)
        {
            productService.sortByRatingDescending();

            cout << "\nProducts sorted by rating!\n";

            displayProducts(productService);
        }


        // ----------------------------------------------------
        // BACK
        // ----------------------------------------------------

        else if (choice == 10)
        {
            break;
        }


        else
        {
            cout << "\nInvalid choice!\n";
        }
    }
}


// ============================================================
// ADMIN MENU
// ============================================================

void adminMenu(
    Admin* admin,
    ProductService& productService
)
{
    while (true)
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "                ADMIN MENU\n";
        cout << "============================================\n";

        cout << "1. View Profile\n";
        cout << "2. Product Management\n";
        cout << "3. View All Orders\n";
        cout << "4. Logout\n";


        cout << "\nEnter choice: ";


        int choice;
        cin >> choice;


        // ----------------------------------------------------
        // PROFILE
        // ----------------------------------------------------

        if (choice == 1)
        {
            admin->displayProfile();
        }


        // ----------------------------------------------------
        // PRODUCTS
        // ----------------------------------------------------

        else if (choice == 2)
        {
            adminProductMenu(
                productService
            );
        }


        // ----------------------------------------------------
        // ORDERS
        // ----------------------------------------------------

        else if (choice == 3)
        {
            cout << "\n";
            cout << "============================================\n";
            cout << "              ALL ORDERS\n";
            cout << "============================================\n";


            if (allOrders.empty())
            {
                cout << "\nNo orders available.\n";
            }
            else
            {
                for (const Order& order : allOrders)
                {
                    order.displayOrder();
                }
            }
        }


        // ----------------------------------------------------
        // LOGOUT
        // ----------------------------------------------------

        else if (choice == 4)
        {
            cout << "\nAdmin logged out successfully.\n";
            break;
        }


        else
        {
            cout << "\nInvalid choice!\n";
        }
    }
}


// ============================================================
// STANDALONE PAYMENT
// ============================================================

void standalonePayment()
{
    double amount;


    cout << "\n";
    cout << "============================================\n";
    cout << "            SMARTCART PAYMENT\n";
    cout << "============================================\n";


    cout << "Enter amount: Rs. ";
    cin >> amount;


    if (amount <= 0)
    {
        cout << "\nInvalid amount!\n";
        return;
    }


    double discount = 0;


    double finalAmount =
        applyCoupon(
            amount,
            discount
        );


    string paymentMethod;


    processPayment(
        finalAmount,
        paymentMethod
    );
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    AuthService auth;

    ProductService productService;


    // Load products when application starts
    loadProducts(productService);


    while (true)
    {
        cout << "\n\n";
        cout << "============================================\n";
        cout << "                  SMARTCART\n";
        cout << "============================================\n";

        cout << "1. Register Customer\n";
        cout << "2. Customer Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Payment Demo\n";
        cout << "5. Exit\n";


        cout << "\nEnter choice: ";


        int choice;
        cin >> choice;

// ====================================================
// CUSTOMER REGISTRATION
// ====================================================

if (choice == 1)
{
    string id;
    string name;
    string username;
    string password;
    string phone;
    string address;


    cout << "\n";
    cout << "============================================\n";
    cout << "          CUSTOMER REGISTRATION\n";
    cout << "============================================\n";


    // ----------------------------------------------------
    // CUSTOMER ID
    // ----------------------------------------------------

    cout << "Enter Customer ID: ";
    cin >> id;


    // Check duplicate Customer ID
    if (auth.userIdExists(id))
    {
        cout << "\nCustomer ID already exists!\n";
        cout << "Please use a different Customer ID.\n";

        continue;
    }


    // ----------------------------------------------------
    // NAME
    // ----------------------------------------------------

    cout << "Enter Name: ";
    cin >> name;


    // ----------------------------------------------------
    // USERNAME
    // ----------------------------------------------------

    cout << "Enter Username: ";
    cin >> username;


    // Check duplicate username
    if (auth.usernameExists(username))
    {
        cout << "\nUsername already exists!\n";
        cout << "Please use a different username.\n";

        continue;
    }


    // ----------------------------------------------------
    // PASSWORD
    // ----------------------------------------------------

    while (true)
    {
        cout << "Enter Password: ";
        cin >> password;


        if (!password.empty())
        {
            break;
        }


        cout << "Password cannot be empty!\n";
    }


    // ----------------------------------------------------
    // PHONE
    // ----------------------------------------------------

    while (true)
    {
        cout << "Enter Phone: ";
        cin >> phone;


        if (isValidPhone(phone))
        {
            break;
        }


        cout << "Invalid phone number!\n";
        cout << "Enter exactly 10 digits.\n";
    }


    // ----------------------------------------------------
    // ADDRESS
    // ----------------------------------------------------

    cout << "Enter Address: ";
    cin >> address;


    // ----------------------------------------------------
    // CREATE CUSTOMER
    // ----------------------------------------------------

    Customer customer(
        id,
        name,
        username,
        password,
        phone,
        address
    );


    // ----------------------------------------------------
    // REGISTER CUSTOMER
    // ----------------------------------------------------

    if (auth.registerCustomer(customer))
    {
        cout << "\n";
        cout << "Registration successful!\n";
    }
    else
    {
        cout << "\n";
        cout << "Registration failed!\n";
    }
}


        // ====================================================
        // CUSTOMER LOGIN
        // ====================================================

        else if (choice == 2)
        {
            string username;
            string password;


            cout << "\n";
            cout << "============================================\n";
            cout << "             CUSTOMER LOGIN\n";
            cout << "============================================\n";


            cout << "Username: ";
            cin >> username;


            cout << "Password: ";
            cin >> password;


            Customer* customer =
                auth.loginCustomer(
                    username,
                    password
                );


            if (customer != nullptr)
            {
                cout << "\nLogin successful!\n";


                customerMenu(
                    customer,
                    productService
                );
            }
            else
            {
                cout << "\nInvalid username or password!\n";
            }
        }


        // ====================================================
        // ADMIN LOGIN
        // ====================================================

        else if (choice == 3)
        {
            string username;
            string password;


            cout << "\n";
            cout << "============================================\n";
            cout << "               ADMIN LOGIN\n";
            cout << "============================================\n";


            cout << "Username: ";
            cin >> username;


            cout << "Password: ";
            cin >> password;


            Admin* admin =
                auth.loginAdmin(
                    username,
                    password
                );


            if (admin != nullptr)
            {
                cout << "\nAdmin login successful!\n";


                adminMenu(
                    admin,
                    productService
                );
            }
            else
            {
                cout << "\nInvalid admin username or password!\n";
            }
        }


        // ====================================================
        // PAYMENT DEMO
        // ====================================================

        else if (choice == 4)
        {
            standalonePayment();
        }


        // ====================================================
        // EXIT
        // ====================================================

        else if (choice == 5)
        {
            cout << "\n";
            cout << "============================================\n";
            cout << " Thank you for using SmartCart!\n";
            cout << "============================================\n";

            break;
        }


        else
        {
            cout << "\nInvalid choice!\n";
        }
    }


    return 0;
}