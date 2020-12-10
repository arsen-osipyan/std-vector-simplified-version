#ifndef ALLOCATOR_H
#define ALLOCATOR_H


template<typename T>
class allocator
{
  public:
  T*   allocate   (int);
  void deallocate (T*, int);
  void construct  (T*, const T&);
  void destroy    (T*);
};

template<typename T>
T* allocator<T>::allocate (int n)
{
  T* ptr = static_cast<T*>(new char[sizeof(T) * n]);
}

template<typename T>
void allocator<T>::deallocate (T* obj, int n)
{
  delete[] static_cast<char*>(obj);
}

template<typename T>
void allocator<T>::construct (T* obj, const T& val)
{
  new(static_cast<void*>(obj)) T(val);
}

template<typename T>
void allocator<T>::destroy (T* obj)
{
  obj->~T();
}


#endif // ALLOCATOR_H
