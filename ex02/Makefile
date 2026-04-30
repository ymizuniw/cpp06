NAME = identify
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98 -pedantic-errors

SRCS = Base.cpp ABC.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
INC = -I.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

.PHONEY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS) $(NAME)

re: fclean all