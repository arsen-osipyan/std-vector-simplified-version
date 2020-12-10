#ifndef TEST_H
#define TEST_H


#include "vector.h"
#include <iostream>


template<typename T>
void print_vector(const vector<T>& v)
{
  std::cout << "{ ";
  for (size_t i{0}; i < v.size(); ++i)
  {
    std::cout << v[i];
    if (i != v.size() - 1) std::cout << ", ";
  }
  std::cout << " }";
}


template<typename T>
void vector_equality (const vector<T>& a, const vector<T>& b)
{
  if (a.size() != b.size())
  {
    print_vector(a);
    std::cout << " not equal with ";
    print_vector(b);
    std::cout << std::endl;
    return;
  }

  for (size_t i{0}; i < a.size(); ++i)
  {
    if (a[i] != b[i])
    {
      print_vector(a);
      std::cout << " not equal with ";
      print_vector(b);
      std::cout << std::endl;
      return;
    }
  }

  std::cout << "OK" << std::endl;
}

template<typename T>
void value_equality (const T& a, const T& b)
{
  if (a != b) std::cout << a << " not equal " << b << std::endl;
  else std::cout << "OK" << std::endl;
}


void test_constructor ();
void test_memory_leak ();


#endif // TEST_H
