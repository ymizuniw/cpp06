#include "ScalarConverter.hpp"
#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <exception>

typedef enum e_scalar_convert_status{
    SC_STATUS_DOUBLE,
    SC_STATUS_FLOAT,
    SC_STATUS_INT,
    SC_STATUS_CHAR,
    SC_STATUS_MINUS_INF,
    SC_STATUS_PLUS_INF,
    SC_STATUS_NAN,
    SC_STATUS_ERROR
} t_scalar_convert_status;

//this shoul return the specific types
t_scalar_convert_status validate_num(std::string num)
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
        return (SC_STATUS_INT);
    if (num.at(i)=='.')
    {
        i++;
        if (i==num.length())
            return (SC_STATUS_DOUBLE);
        else if (num.at(i)!='f' && !std::isdigit(num.at(i)))
            return (SC_STATUS_ERROR);
    }
    if (num.at(i)=='f')
    {
        i++;
        if (i==num.length())
            return (SC_STATUS_FLOAT);
        else
            return (SC_STATUS_ERROR);
    }
    // fractional part
    while(i<num.length())
    {
        if (!std::isdigit(num.at(i)))
            break;
        i++;
    }
    if (i==num.length())
        return (SC_STATUS_DOUBLE);
    if (num.at(i)=='f')
    {
        i++;
        if (i==num.length())
            return (SC_STATUS_FLOAT);
        else
            return (SC_STATUS_ERROR);
    }
    return (SC_STATUS_ERROR);
}

int validate_char(std::string num)
{
    if(num.length()==1 && !std::isdigit(num.at(0)))
        return (1);
    return (0);
}



void printResult(int num_type, std::string num)
{
    std::stringstream ss_int(num);
    std::stringstream ss_float(num);
    std::stringstream ss_double(num);
    int converted_int = 0;
    float converted_float = 0.f;
    double converted_double = 0.0;

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
    else if (num_type==SC_STATUS_DOUBLE)
    {
        
    }
    else if (num_type==SC_STATUS_FLOAT)
    {
        
    }
    else if (num_type==SC_STATUS_INT)
    {
        
    }
    else if (num_type==SC_STATUS_CHAR)
    {
        converted_int = static_cast<int>(num.at(0));
        converted_float = static_cast<float>(num.at(0));
        converted_double = static_cast<double>(num.at(0));
        if (std::isprint(converted_int))
            std::cout << "char: " << static_cast<unsigned char>(converted_int) << "\n";
        else
            std::cout << "char: " << "Non displayable\n";
        std::cout << "int: " << converted_int << "\n";
        std::cout << "float: " << converted_float << "f\n";
        std::cout << "double: " << converted_double << std::endl;
    }
    else
    {
        std::cout << "[Invalid Argment]: " << num << std::endl;
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

//     int num_type = SC_STATUS_ERROR;
//     double dmax = std::numeric_limits<double>::max();
//     double dmin = std::numeric_limits<double>::min();
//     float fmax = std::numeric_limits<float>::max();
//     float fmin = std::numeric_limits<float>::min();

//     std::stringstream ss_dmax;
//     std::stringstream ss_dmin;
//     std::stringstream ss_fmax;
//     std::stringstream ss_fmin;
    
//     ss_dmax<<dmax;
//     ss_dmin<<dmin;
//     ss_fmax<<fmax;
//     ss_fmin<<fmin;
// // std::cout << num << std::endl;
//     std::string s_dmax = ss_dmax.str();
//     std::string s_dmin = ss_dmin.str();
//     std::string s_fmax = ss_fmax.str();
//     std::string s_fmin = ss_fmin.str();

    std::cout << fmax << std::endl;
    if (num=="-inff" || num=="-inf")
        num_type = SC_STATUS_MINUS_INF;
    else if (num=="inff" || num=="inf")
        num_type = SC_STATUS_PLUS_INF;
    else if (num=="nanf" || num=="nan")
        num_type = SC_STATUS_NAN;
    else if (validate_char(num))
        num_type = SC_STATUS_CHAR;
    else
        num_type = validate_num(num);
    printResult(num_type, num);
}
