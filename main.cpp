#include "vector.h"
#include "tracer.h"
#include "test.h"

#include <iostream>


int main()
{
  TRACE_FUNC;

  test_resize();
  test_push_back();

  return 0;
}
