#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H


#include "tracer.h"
#include <iostream>
#include <memory>

template<typename T, typename A = std::allocator<T> >
class vector_base
{
public:
  vector_base (A, size_t);
  vector_base (vector_base&&);

  ~vector_base ();

  vector_base& operator= (vector_base&&);

  A      alloc;
  T*     elem;
  size_t sz;
  size_t space;
};


// Constructors
template<typename T, typename A>
vector_base<T, A>::vector_base (A a, size_t n)
  : alloc{ a }
    , elem{ a.allocate(n) }
    , sz{ n }
    , space{ n }
{
  TRACE_FUNC;
}

template<typename T, typename A>
vector_base<T, A>::vector_base (vector_base&& v)
  : elem{ v.elem }
    , sz{ v.sz }
    , space{ v.space }
{
  TRACE_FUNC;
  v.elem = nullptr;
  v.sz = 0;
  v.space = 0;
}


// Operator overloading
template<typename T, typename A>
vector_base<T, A>& vector_base<T, A>::operator= (vector_base<T, A>&& arg)
{
  TRACE_FUNC;
  alloc.deallocate(elem, space);

  elem = arg.elem;
  sz = arg.sz;
  space = arg.space;

  arg.elem = nullptr;
  arg.sz = 0;
  arg.space = 0;

  return *this;
}


// Destructor
template<typename T, typename A>
vector_base<T, A>::~vector_base ()
{
  TRACE_FUNC;
  alloc.deallocate(&elem[0], space);
}


#endif // VECTOR_BASE_H
