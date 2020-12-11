#ifndef TEST_CLASS_H
#define TEST_CLASS_H


#include "tracer.h"
#include <iostream>
#include <vector>


class H
{
public:
  H (bool s)
    : v( 1'000'000, 1 )
      , b{ s }
  {
    TRACE_FUNC;
  }

  H (H&& a)
    : v{ a.v }
      , b{ a.b }
  {
    TRACE_FUNC;
  }

  H (const H& a)
    : v{ a.v }
      , b{ a.b }
  {
    TRACE_FUNC;
    if (!b)
      throw std::runtime_error("exception from copying constructor");
  }

  ~H ()
  {
    TRACE_FUNC;
  }

private:
  std::vector<double> v;
  bool b{true};
};


class X
{
public:
  X ()
    : v( 1'000'000, 1 )
  {
    TRACE_FUNC;
  }


  ~X ()
  {
    TRACE_FUNC;
  }

private:
  std::vector<double> v;
};


#endif // TEST_CLASS_H
