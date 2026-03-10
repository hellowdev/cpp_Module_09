CXX = c++

NAME = PmergeMe

CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address -std=c++98

SRC = main.cpp  PmergeMe.cpp

OBJ = ${SRC:.cpp=.o}

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	
%.o : %.cpp PmergeMe.hpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all