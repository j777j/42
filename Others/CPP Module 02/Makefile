NAME_EX00 = ex00
NAME_EX01 = ex01
NAME_EX02 = ex02
NAME_EX03 = ex03

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_EX00 = ex00/main.cpp ex00/Fixed.cpp
SRCS_EX01 = ex01/main.cpp ex01/Fixed.cpp
SRCS_EX02 = ex02/main.cpp ex02/Fixed.cpp
SRCS_EX03 = ex03/main.cpp ex03/Fixed.cpp ex03/Point.cpp ex03/bsp.cpp

OBJS_EX00 = $(SRCS_EX00:.cpp=.o)
OBJS_EX01 = $(SRCS_EX01:.cpp=.o)
OBJS_EX02 = $(SRCS_EX02:.cpp=.o)
OBJS_EX03 = $(SRCS_EX03:.cpp=.o)

all: $(NAME_EX00) $(NAME_EX01) $(NAME_EX02) $(NAME_EX03)

$(NAME_EX00): $(OBJS_EX00)
	$(CXX) $(CXXFLAGS) -o $(NAME_EX00) $(OBJS_EX00)

$(NAME_EX01): $(OBJS_EX01)
	$(CXX) $(CXXFLAGS) -o $(NAME_EX01) $(OBJS_EX01)

$(NAME_EX02): $(OBJS_EX02)
	$(CXX) $(CXXFLAGS) -o $(NAME_EX02) $(OBJS_EX02)

$(NAME_EX03): $(OBJS_EX03)
	$(CXX) $(CXXFLAGS) -o $(NAME_EX03) $(OBJS_EX03)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_EX00) $(OBJS_EX01) $(OBJS_EX02) $(OBJS_EX03)

fclean: clean
	rm -f $(NAME_EX00) $(NAME_EX01) $(NAME_EX02) $(NAME_EX03)

re: fclean all

.PHONY: all clean fclean re
