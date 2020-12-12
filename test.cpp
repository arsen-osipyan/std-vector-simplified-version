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

    assert_equal(v.size(), static_cast<size_t>(4));
    assert_equal(v.capacity(), static_cast<size_t>(4));
    assert_equal(v, vector<double>{0., 0., 0., 0.});

    v.resize(5, 1.);

    assert_equal(v.size(), static_cast<size_t>(5));
    assert_equal(v.capacity(), static_cast<size_t>(5));
    assert_equal(v, vector<double>{0., 0., 0., 0., 1.});

    v.resize(3, 1.);

    assert_equal(v.size(), static_cast<size_t>(3));
    assert_equal(v.capacity(), static_cast<size_t>(5));
    assert_equal(v, vector<double>{0., 0., 0.});

    v.resize(7, 2.);

    assert_equal(v.size(), static_cast<size_t>(7));
    assert_equal(v.capacity(), static_cast<size_t>(7));
    assert_equal(v, vector<double>{0., 0., 0., 2., 2., 2., 2.});

    vector<X> v1(2);

    assert_equal(v1.size(), static_cast<size_t>(2));
    assert_equal(v1.capacity(), static_cast<size_t>(2));

    v1.resize(4, X());

    assert_equal(v1.size(), static_cast<size_t>(4));
    assert_equal(v1.capacity(), static_cast<size_t>(4));

    v1.resize(1, X());

    assert_equal(v1.size(), static_cast<size_t>(1));
    assert_equal(v1.capacity(), static_cast<size_t>(4));
  }
  catch (...)
  {
    std::cout << "Fault";
  }
  std::cout << "END OF BLOCK\n" <<std::endl;
}

void test_push_back ()
{
  std::cout << "TEST PUSH_BACK():\n";
  try
  {
    vector<double> v;

    assert_equal(v.size(), static_cast<size_t>(0));
    assert_equal(v.capacity(), static_cast<size_t>(0));

    v.push_back(2.2);

    assert_equal(v.size(), static_cast<size_t>(1));
    assert_equal(v.capacity(), static_cast<size_t>(8));
    assert_equal(v, vector<double>{2.2});

    v.push_back(3.3);

    assert_equal(v.size(), static_cast<size_t>(2));
    assert_equal(v.capacity(), static_cast<size_t>(8));
    assert_equal(v, vector<double>{2.2, 3.3});

    v.push_back(3.3);
    v.push_back(3.3);
    v.push_back(3.3);
    v.push_back(3.3);
    v.push_back(3.3);
    v.push_back(3.3);
    v.push_back(3.3);

    assert_equal(v.size(), static_cast<size_t>(9));
    assert_equal(v.capacity(), static_cast<size_t>(16));
    assert_equal(v, vector<double>{2.2, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3, 3.3});

    vector<vector<double>> v1;

    assert_equal(v1.size(), static_cast<size_t>(0));
    assert_equal(v1.capacity(), static_cast<size_t>(0));

    v1.push_back(vector<double>{2.2});

    assert_equal(v1.size(), static_cast<size_t>(1));
    assert_equal(v1, vector<vector<double>>{vector<double>{2.2}});

    v1.push_back(vector<double>{2.3});

    assert_equal(v1.size(), static_cast<size_t>(2));
    assert_equal(v1, vector<vector<double>>{vector<double>{2.2}, vector<double>{2.3}});

    v1.push_back(vector<double>{2.3, 2.1, 2.0, 2.2, 2.3, 2.1, 2.0, 2.2});

    assert_equal(v1.size(), static_cast<size_t>(3));
    assert_equal(v1, vector<vector<double>>{vector<double>{2.2}, vector<double>{2.3},
                                            vector<double>{2.3, 2.1, 2.0, 2.2, 2.3, 2.1, 2.0, 2.2}});


//    for (size_t i{0}; i < 10'000; ++i)
//    {
//      vector<vector<X>> vec;
//      for (size_t j{0}; j < 10; ++j)
//      {
//        vec.push_back(vector<X>{});
//        for (size_t t{0}; t < 10; ++t)
//          vec[j].push_back(X());
//      }
//      std::cout << vec.size();
//    }

    vector<vector<double>> v2;
    vector<double>* pvd = nullptr;
    {
      vector<double> vd;
      for (size_t i{0}; i < 10; ++i)
        vd.push_back(i);
      v2.push_back(vd);
      pvd = &vd;
    }
    assert_equal(v2.size(), static_cast<size_t>(1));
    assert_equal(v2[0].size(), static_cast<size_t>(10));
    assert_equal(v2[0], vector<double>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    assert_equal(v2, vector<vector<double>>{vector<double>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}});
  }
  catch (...)
  {
    std::cout << "Fault" << std::endl;
  }
  std::cout << "END OF BLOCK\n" <<std::endl;
}
