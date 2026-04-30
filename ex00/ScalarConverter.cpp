#include "ScalarConverter.hpp"
#include <cctype>
#include <cstring>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

typedef enum e_scalar_convert_status {
  SC_STATUS_CHAR,
  SC_STATUS_INT,
  SC_STATUS_FLOAT,
  SC_STATUS_DOUBLE,
  SC_STATUS_MINUS_INFF,
  SC_STATUS_PLUS_INFF,
  SC_STATUS_MINUS_INF,
  SC_STATUS_PLUS_INF,
  SC_STATUS_NANF,
  SC_STATUS_NAN,
  SC_STATUS_ERROR
} t_scalar_convert_status;

typedef struct s_scalar_values {
  char sc_char;
  int sc_int;
  float sc_float;
  double sc_double;
  int sc_nanf;
  int sc_nan;
  int sc_char_non_print;
  int sc_char_impossible;
  int sc_int_impossible;
  int sc_float_impossible;
  int sc_double_impossible;
} t_scalar_values;

//this shoul return the specific types
t_scalar_convert_status validate_num(std::string num)
{
    // int part
    size_t i = 0;

    if (num.at(i) == '-' || num.at(i) == '+')
      i++;
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

t_scalar_convert_status DetectType(std::string num) {

  t_scalar_convert_status num_type = SC_STATUS_ERROR;

  if (num == "-inff")
    num_type = SC_STATUS_MINUS_INFF;
  else if (num == "-inf")
    num_type = SC_STATUS_MINUS_INF;
  else if (num == "+inff")
    num_type = SC_STATUS_PLUS_INFF;
  else if (num == "+inf")
    num_type = SC_STATUS_PLUS_INF;
  else if (num == "nanf")
    num_type = SC_STATUS_NANF;
  else if (num == "nan")
    num_type = SC_STATUS_NANF;
  else if (validate_char(num))
    num_type = SC_STATUS_CHAR;
  else
    num_type = validate_num(num);
  return (num_type);
}

void ConvertActual(t_scalar_values *sc_vals, t_scalar_convert_status sc_stat,
                   std::string num) {

  std::stringstream ss(num);

  // NORMAL TYPES SWITCH CASE
  switch (static_cast<int>(sc_stat)) {
  case SC_STATUS_CHAR:
    if (!std::isprint(num.at(0)))
      sc_vals->sc_char_non_print = 1;
    else
      ss >> sc_vals->sc_char;
    break;
  case SC_STATUS_INT:
    ss >> sc_vals->sc_int;
    if (ss.fail())
      sc_vals->sc_int_impossible = 1;
    break;
  case SC_STATUS_FLOAT:
    ss >> sc_vals->sc_float;
    if (ss.fail())
      sc_vals->sc_float_impossible = 1;
    break;
  case SC_STATUS_DOUBLE:
    ss >> sc_vals->sc_double;
    if (ss.fail())
      sc_vals->sc_double_impossible = 1;
    break;
  case SC_STATUS_MINUS_INFF:
    sc_vals->sc_float = -std::numeric_limits<float>::infinity();
    break;
  case SC_STATUS_PLUS_INFF:
    sc_vals->sc_float = std::numeric_limits<float>::infinity();
    break;
  case SC_STATUS_MINUS_INF:
    sc_vals->sc_double = -std::numeric_limits<double>::infinity();
    break;
  case SC_STATUS_PLUS_INF:
    sc_vals->sc_double = std::numeric_limits<double>::infinity();
    break;
  case SC_STATUS_NANF:
    sc_vals->sc_nanf = 1;
    break;
  case SC_STATUS_NAN:
    sc_vals->sc_nan = 1;
    break;
  }
}

void ConvertOthers(t_scalar_values *sc_vals, t_scalar_convert_status sc_stat,
                   std::string num) {

  if (sc_stat == SC_STATUS_MINUS_INFF || sc_stat == SC_STATUS_PLUS_INFF ||
      sc_stat == SC_STATUS_MINUS_INF || sc_stat == SC_STATUS_PLUS_INF ||
      sc_stat == SC_STATUS_NANF || sc_stat == SC_STATUS_NAN) {
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    switch (static_cast<int>(sc_stat)) {
    case SC_STATUS_MINUS_INFF:
      sc_vals->sc_double = -std::numeric_limits<double>::infinity();
      break;
    case SC_STATUS_PLUS_INFF:
      sc_vals->sc_double = std::numeric_limits<double>::infinity();
      break;
    case SC_STATUS_MINUS_INF:
      sc_vals->sc_float = -std::numeric_limits<float>::infinity();
      break;
    case SC_STATUS_PLUS_INF:
      sc_vals->sc_float = std::numeric_limits<float>::infinity();
      break;
    }
    return;
  }
  if (sc_stat != SC_STATUS_CHAR) {
    std::stringstream ss(num);
    int sc_char_num;
    ss >> sc_char_num;
    if (ss.fail())
      sc_vals->sc_char_impossible = 1;
    else if (!std::isprint(static_cast<char>(sc_char_num)))
      sc_vals->sc_char_non_print = 1;
    else
      sc_vals->sc_char = static_cast<char>(sc_char_num);
  }
  if (sc_stat != SC_STATUS_INT) {
    std::stringstream ss(num);
    ss >> sc_vals->sc_int;
    if (ss.fail())
      sc_vals->sc_int_impossible = 1;
  }
  if (sc_stat != SC_STATUS_FLOAT) {
    std::stringstream ss(num);
    ss >> sc_vals->sc_float;
    if (ss.fail())
      sc_vals->sc_float_impossible = 1;
  }
  if (sc_stat != SC_STATUS_DOUBLE) {
    std::stringstream ss(num);
    ss >> sc_vals->sc_double;
    if (ss.fail())
      sc_vals->sc_double_impossible = 1;
  }
}

void DisplayResults(t_scalar_convert_status sc_stat, t_scalar_values *sc_vals) {

  (void)sc_stat;
  if (sc_vals->sc_char_impossible)
    std::cout << "char: " << "impossible\n";
  else if (sc_vals->sc_char_non_print)
    std::cout << "char: " << "Not displayable\n";
  else
    std::cout << "char: " << sc_vals->sc_char << "\n";

  if (sc_vals->sc_int_impossible)
    std::cout << "int: " << "impossible\n";
  else
    std::cout << "int: " << sc_vals->sc_int << "\n";

  if (sc_vals->sc_float_impossible)
    std::cout << "float: " << "impossible\n";
  else
    std::cout << "float: " << sc_vals->sc_float << "f\n";

  if (sc_vals->sc_double_impossible)
    std::cout << "double: " << "impossible\n";
  else
    std::cout << "double: " << sc_vals->sc_double << "\n";

  //   if (sc_stat == SC_STATUS_MINUS_INF) {
  //     std::cout << "char: " << "impossible\n";
  //     std::cout << "int: " << "impossible\n";
  //     std::cout << "float: " << "-inff\n";
  //     std::cout << "double: " << "-inf" << std::endl;
  //   } else if (sc_stat == SC_STATUS_PLUS_INF) {
  //     std::cout << "char: " << "impossible\n";
  //     std::cout << "int: " << "impossible\n";
  //     std::cout << "float: " << "+inff\n";
  //     std::cout << "double: " << "+inf" << std::endl;
  //   } else if (sc_stat == SC_STATUS_NANF || sc_stat == SC_STATUS_NAN) {
  //     std::cout << "char: " << "impossible\n";
  //     std::cout << "int: " << "impossible\n";
  //     std::cout << "float: " << "nanf\n";
  //     std::cout << "double: " << "nan" << std::endl;
  //   } else {
  //     if (sc_vals->sc_char_impossible)
  //       std::cout << "char: " << "impossible" << "\n";
  //     else if (sc_vals->sc_char_non_print)
  //       std::cout << "char: " << "Non displayable" << "\n";
  //     else
  //       std::cout << "char: " << sc_vals->sc_char << "\n";
  //     if (sc_vals->sc_int_impossible)
  //       std::cout << "int: " << "impossible" << "\n";
  //     else
  //       std::cout << "int: " << sc_vals->sc_int << "\n";
  //     if (sc_vals->sc_float_impossible)
  //       std::cout << "float: " << "impossible" << "\n";
  //     else
  //       std::cout << "float: " << sc_vals->sc_float << "f\n";
  //     if (sc_vals->sc_double_impossible)
  //       std::cout << "double: " << "impossible" << "\n";
  //     else
  //       std::cout << "double: " << sc_vals->sc_double << std::endl;
}

void ScalarConverter::convert(std::string num) {
  t_scalar_convert_status sc_stat = DetectType(num);
  t_scalar_values *sc_vals = new (t_scalar_values);
  memset(sc_vals, 0, sizeof(t_scalar_values));
  try {
    ConvertActual(sc_vals, sc_stat, num);
    ConvertOthers(sc_vals, sc_stat, num);
    DisplayResults(sc_stat, sc_vals);
  } catch (...) {
    delete sc_vals;
    return;
  }
  delete sc_vals;
}
