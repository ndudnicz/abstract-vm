NAME = avm
CC = g++
CFLAGS = -Werror -Wextra -Wall
DEBUGFLAGS = # -fsanitize=address -g3

# SOURCE FOLDERS ==============================================================#

SRC_DIR = src

# OBJECTS FOLDERS =============================================================#

OBJ_DIR = obj

# INCLUDES FOLDERS ============================================================#

PATH_INCLUDES = includes

# SOURCES LIST ================================================================#

SRC = main.cpp \
Operand.class.cpp \
Cpu.class.cpp \
OperandFactory.class.cpp \

# OBJECTS LIST ================================================================#

OBJ = $(SRC:%.cpp=obj/%.o)
DEP = $(SRC:%.cpp=obj/%.d)

# GENERIC RULES ===============================================================#

all: $(NAME)

clean:
		$(RM) $(OBJ) $(DEP)

fclean: clean
		$(RM) $(NAME)

re: clean fclean all

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -MMD -o $@ -c $< -I $(PATH_INCLUDES)

-include $(OBJ:.o=.d)
