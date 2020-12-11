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

//private:
  A      alloc;
  T*     elem;
  size_t sz;
  size_t space;
};


// Constructors
template<typename T, typename A>
vector_base<T, A>::vector_base (A a, size_t n)
{
  TRACE_FUNC;
  alloc = a;
  elem = a.allocate(n);
  sz = n;
  space = n;
}

template<typename T, typename A>
vector_base<T, A>::vector_base (vector_base&& v)
{
  TRACE_FUNC;
  for (T* ptr = elem; ptr < elem + sz; ++ptr)
    alloc.destroy(ptr);
  alloc.deallocate(elem, space);

  elem = v.elem;
  sz = v.sz;
  space = v.space;

  v.elem = nullptr;
  v.sz = 0;
  v.space = 0;
}


// Destructor
template<typename T, typename A>
vector_base<T, A>::~vector_base ()
{
  TRACE_FUNC;
  for (T* ptr = this->elem; ptr < this->elem + this->sz; ++ptr)
    this->alloc.destroy(ptr);
  alloc.deallocate(&elem[0], space);
}


#endif // VECTOR_BASE_H
