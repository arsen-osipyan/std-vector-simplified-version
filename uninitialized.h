#ifndef UNINITIALIZED_H
#define UNINITIALIZED_H


#include <memory>


template<typename T, typename A = std::allocator<T>>
T* uninitialized_copy(T* first, T* last, T* target)
{
  A alloc;
  T* cur = target;
  try
  {
    for (; first != last; ++first, ++cur)
      alloc.construct(cur, *first);
    return target;
  }
  catch (...)
  {
    for (; target != cur; ++target)
      alloc.destroy(target);
    throw;
  }
}


template<typename T, typename A = std::allocator<T>>
T* uninitialized_copy(const T* first, const T* last, T* target)
{
  A alloc;
  T* cur = target;
  try
  {
    for (const T* ptr = first; ptr != last; ++ptr, ++cur)
      alloc.construct(cur, *ptr);
    return target;
  }
  catch (...)
  {
    for (; target != cur; ++target)
      alloc.destroy(target);
    throw;
  }
}


template<typename T, typename A = std::allocator<T>>
T* uninitialized_fill(T* first, T* last, const T& val)
{
  A alloc;
  T* cur = first;
  try
  {
    for (; cur != last; ++cur)
      alloc.construct(cur, val);
    return first;
  }
  catch (...)
  {
    for (; first != cur; ++first)
      alloc.destroy(first);
    throw;
  }
}


#endif // UNINITIALIZED_H
