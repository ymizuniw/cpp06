#include "ScalarConverter.hpp"
#include <cctype>
#include <string>
#include <iostream>
#include <sstream>

int validate_num(std::string num)
{
    // int part
    size_t i = 0;
    while(i<num.length())
    {
        if (!std::isdigit(num.at(i)))
            break;
        i++;
    }
    if (i==num.length())
        return 1;
    if (num.at(i)=='.')
        i++;
    if (i==num.length())
        return (1);
    // fractional part
    while(i<num.length())
    {
        if (!std::isdigit(num.at(i)))
            break;
        i++;
    }
    if (i==num.length())
        return (1);
    if (num.at(i)=='f')
        i++;
    else
        return (0);
    if (i==num.length())
        return (1);
    return (0);
}

typedef enum e_scalar_convert_status{
    SC_STATUS_CONVERTIBLE,
    SC_STATUS_MINUS_INF,
    SC_STATUS_PLUS_INF,
    SC_STATUS_NAN,
    SC_STATUS_ERROR
} t_scalar_convert_status;

void printResult(int num_type, std::string num)
{
    if (num_type==SC_STATUS_MINUS_INF)
    {
        std::cout << "char: " << "impossible\n";
        std::cout << "int: " << "impossible\n";
        std::cout << "float: " << "-inff\n";
        std::cout << "double: " << "-inf" << std::endl;
    }
    else if (num_type==SC_STATUS_PLUS_INF)
    {
        std::cout << "char: " << "impossible\n";
        std::cout << "int: " << "impossible\n";
        std::cout << "float: " << "+inff\n";
        std::cout << "double: " << "+inf" << std::endl;
    }
    else if (num_type==SC_STATUS_NAN)
    {
        std::cout << "char: " << "impossible\n";
        std::cout << "int: " << "impossible\n";
        std::cout << "float: " << "nanf\n";
        std::cout << "double: " << "nan" << std::endl;
    }
    else if (num_type==SC_STATUS_CONVERTIBLE)
    {
        std::stringstream ss_int(num);
        std::stringstream ss_float(num);
        std::stringstream ss_double(num);
        int converted_int = 0;
        float converted_float = 0.f;
        double converted_double = 0.0;
        ss_int >> converted_int;
        ss_float >> converted_float;
        ss_double >> converted_double;
        
        if (std::isprint(converted_int))
            std::cout << "char: " << static_cast<unsigned char>(converted_int) << "\n";
        else
            std::cout << "char: " << "Non displayable\n";
        std::cout << "int: " << converted_int << "\n";
        std::cout << "float: " << converted_float << "f\n";
        std::cout << "double: " << converted_double << std::endl;
    }
}

void ScalarConverter::convert(std::string num){

    if (num.empty())
    {
        std::cout << "num is empty!" << std::endl;
        return ;
    }

    //specific cases
    // 1. -inff OR +inff OR nanf -> only float handles
    // 2. -inf OR +inf OR nan -> only double handles
    // 3. the num is more than one characters or non-displayable, char handles it properly.
    // 4. FLOAT_MIN > num || FLOAT_MAX < num and within double, how does it behave?

    int num_type = SC_STATUS_ERROR;

    if (num=="-inff" || num=="-inf")
        num_type = SC_STATUS_MINUS_INF;
    else if (num=="inff" || num=="inf")
        num_type = SC_STATUS_PLUS_INF;
    else if (num=="nanf" || num=="nan")
        num_type = SC_STATUS_NAN;
    else if (validate_num(num))
        num_type = SC_STATUS_CONVERTIBLE;
    else
        num_type = SC_STATUS_ERROR;
    printResult(num_type, num);
}

int main(void)
{
    ScalarConverter::convert("1.4f");
}
