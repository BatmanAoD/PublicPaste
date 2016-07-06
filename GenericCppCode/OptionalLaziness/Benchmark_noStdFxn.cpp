#ifdef USE_STD_FXN
#   error "USE_STD_FXN defined inside 'Benchmark_noStdFxn'!"
#endif

#include "Benchmark_noStdFxn.hpp"
#include "Benchmark_impl.hxx"

void DoBenchmark_noStdFxn(std::size_t num_iterations)
{
  std::cout << "Benchmarking implementation WITHOUT `std::function`." << std::endl;
  PerformBenchmark(num_iterations);
}
