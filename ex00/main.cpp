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
    double dmax = std::numeric_limits<double>::max();
    float fmax = std::numeric_limits<float>::max();
    dmax = fmax;
    std::stringstream ss;
    ss << dmax;
    std::string str = ss.str();
    // (void)argv;
    ScalarConverter::convert(argv[1]);
    return (0);
}
