#include "Benchmark_stdFxn.hpp"
#include "Benchmark_noStdFxn.hpp"

#ifndef NUM_ITERS
  static const auto NUM_ITERS = 10000000;
#endif

int main(void)
{
  DoBenchmark_stdFxn(NUM_ITERS);
  DoBenchmark_noStdFxn(NUM_ITERS);
}
