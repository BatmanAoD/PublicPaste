#pragma once

#include <chrono>
#include <iostream>

#define BENCHMARK_EXPR(expr) \
    do { \
      std::cout << "Benchmarking `" #expr "`:\n"; \
      auto start_time = std::chrono::high_resolution_clock::now(); \
      (expr); \
      auto end_time = std::chrono::high_resolution_clock::now(); \
      std::cout << "Microseconds elapsed: " \
        << std::chrono::duration_cast<std::chrono::microseconds>( \
                end_time - start_time).count() \
        << std::endl; \
    } while (false)
