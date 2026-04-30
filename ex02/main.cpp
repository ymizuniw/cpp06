#include <cstdio>
#include <cstring>
#include <iostream>

#include "ABC.hpp"
#include "Base.hpp"
#include <cstdlib>
#include <ctime>
#include <typeinfo>

Base *generate(void){
  int random = std::rand();
  if (0 <= random && random < RAND_MAX / 3)
    return (new (A));
  else if (RAND_MAX / 3 <= random && random < 2 * (RAND_MAX / 3))
    return (new (B));
  else
    return (new (C));
  return (NULL);
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
  Base *base = generate();
  try {
    identify(base);
    identify(*base);
  } catch (...) {
    delete (base);
  }
  delete (base);
  return (0);
}
