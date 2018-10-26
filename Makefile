NAME = avm
CC = g++
CFLAGS =# -Werror -Wextra -Wall
DEBUGFLAGS =# -fsanitize=address -g3
LFLAGS =# -lasan

# SOURCE FOLDERS ==============================================================#

SRC_DIR = src

# OBJECTS FOLDERS =============================================================#

OBJ_DIR = obj

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = includes

# SOURCES LIST ================================================================#

SRC = main.cpp \
Operand.cpp \

# OBJECTS LIST ================================================================#

OBJ = $(SRC:%.cpp=obj/%.o)

# GENERIC RULES ===============================================================#

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: clean fclean all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(LFLAGS) -o $@ -c $< -I $(PATH_INCLUDES)
