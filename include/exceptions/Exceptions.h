#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Base exception for the entire SmartCart project
class SmartCartException : public std::exception {
protected:
    std::string message;

public:
    explicit SmartCartException(const std::string& msg);

    const char* what() const noexcept override;

    virtual ~SmartCartException() noexcept = default;
};


// Thrown when a product cannot be found
class ProductNotFoundException : public SmartCartException {
public:
    explicit ProductNotFoundException(const std::string& productId);
};


// Thrown when an invalid quantity is entered
class InvalidQuantityException : public SmartCartException {
public:
    explicit InvalidQuantityException(const std::string& msg);
};


// Thrown when requested quantity is greater than available stock
class InsufficientStockException : public SmartCartException {
public:
    explicit InsufficientStockException(const std::string& msg);
};


// Thrown when login credentials are incorrect
class InvalidLoginException : public SmartCartException {
public:
    explicit InvalidLoginException(const std::string& msg);
};


// Thrown when a file operation fails
class FileException : public SmartCartException {
public:
    explicit FileException(const std::string& msg);
};


// Thrown when payment information is invalid
class InvalidPaymentException : public SmartCartException {
public:
    explicit InvalidPaymentException(const std::string& msg);
};


// Thrown when an invalid order operation is attempted
class InvalidOrderOperationException : public SmartCartException {
public:
    explicit InvalidOrderOperationException(const std::string& msg);
};

#endif