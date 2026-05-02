#include "ScalarConverter.hpp"
#include <cctype>
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

// this shoul return the specific types
t_scalar_convert_status validate_num(std::string num) {
  // int part
  size_t i = 0;

  if (num.at(i) == '-' || num.at(i) == '+')
    i++;
  while (i < num.length()) {
    if (!std::isdigit(static_cast<unsigned char>(num.at(i))))
      break;
    i++;
  }
  if (i == num.length())
    return (SC_STATUS_INT);
  if (num.at(i) == '.') {
    i++;
    if (i == num.length())
      return (SC_STATUS_DOUBLE);
    else if (num.at(i) != 'f' &&
             !std::isdigit(static_cast<unsigned char>(num.at(i))))
      return (SC_STATUS_ERROR);
  }
  if (num.at(i) == 'f') {
    i++;
    if (i == num.length())
      return (SC_STATUS_FLOAT);
    else
      return (SC_STATUS_ERROR);
  }
  // fractional part
  while (i < num.length()) {
    if (!std::isdigit(static_cast<unsigned char>(num.at(i))))
      break;
    i++;
  }
  if (i == num.length())
    return (SC_STATUS_DOUBLE);
  if (num.at(i) == 'f') {
    i++;
    if (i == num.length())
      return (SC_STATUS_FLOAT);
    else
      return (SC_STATUS_ERROR);
  }
  return (SC_STATUS_ERROR);
}

int validate_char(std::string num) {
  if (num.length() == 1 && !std::isdigit(static_cast<unsigned char>(num.at(0))))
    return (1);
  return (0);
}

t_scalar_convert_status DetectType(std::string num) {

  t_scalar_convert_status num_type = SC_STATUS_ERROR;

  if (num.empty())
    return (num_type);
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
    num_type = SC_STATUS_NAN;
  else if (validate_char(num))
    num_type = SC_STATUS_CHAR;
  else
    num_type = validate_num(num);
  return (num_type);
}

void ConvertDecimalToInt(t_scalar_values *sc_vals, const std::string &num) {
  std::stringstream ss(num);
  ss >> sc_vals->sc_int;
  if (ss.fail())
    sc_vals->sc_int_impossible = 1;
}

void ConvertDecimalToFloat(t_scalar_values *sc_vals, std::string &num) {
  if (num[num.size() - 1] == 'f')
    num = num.substr(0, num.size() - 1);
  std::stringstream ss(num);
  ss >> sc_vals->sc_float;
  if (ss.fail())
    sc_vals->sc_float_impossible = 1;
}

void ConvertDecimalToDouble(t_scalar_values *sc_vals, const std::string &num) {
  std::stringstream ss(num);
  ss >> sc_vals->sc_double;
  if (ss.fail())
    sc_vals->sc_double_impossible = 1;
}

void ConvertActual(t_scalar_values *sc_vals, t_scalar_convert_status sc_stat,
                   std::string &num) {

  switch (static_cast<int>(sc_stat)) {
  case SC_STATUS_ERROR:
    return;
  case SC_STATUS_CHAR: {
    if (!std::isprint(static_cast<unsigned char>(num.at(0))))
      sc_vals->sc_char_non_print = 1;
    else
      sc_vals->sc_char = num.at(0);
    return;
  }
  case SC_STATUS_INT:
    ConvertDecimalToInt(sc_vals, num);
    return;
  case SC_STATUS_FLOAT:
    ConvertDecimalToFloat(sc_vals, num);
    return;
  case SC_STATUS_DOUBLE:
    ConvertDecimalToDouble(sc_vals, num);
    return;
  case SC_STATUS_MINUS_INFF:
    sc_vals->sc_float = -std::numeric_limits<float>::infinity();
    return;
  case SC_STATUS_PLUS_INFF:
    sc_vals->sc_float = std::numeric_limits<float>::infinity();
    return;
  case SC_STATUS_MINUS_INF:
    sc_vals->sc_double = -std::numeric_limits<double>::infinity();
    return;
  case SC_STATUS_PLUS_INF:
    sc_vals->sc_double = std::numeric_limits<double>::infinity();
    return;
  case SC_STATUS_NANF:
    sc_vals->sc_nanf = 1;
    return;
  case SC_STATUS_NAN:
    sc_vals->sc_nan = 1;
    return;
  }
}

void ConvertSpecialStatus(t_scalar_values *sc_vals,
                          t_scalar_convert_status sc_stat) {
  switch (static_cast<int>(sc_stat)) {
  case SC_STATUS_ERROR:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_float_impossible = 1;
    sc_vals->sc_double_impossible = 1;
    return;
  case SC_STATUS_MINUS_INFF:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_double = -std::numeric_limits<double>::infinity();
    return;
  case SC_STATUS_PLUS_INFF:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_double = std::numeric_limits<double>::infinity();
    return;
  case SC_STATUS_MINUS_INF:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_float = -std::numeric_limits<float>::infinity();
    return;
  case SC_STATUS_PLUS_INF:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_float = std::numeric_limits<float>::infinity();
    return;
  case SC_STATUS_NANF:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_nan = 1;
    return;
  case SC_STATUS_NAN:
    sc_vals->sc_char_impossible = 1;
    sc_vals->sc_int_impossible = 1;
    sc_vals->sc_nanf = 1;
    return;
  }
}

