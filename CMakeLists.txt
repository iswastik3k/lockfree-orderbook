cmake_minimum_required(VERSION 3.10)
project(lockfree_orderbook)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -pthread")

add_executable(benchmark
    src/benchmark.cpp
    src/order_book.hpp
    src/mutex_order_book.hpp
    src/lock_free_order_book.hpp
)