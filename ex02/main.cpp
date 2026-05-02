#include "ABC.hpp"
#include "Base.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <iostream>
#include <typeinfo>
#include <unistd.h>

/*
    The grounds of this implementation is at 5)b)iii) from:
    https://en.cppreference.com/cpp/language/dynamic_cast
*/

Base *generate(void) {
  int r = std::rand() % 3;
  if (r == 0)
    return new A();
  if (r == 1)
    return new B();
  return new C();
}

void identify(Base *p) {
  A *a = dynamic_cast<A *>(p);
  B *b = dynamic_cast<B *>(p);
  C *c = dynamic_cast<C *>(p);
  if (a != NULL)
    std::cout << "PtrType: A" << std::endl;
  if (b != NULL)
    std::cout << "PtrType: B" << std::endl;
  if (c != NULL)
    std::cout << "PtrType: C" << std::endl;
}

void identify(Base &p) {
  int casted = 1;
  try {
    A a = dynamic_cast<A &>(p);
  } catch (std::bad_cast &e) {
    casted = 0;
  }
  if (casted)
    std::cout << "RefType: A" << std::endl;
  casted = 1;
  try {
    B b = dynamic_cast<B &>(p);
  } catch (std::bad_cast &e) {
    casted = 0;
  }
  if (casted)
    std::cout << "RefType: B" << std::endl;
  casted = 1;
  try {
    C c = dynamic_cast<C &>(p);
  } catch (std::bad_cast &e) {
    casted = 0;
  }
  if (casted)
    std::cout << "RefType: C" << std::endl;
}

int main(void) {

  std::srand(static_cast<unsigned int>(std::time(NULL)));
  Base *base = NULL;
  try {
    base = generate();
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    return (1);
  }
  try {
    identify(base);
    identify(*base);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    delete (base);
    return (1);
  }
  delete (base);
  return (0);
}