void ConvertIntToChar(t_scalar_values *sc_vals) {
  if (!(0 <= sc_vals->sc_int && sc_vals->sc_int <= 127))
    sc_vals->sc_char_impossible = 1;
  else if (std::isprint(static_cast<unsigned char>(sc_vals->sc_int)))
    sc_vals->sc_char = static_cast<char>(sc_vals->sc_int);
  else
    sc_vals->sc_char_non_print = 1;
}

void ConvertFloatToChar(t_scalar_values *sc_vals) {
  if (!(0.0f <= sc_vals->sc_float && sc_vals->sc_float < 128.0f)) {
    sc_vals->sc_char_impossible = 1;
    return;
  }
  int tmp = static_cast<int>(sc_vals->sc_float);
  if (std::isprint(static_cast<unsigned char>(tmp)))
    sc_vals->sc_char = static_cast<char>(tmp);
  else
    sc_vals->sc_char_non_print = 1;
}

void ConvertDoubleToChar(t_scalar_values *sc_vals) {
  if (!(0.0 <= sc_vals->sc_double && sc_vals->sc_double < 128.0)) {
    sc_vals->sc_char_impossible = 1;
    return;
  }
  int tmp = static_cast<int>(sc_vals->sc_double);
  if (std::isprint(static_cast<unsigned char>(tmp)))
    sc_vals->sc_char = static_cast<char>(tmp);
  else
    sc_vals->sc_char_non_print = 1;
}

void ConvertCharToOthers(t_scalar_values *sc_vals, const std::string &num) {
  sc_vals->sc_int = static_cast<int>(num.at(0));
  sc_vals->sc_float = static_cast<float>(num.at(0));
  sc_vals->sc_double = static_cast<double>(num.at(0));
}

void ConvertRegularStatus(t_scalar_values *sc_vals,
                          t_scalar_convert_status sc_stat,
                          const std::string &num) {
  switch (static_cast<int>(sc_stat)) {
  case SC_STATUS_CHAR: // convert to except char type
    ConvertCharToOthers(sc_vals, num);
    return;
  case SC_STATUS_INT:
    ConvertIntToChar(sc_vals);
    ConvertDecimalToFloat(sc_vals, const_cast<std::string &>(num));
    ConvertDecimalToDouble(sc_vals, num);
    return;
  case SC_STATUS_FLOAT:
    ConvertFloatToChar(sc_vals);
    ConvertDecimalToInt(sc_vals, num);
    ConvertDecimalToDouble(sc_vals, num);
    return;
  case SC_STATUS_DOUBLE:
    ConvertDoubleToChar(sc_vals);
    ConvertDecimalToInt(sc_vals, num);
    ConvertDecimalToFloat(sc_vals, const_cast<std::string &>(num));
    return;
  }
}

int IsSpecialStatus(t_scalar_convert_status sc_stat) {
  switch (static_cast<int>(sc_stat)) {
  case SC_STATUS_ERROR:
  case SC_STATUS_MINUS_INFF:
  case SC_STATUS_PLUS_INFF:
  case SC_STATUS_MINUS_INF:
  case SC_STATUS_PLUS_INF:
  case SC_STATUS_NANF:
  case SC_STATUS_NAN:
    return (1);
  }
  return (0);
}

void ConvertOthers(t_scalar_values *sc_vals, t_scalar_convert_status sc_stat,
                   std::string &num) {
  if (IsSpecialStatus(sc_stat))
    ConvertSpecialStatus(sc_vals, sc_stat);
  ConvertRegularStatus(sc_vals, sc_stat, num);
}

void DisplayResults(t_scalar_values *sc_vals) {
  // display char:
  if (sc_vals->sc_char_impossible)
    std::cout << "char: " << "impossible\n";
  else if (sc_vals->sc_char_non_print)
    std::cout << "char: " << "Not displayable\n";
  else
    std::cout << "char: " << sc_vals->sc_char << "\n";
  // display int:
  if (sc_vals->sc_int_impossible)
    std::cout << "int: " << "impossible\n";
  else
    std::cout << "int: " << sc_vals->sc_int << "\n";
  // display float:
  if (sc_vals->sc_float_impossible)
    std::cout << "float: " << "impossible\n";
  else if (sc_vals->sc_nanf)
    std::cout << "float: " << "nanf\n";
  else
    std::cout << "float: " << sc_vals->sc_float << "f\n";
  // display double:
  if (sc_vals->sc_double_impossible)
    std::cout << "double: " << "impossible\n";
  else if (sc_vals->sc_nan)
    std::cout << "double: " << "nan\n";
  else
    std::cout << "double: " << sc_vals->sc_double << "\n";
}

void ScalarConverter::convert(std::string num) {
  t_scalar_convert_status sc_stat = DetectType(num);
  t_scalar_values sc_vals = {};
  ConvertActual(&sc_vals, sc_stat, num);
  /*
    sc_vals.sc_double_impossible=1 means num (type is double) cannot be double
    num, then it cannot be converted to other types (impossible).
  */
  if (sc_vals.sc_double_impossible)
    sc_stat = SC_STATUS_ERROR;
  ConvertOthers(&sc_vals, sc_stat, num);
  DisplayResults(&sc_vals);
}
