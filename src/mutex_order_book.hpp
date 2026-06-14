#pragma once
#include "order_book.hpp"
#include <unordered_map>
#include <mutex>
#include <sstream>

class MutexOrderBook : public OrderBook {
private:
    std::unordered_map<uint64_t, Order> orders_;
    mutable std::mutex mtx_;

public:
    void add_order(const Order& order) override {
        std::lock_guard<std::mutex> lock(mtx_);
        orders_[order.id] = order;
    }

    void remove_order(uint64_t order_id) override {
        std::lock_guard<std::mutex> lock(mtx_);
        orders_.erase(order_id);
    }

    std::string snapshot() const override {
        std::lock_guard<std::mutex> lock(mtx_);
        std::ostringstream oss;
        for (const auto& [id, order] : orders_) {
            oss << "ID: " << id
                << " Price: " << order.price
                << " Qty: " << order.quantity
                << " Side: " << (order.is_buy ? "BUY" : "SELL")
                << "\n";
        }
        return oss.str();
    }
};