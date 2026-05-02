#include "Data.hpp"
#include "Serializer.hpp"
#include <cstdio>
#include <iostream>

using namespace std;

int main(void) {
  Data data;
  data.val = 0;
  uintptr_t raw = Serializer::serialize(&data);
  std::cout << raw << std::endl;
  Data *ptr = Serializer::deserialize(raw);
  if (&data == ptr)
    std::cout << "Match: " << &data << " and " << ptr << std::endl;
  else
    std::cout << "Not Match: " << &data << " and " << ptr << std::endl;
  return (0);
}
