#include "Benchmark_stdFxn.hpp"

#define USE_STD_FXN
#include "Benchmark_impl.hxx"

void DoBenchmark_stdFxn(std::size_t num_iterations)
{
  std::cout << "Benchmarking implementation WITH `std::function`." << std::endl;
  PerformBenchmark(num_iterations);
}
