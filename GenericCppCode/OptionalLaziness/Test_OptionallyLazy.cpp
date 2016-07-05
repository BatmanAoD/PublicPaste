#include <iostream>

#include "OptionallyLazy.hpp"

void PermitLazy(
    LAZY_PARAM(int) my_int)
{
  std::cout << "Called 'PermitLazy'." << std::endl;
  std::cout << "Got possibly-lazy int: " << my_int << std::endl;
}

int ExpensivelyGenerateInt(void)
{
  std::cerr << " <[( Generating int (pretend this call is expensive)! )]> ";
  std::cerr.flush();
  return 7;
}

int main(void)
{
  PermitLazy(LAZY_ARG(ExpensivelyGenerateInt()));
  PermitLazy(EAGER_ARG(ExpensivelyGenerateInt()));
  PermitLazy(EAGER_ARG(3));
  // See comment above `EAGER_ARG`
  // PermitLazy(ExpensivelyGenerateInt());
}
