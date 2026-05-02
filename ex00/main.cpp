#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include "ScalarConverter.hpp"
#include <limits>

int main(int argc, char **argv)
{
    if (argc!=2)
      return (1);
    (void)argv;
    char const *special_args[] = {"-inff", "+inff", "-inf", "+inff", "nanf", "nan", NULL};
    char const *regular_args[] = {"a", "1", "1.5f", "1.5", NULL};
    char const **sp_ptr = special_args;
    while(*sp_ptr)
    {
      std::cout << "\n=======================\n" << std::endl;
      std::cout << "Test: " << *sp_ptr << "\n\n";
      ScalarConverter::convert(*sp_ptr);
      sp_ptr++;
    }
    char const **reg_ptr = regular_args;
    while(*reg_ptr)
    {
      std::cout << "\n=======================\n" << std::endl;
      std::cout << "Test: " << *reg_ptr << "\n\n";
      ScalarConverter::convert(*reg_ptr);
      reg_ptr++;
    }
    std::cout << "\n=======================" << std::endl;
    // ScalarConverter::convert(argv[1]);
    return (0);
}
