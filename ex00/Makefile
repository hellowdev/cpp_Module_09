CXX = c++

NAME = btc

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp  BitcoinExchange.cpp

OBJ = ${SRC:.cpp=.o}

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	
%.o : %.cpp BitcoinExchange.hpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all