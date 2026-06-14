cmake_minimum_required(VERSION 3.16)
project(LockFreeOrderBook LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Targets
add_executable(lock_free_order_book src/lock_free_order_book.cpp src/order_book.hpp)
add_executable(mutex_order_book src/mutex_order_book.cpp src/order_book.hpp)
add_executable(benchmark src/benchmark.cpp src/order_book.hpp)