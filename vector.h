#ifndef VECTOR_H
#define VECTOR_H 1


#include "tracer.h"
#include "uninitialized.h"
#include <iostream>
#include <initializer_list>
#include <memory>
#include <algorithm>


class out_of_range { };


template<typename T, typename A = std::allocator<T> >
class vector
{
public:
  vector ();
  explicit vector (size_t);
  vector (std::initializer_list<T>);
  vector (const vector&);
  vector (vector&&);
  ~vector ();

  // Memory operation methods
  void reserve   (size_t);
  void resize    (size_t, const T&);
  void push_back (const T&);

  // Access with verification
  T& at (size_t);
  const T& at (size_t) const;

  // Access to private parameters
  size_t capacity () const { return this->space; }
  size_t size     () const { return this->sz; }

  // Operators overloading
  T&       operator[] (size_t);
  const T& operator[] (size_t) const;
  vector&  operator=  (const vector&);
  vector&  operator=  (vector&&);

private:
  A   alloc;
  T*  elem;
  size_t sz;
  size_t space;
};


// Constructors
template<typename T, typename A>
vector<T, A>::vector ()
  : elem{ nullptr }
    , sz{ 0 }
    , space{ 0 }
{
  TRACE_FUNC;
}

template<typename T, typename A>
vector<T, A>::vector (size_t s)
  : elem{ alloc.allocate(s) }
    , sz{ s }
    , space{ s }
{
  TRACE_FUNC;
  for (size_t i{0}; i < sz; ++i)
    alloc.construct(&elem[i], T());
//  uninitialized_fill(&elem[0], &elem[sz], T());
}

template<typename T, typename A>
vector<T, A>::vector (std::initializer_list<T> lst)
  : elem{ alloc.allocate(lst.size())}
    , sz{ lst.size() }
    , space{ lst.size() }
{
  TRACE_FUNC;
  uninitialized_copy(lst.begin(), lst.end(), elem);
}

template<typename T, typename A>
vector<T, A>::vector (const vector& arg)
  : elem{ alloc.allocate(arg.sz) }
    , sz{ arg.sz }
    , space{ arg.sz }
{
  TRACE_FUNC;
  for (size_t i{0}; i < sz; ++i)
    alloc.construct(&elem[i], arg[i]);
//  uninitialized_copy(&arg.elem[0], &arg.elem[arg.sz], elem);
}

template<typename T, typename A>
vector<T, A>::vector (vector&& arg)
  : elem{ arg.elem }
    , sz{ arg.sz }
    , space{ arg.space }
{
  TRACE_FUNC;
  for (T* ptr = elem; ptr < elem + sz; ++ptr)
    alloc.destroy(ptr);
  alloc.deallocate(elem, space);
  arg.elem = nullptr;
  arg.sz = 0;
  arg.space = 0;
}

// Destructor
template<typename T, typename A>
vector<T, A>::~vector ()
{
  TRACE_FUNC;
  for (T* ptr = elem; ptr < elem + sz; ++ptr)
    alloc.destroy(ptr);
  alloc.deallocate(elem, space);
}

// Operators overloading
template<typename T, typename A>
T& vector<T, A>::operator [] (size_t i)
{
  TRACE_FUNC;
  return elem[i];
}

template<typename T, typename A>
const T& vector<T, A>::operator [] (size_t i) const
{
  TRACE_FUNC;
  return elem[i];
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator= (const vector& arg)
{
  TRACE_FUNC;
  if (this == &arg) return *this;

  if (arg.sz <= space)
  {
    sz = arg.sz;
    uninitialized_copy(&arg[0], &arg[arg.sz], elem);
    for (size_t i{sz}; i < space; ++i)
      alloc.destroy(&elem[i]);
    return *this;
  }

  for (size_t i{0}; i < sz; ++i)
    alloc.destroy(&elem[i]);
  alloc.deallocate(elem, space);

  T* p = alloc.allocate(arg.sz);
  uninitialized_copy(&arg[0], &arg[arg.sz], p);
  space = arg.sz;
  sz = arg.sz;
  elem = p;

  return *this;
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator= (vector&& arg)
{
  TRACE_FUNC;

  for (T* ptr = elem; ptr < elem + sz; ++ptr)
    alloc.destroy(ptr);
  alloc.deallocate(elem, space);

  elem = arg.elem;
  sz = arg.sz;
  space = arg.space;

  arg.elem = nullptr;
  arg.sz = 0;
  arg.space = 0;

  return *this;
}

// Memory operation
template<typename T, typename A>
void vector<T, A>::reserve (size_t newalloc)
{
  TRACE_FUNC;
  if (newalloc <= space) return;
  T* p = alloc.allocate(newalloc);
  uninitialized_copy(&elem[0], &elem[sz], p);

  for (size_t i{0}; i < sz; ++i)
    alloc.destroy(&elem[i]);

  alloc.deallocate(elem, space);
  elem = p;
  space = newalloc;
}

template<typename T, typename A>
void vector<T, A>::resize (size_t newsize, const T& val)
{
  TRACE_FUNC;
  reserve(newsize);

  if (newsize < sz)
  {
    for (T* ptr = elem; ptr < elem + sz; ++ptr)
      alloc.destroy(ptr);

    uninitialized_copy(&elem[0], &elem[newsize], val);
    sz = newsize;
  }
  else
  {
    uninitialized_copy(&elem[sz], &elem[newsize], val);
    sz = newsize;
  }
}

template<typename T, typename A>
void vector<T, A>::push_back (const T& val)
{
  TRACE_FUNC;
  if (space == 0)
    reserve(sizeof(T));
  else if (sz == space)
    reserve(2*space);
  alloc.construct(&elem[sz], val);
  ++sz;
}

// Access with condition
template<typename T, typename A>
T& vector<T, A>::at (size_t i)
{
  TRACE_FUNC;
  if (i < 0 || i >= size())
    throw out_of_range();
  return elem[i];
}

template<typename T, typename A>
const T& vector<T, A>::at (size_t i) const
{
  TRACE_FUNC;
  if (i < 0 || i >= size())
    throw out_of_range();
  return elem[i];
}





#endif // VECTOR_H
