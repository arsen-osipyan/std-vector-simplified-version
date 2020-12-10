#include "vector.h"
#include "tracer.h"
#include "test.h"

#include <iostream>


int main()
{
  TRACE_FUNC;

  test_memory_leak();

  return 0;
}
