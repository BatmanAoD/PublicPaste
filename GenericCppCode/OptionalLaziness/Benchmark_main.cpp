#include "Benchmark_stdFxn.hpp"
#include "Benchmark_noStdFxn.hpp"

static const auto NUM_ITERS = 10000000;

int main(void)
{
  DoBenchmark_stdFxn(NUM_ITERS);
  DoBenchmark_noStdFxn(NUM_ITERS);
}
