# Lock-Free Order Book (C++ High-Frequency Trading Project)

A high-performance order book implementation designed for **high-frequency trading (HFT)** systems.  
The project leverages **lock-free data structures** (e.g., ring buffers, atomic operations) to minimize contention and reduce latency under extreme workloads.

The system is benchmarked against traditional **mutex-based designs**, demonstrating measurable improvements in both **latency** and **throughput**.  
This comparison highlights the advantages of lock-free concurrency in environments where **nanosecond-level performance** is critical.

## Key Features
- **[Lock-free design](ca://s?q=Lock-free_data_structures_in_C%2B%2B)** using atomic primitives for concurrent access.  
- **[Ring buffer architecture](ca://s?q=Ring_buffer_in_C%2B%2B)** optimized for cache locality and predictable memory usage.  
- **[Benchmarking framework](ca://s?q=Benchmarking_in_C%2B%2B)** to evaluate latency and throughput under realistic trading workloads.  
- **[Comparison with mutex-based models](ca://s?q=Mutex_vs_lock-free_in_C%2B%2B)** to quantify performance trade-offs.  
- **[Industry relevance](ca://s?q=Order_book_in_HFT)**: Demonstrates techniques used in production-grade HFT systems where deterministic performance is paramount.


## Roadmap Checklist

- [x] Phase 01 — Project Scaffold
- [x] Phase 02 — Baseline Mutex Order Book
- [x] Phase 03 — Lock-Free Core Implementation
- [x] Phase 04 — Memory Reclamation Strategy
- [x] Phase 05 — Benchmarking & Latency Profiling
- [x] Phase 06 — Recruiter Polish (Docs, CI/CD, Charts)

## Goals

- Showcase mastery of concurrency and lock-free programming.
- Demonstrate cache-aware design and hardware-level optimization.
- Provide reproducible benchmarks highlighting latency improvements.

## Structure

- `src/order_book.hpp` — Common interface for order book implementations.
- `src/lock_free_order_book.cpp` — Lock-free design using atomics.
- `src/mutex_order_book.cpp` — Baseline design using mutexes.
- `src/benchmark.cpp` — Benchmarking harness for performance comparison.

## Benchmark Results

| Implementation | Avg Latency (µs) | Throughput (ops/sec)  |
|----------------|------------------|-----------------------|
| Mutex          | 0.038544         | 25.9M                 |
| Lock-Free      | 0.019003         | 52.6M                 |

### Charts
![Latency Histogram](benchmarks/plots/latency_histogram.png)
![Throughput Chart](benchmarks/plots/throughput_chart.png)
![Combined Dual Axis](benchmarks/plots/combined_dual_axis.png)

> Latency and throughput are measured on very different scales.  
> Latency is in microseconds, throughput in millions of ops/sec.  
> To visualize both meaningfully, we use separate charts and a dual‑axis plot.  
> Lock‑free design achieved ~2× lower latency and ~2× higher throughput compared to the mutex baseline.
