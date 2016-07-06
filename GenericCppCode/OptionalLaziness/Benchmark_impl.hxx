#pragma once

#include "Benchmarking.hpp"

#include "OptionallyLazy.hpp"

static auto sum = 0;

static void PermitLazy(
    OPTIONALLY_LAZY(int) my_int)
{
  sum += my_int;
}

#define DEF_ITERATE_FUNC(eval_type) \
  static void Call_##eval_type(std::size_t num_iterations) \
{ \
  for (std::size_t i = 0; i < num_iterations; ++i) \
  { \
    PermitLazy(eval_type ## _ARG(3)); \
  } \
}

DEF_ITERATE_FUNC(LAZY)
DEF_ITERATE_FUNC(EAGER)

static void PerformBenchmark(std::size_t num_iterations)
{
  BENCHMARK_EXPR(Call_LAZY(num_iterations));
  BENCHMARK_EXPR(Call_EAGER(num_iterations));
}
