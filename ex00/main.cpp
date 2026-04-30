#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include "ScalarConverter.hpp"
#include <limits>

/*
    valid
    char
    "1"
    "a"
    "A"
    ""
    int
    1
    0
    100
    2147483647
    -2147483648

    float
    1.0f
    100.f
    2147483647.1f
    -2147483648.1f

    double
    1.0


    invalid
    2147483648
    -2147483649
*/

int main(int argc, char **argv)
{
    if (argc!=2)
        return (1);
    /*
        Here are all patterns:
        char : one char
        int : only int
        float : suffix "f", -inff, +inff, nanf
        double : ., -inf, +inf nan

    */

    ScalarConverter::convert(argv[1]);
    return (0);
}
