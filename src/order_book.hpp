#pragma once

#include <cstdint>
#include <string>

struct Order {
    uint64_t id;
    double price;
    uint32_t quantity;
    bool is_buy;
};

class OrderBook {
public:
    virtual ~OrderBook() = default;

    virtual void add_order(const Order& order) = 0;
    virtual void remove_order(uint64_t order_id) = 0;
    virtual std::string snapshot() const = 0;
};