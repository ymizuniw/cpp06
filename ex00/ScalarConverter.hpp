#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <string>

class ScalarConverter {
public:
  static void convert(std::string num);
};

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

#endif
