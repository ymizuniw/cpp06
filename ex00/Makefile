NAME=convert
CXX=c++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -pedantic-errors

SRCS=ScalarConverter.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
INC=-I.

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

.PHONEY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS) $(NAME)

re:
	fclean
	all