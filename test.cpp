#include "test.h"
#include "vector.h"
#include <vector>


constexpr int SIZE = 30'000;


class El
{
public:
  El (bool b)
  {
    TRACE_FUNC;
    if (!b) throw;
  }

  El (const El& e)
  {
    TRACE_FUNC;
    data = e.data;
  }

private:
  vector<double> data{SIZE};
};


void test_constructor ()
{

}

void test_memory_leak ()
{
  TRACE_FUNC;
  for (int i{0}; i < 10000; ++i)
  {
    vector<El> cur{ El(true), El(true), El(true), El(true), El(true) };
    std::cout << cur.size() << '\n';
  }
}
