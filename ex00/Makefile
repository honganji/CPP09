NAME := easyfind

INCLUDE_DIR := include
SRC_DIR := src
OBJ_DIR := objs

SOURCE := main.cpp

HEADER := $(addprefix $(INCLUDE_DIR)/, easyfind.hpp)


OBJS := $(SOURCE:%.cpp=$(OBJ_DIR)/%.o)

CC := c++
CC_FLAG := -Wall -Wextra -Werror -std=c++98 

all: $(NAME)

$(NAME): $(SOURCE) $(OBJ_DIR) $(OBJS) $(HEADER)
	$(CC) $(CC_FLAG) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CC_FLAG) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	mkdir $(OBJ_DIR)/$(SRC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug_val: CC_FLAG += -g
debug_val: re
	./$(NAME)

.PHONY: all clean fclean re debug
