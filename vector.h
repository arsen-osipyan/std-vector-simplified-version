#ifndef VECTOR_H
#define VECTOR_H 1


#include "tracer.h"
#include "uninitialized.h"
#include "vector_base.h"
#include <iostream>
#include <initializer_list>
#include <memory>
#include <algorithm>


class out_of_range { };


template<typename T, typename A = std::allocator<T> >
class vector : private vector_base<T, A>
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
};


// Constructors
template<typename T, typename A>
vector<T, A>::vector ()
  : vector_base<T, A> (A(), 0)
{
  TRACE_FUNC;
}

template<typename T, typename A>
vector<T, A>::vector (size_t s)
  : vector_base<T, A> (A(), s)
{
  TRACE_FUNC;
  uninitialized_fill(&this->elem[0], &this->elem[this->sz], T());
}

template<typename T, typename A>
vector<T, A>::vector (std::initializer_list<T> lst)
  : vector_base<T, A> (A(), lst.size())
{
  TRACE_FUNC;
  uninitialized_copy(lst.begin(), lst.end(), this->elem);
}

template<typename T, typename A>
vector<T, A>::vector (const vector& arg)
  : vector_base<T, A> (A(), arg.size())
{
  TRACE_FUNC;
  uninitialized_copy(&arg.elem[0], &arg.elem[arg.sz], this->elem);
}

template<typename T, typename A>
vector<T, A>::vector (vector&& arg)
{
  TRACE_FUNC;
  for (T* ptr = this->elem; ptr < this->elem + this->sz; ++ptr)
    this->alloc.destroy(ptr);
  this->alloc.deallocate(this->elem, this->space);

  this->elem = arg.elem;
  this->sz = arg.sz;
  this->space = arg.space;

  arg.elem = nullptr;
  arg.sz = 0;
  arg.space = 0;
}

// Destructor
template<typename T, typename A>
vector<T, A>::~vector ()
{
  TRACE_FUNC;
}

// Operators overloading
template<typename T, typename A>
T& vector<T, A>::operator [] (size_t i)
{
  TRACE_FUNC;
  return this->elem[i];
}

template<typename T, typename A>
const T& vector<T, A>::operator [] (size_t i) const
{
  TRACE_FUNC;
  return this->elem[i];
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator= (const vector& arg)
{
  TRACE_FUNC;
  if (this == &arg) return *this;

  if (arg.sz <= this->space)
  {
    this->sz = arg.sz;
    uninitialized_copy(&arg[0], &arg[arg.sz], this->elem);
    for (size_t i{this->sz}; i < this->space; ++i)
      this->alloc.destroy(&this->elem[i]);
    return *this;
  }

  for (size_t i{0}; i < this->sz; ++i)
    this->alloc.destroy(&this->elem[i]);
  this->alloc.deallocate(this->elem, this->space);

  vector_base<T, A> p{ this->alloc, arg.sz };
  uninitialized_copy(&arg[0], &arg[arg.sz], p.elem);
  this->space = arg.sz;
  this->sz = arg.sz;
  this->elem = p.elem;

  return *this;
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator= (vector&& arg)
{
  TRACE_FUNC;

  for (T* ptr = this->elem; ptr < this->elem + this->sz; ++ptr)
    this->alloc.destroy(ptr);
  this->alloc.deallocate(this->elem, this->space);

  this->elem = arg.elem;
  this->sz = arg.sz;
  this->space = arg.space;

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
  if (newalloc <= this->space) return;
  vector_base<T, A> p{ A(), newalloc };
  uninitialized_copy(&this->elem[0], &this->elem[this->sz], p.elem);

  for (size_t i{0}; i < this->sz; ++i)
    this->alloc.destroy(&this->elem[i]);

  this->alloc.deallocate(&this->elem[0], this->space);
  this->elem = p.elem;
  this->space = newalloc;

  p.elem = nullptr;
  p.space = 0;
  p.sz = 0;
}

template<typename T, typename A>
void vector<T, A>::resize (size_t newsize, const T& val)
{
  TRACE_FUNC;
  reserve(newsize);

  if (newsize < this->sz)
  {
    for (T* ptr = this->elem + newsize; ptr < this->elem + this->sz; ++ptr)
      this->alloc.destroy(ptr);

    this->sz = newsize;
  }
  else
  {
    uninitialized_fill(&this->elem[this->sz], &this->elem[newsize], val);
    this->sz = newsize;
  }
}

template<typename T, typename A>
void vector<T, A>::push_back (const T& val)
{
  TRACE_FUNC;
  if (this->space == 0)
    reserve(sizeof(T));
  else if (this->sz == this->space)
    reserve(2*this->space);
  this->alloc.construct(&this->elem[this->sz], val);
  ++this->sz;
}

// Access with condition
template<typename T, typename A>
T& vector<T, A>::at (size_t i)
{
  TRACE_FUNC;
  if (i < 0 || i >= size())
    throw out_of_range();
  return this->elem[i];
}

template<typename T, typename A>
const T& vector<T, A>::at (size_t i) const
{
  TRACE_FUNC;
  if (i < 0 || i >= size())
    throw out_of_range();
  return this->elem[i];
}


#endif // VECTOR_H
