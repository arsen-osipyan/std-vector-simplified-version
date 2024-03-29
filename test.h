﻿#ifndef TEST_H
#define TEST_H


#include "vector.h"
#include <iostream>
#include <vector>


template<typename T>
void assert_equal (const T& a, const T& b)
{
  if (a == b) std::cout << "- OK" << std::endl;
  else std::cout << a << " not equal " << b << std::endl;
}


void test_reserve ();
void test_constructor ();
void test_resize ();
void test_push_back ();
void test_move_operator ();
void test_copy_operator ();


#endif // TEST_H
