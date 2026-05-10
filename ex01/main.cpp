#include "Data.hpp"
#include "Serializer.hpp"
#include <cstdio>
#include <iostream>

int main(void) {
  Data data;
  data.val_int = 0;
  data.val_str = "str";
  uintptr_t raw = Serializer::serialize(&data);
  Data *ptr = Serializer::deserialize(raw);
  if (&data == ptr)
    std::cout << "Address Match: " << &data << " and " << ptr << std::endl;
  else
    std::cout << "Address Not Match: " << &data << " and " << ptr << std::endl;
  std::cout << "data.val_int: " << data.val_int << std::endl;
  std::cout << "data.val_str: " << data.val_str << std::endl;
  std::cout << "ptr->val_int: " << ptr->val_int << std::endl;
  std::cout << "ptr->val_str: " << ptr->val_str << std::endl;
  return (0);
}
