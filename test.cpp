#include "test.h"
#include "vector.h"
#include "test_class.h"
#include <vector>


void test_constructor ()
{
  TRACE_FUNC;
  for (int i{0}; i < 10'000; ++i)
  {
    try
    {
      vector<H> v{vector<H>{H(true), H(false), H(true), H(true), H(true)}};
      std::cout << "v.size(): " << v.size() << std::endl;
    }
    catch (...)
    {
      std::cerr << "i: " << i << std::endl;
    }
  }
}

void test_resize ()
{
  std::cout << "TEST RESIZE():\n";
  try
  {
    vector<double> v(4);

    value_equality(v.size(), static_cast<size_t>(4));
    value_equality(v.capacity(), static_cast<size_t>(4));
    vector_equality(v, vector<double>{0., 0., 0., 0.});

    v.resize(5, 1.);

    value_equality(v.size(), static_cast<size_t>(5));
    value_equality(v.capacity(), static_cast<size_t>(5));
    vector_equality(v, vector<double>{0., 0., 0., 0., 1.});

    v.resize(3, 1.);

    value_equality(v.size(), static_cast<size_t>(3));
    value_equality(v.capacity(), static_cast<size_t>(5));
    vector_equality(v, vector<double>{0., 0., 0.});

    v.resize(7, 2.);

    value_equality(v.size(), static_cast<size_t>(7));
    value_equality(v.capacity(), static_cast<size_t>(7));
    vector_equality(v, vector<double>{0., 0., 0., 2., 2., 2., 2.});

    vector<X> v1(2);

    value_equality(v1.size(), static_cast<size_t>(2));
    value_equality(v1.capacity(), static_cast<size_t>(2));

    v1.resize(4, X());

    value_equality(v1.size(), static_cast<size_t>(4));
    value_equality(v1.capacity(), static_cast<size_t>(4));

    v1.resize(1, X());

    value_equality(v1.size(), static_cast<size_t>(1));
    value_equality(v1.capacity(), static_cast<size_t>(4));
  }
  catch (...)
  {
    std::cout << "Fault";
  }
  std::cout << "END OF BLOCK\n" <<std::endl;
}
