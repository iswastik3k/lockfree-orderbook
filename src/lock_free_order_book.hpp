#pragma once
#include "order_book.hpp"
#include <atomic>
#include <vector>
#include <sstream>

struct alignas(64) AtomicSlot {
    std::atomic<uint64_t> id{0};
    std::atomic<double> price{0.0};
    std::atomic<uint32_t> quantity{0};
    std::atomic<bool> is_buy{false};
};

class LockFreeOrderBook : public OrderBook {
private:
    static constexpr size_t SIZE = 1024;
    std::vector<AtomicSlot> slots_;
    std::atomic<size_t> write_index_{0};

public:
    LockFreeOrderBook() : slots_(SIZE) {}

    void add_order(const Order& order) override {
        size_t idx = write_index_.fetch_add(1, std::memory_order_relaxed) % SIZE;
        slots_[idx].id.store(order.id, std::memory_order_release);
        slots_[idx].price.store(order.price, std::memory_order_release);
        slots_[idx].quantity.store(order.quantity, std::memory_order_release);
        slots_[idx].is_buy.store(order.is_buy, std::memory_order_release);
    }

    void remove_order(uint64_t order_id) override {
        for (auto& slot : slots_) {
            if (slot.id.load(std::memory_order_acquire) == order_id) {
                slot.quantity.store(0, std::memory_order_release);
                break;
            }
        }
    }

    std::string snapshot() const override {
        std::ostringstream oss;
        for (const auto& slot : slots_) {
            uint64_t id = slot.id.load(std::memory_order_acquire);
            if (id != 0) {
                oss << "ID: " << id
                    << " Price: " << slot.price.load(std::memory_order_acquire)
                    << " Qty: " << slot.quantity.load(std::memory_order_acquire)
                    << " Side: " << (slot.is_buy.load(std::memory_order_acquire) ? "BUY" : "SELL")
                    << "\n";
            }
        }
        return oss.str();
    }
};