#include "order_book.hpp"
#include "mutex_order_book.hpp"
#include "lock_free_order_book.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

struct BenchmarkResult {
    double avg_latency_us;
    double throughput_ops;
};

template <typename BookType>
BenchmarkResult run_benchmark(size_t num_orders) {
    BookType book;
    std::vector<Order> orders;
    orders.reserve(num_orders);

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> price_dist(100.0, 200.0);
    std::uniform_int_distribution<int> qty_dist(1, 100);

    for (size_t i = 0; i < num_orders; ++i) {
        orders.push_back({i, price_dist(rng), static_cast<uint32_t>(qty_dist(rng)), (i % 2 == 0)});
    }

    auto start = std::chrono::steady_clock::now();
    for (const auto& order : orders) {
        book.add_order(order);
        if (order.id % 10 == 0) {
            book.remove_order(order.id);
        }
    }
    auto end = std::chrono::steady_clock::now();

    double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
    double avg_latency = elapsed_us / num_orders;
    double throughput = (num_orders / (elapsed_us / 1e6));

    return {avg_latency, throughput};
}

int main() {
    constexpr size_t NUM_ORDERS = 1'000'000;

    auto mutex_result = run_benchmark<MutexOrderBook>(NUM_ORDERS);
    auto lf_result = run_benchmark<LockFreeOrderBook>(NUM_ORDERS);

    std::cout << "=== Benchmark Results ===\n";
    std::cout << "Mutex OrderBook: Avg Latency = " << mutex_result.avg_latency_us
              << " us, Throughput = " << mutex_result.throughput_ops << " ops/sec\n";
    std::cout << "Lock-Free OrderBook: Avg Latency = " << lf_result.avg_latency_us
              << " us, Throughput = " << lf_result.throughput_ops << " ops/sec\n";

    std::ofstream latency_csv("../benchmarks/latency_results.csv");
    latency_csv << "Implementation,AvgLatency(us)\n";
    latency_csv << "Mutex," << mutex_result.avg_latency_us << "\n";
    latency_csv << "LockFree," << lf_result.avg_latency_us << "\n";

    std::ofstream throughput_csv("../benchmarks/throughput_results.csv");
    throughput_csv << "Implementation,Throughput(ops/sec)\n";
    throughput_csv << "Mutex," << mutex_result.throughput_ops << "\n";
    throughput_csv << "LockFree," << lf_result.throughput_ops << "\n";
}