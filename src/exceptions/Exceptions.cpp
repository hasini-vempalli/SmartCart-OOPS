#include "exceptions/Exceptions.h"

// ==================== SmartCartException ====================

SmartCartException::SmartCartException(const std::string& msg)
    : message(msg) {
}

const char* SmartCartException::what() const noexcept {
    return message.c_str();
}


// ==================== ProductNotFoundException ====================

ProductNotFoundException::ProductNotFoundException(
    const std::string& productId)
    : SmartCartException(
        "Product with ID '" + productId + "' was not found.") {
}


// ==================== InvalidQuantityException ====================

InvalidQuantityException::InvalidQuantityException(
    const std::string& msg)
    : SmartCartException(msg) {
}


// ==================== InsufficientStockException ====================

InsufficientStockException::InsufficientStockException(
    const std::string& msg)
    : SmartCartException(msg) {
}


// ==================== InvalidLoginException ====================

InvalidLoginException::InvalidLoginException(
    const std::string& msg)
    : SmartCartException(msg) {
}


// ==================== FileException ====================

FileException::FileException(
    const std::string& msg)
    : SmartCartException(msg) {
}


// ==================== InvalidPaymentException ====================

InvalidPaymentException::InvalidPaymentException(
    const std::string& msg)
    : SmartCartException(msg) {
}


// ==================== InvalidOrderOperationException ====================

InvalidOrderOperationException::InvalidOrderOperationException(
    const std::string& msg)
    : SmartCartException(msg) {
}