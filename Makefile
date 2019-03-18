
FLAGS := -Werror #-Wextra -Wall
NAME := corewar

INC_DIR := -I ./incs/
INC_DIR_LIB := -I ./libft/

SRC_DIR := ./srcs/
OBJ_DIR := ./objs/

LIB_M := ./libft/Makefile

SRC := error.c init.c read_bytecode.c read_file.c main.c buttle.c print.c free.c \
		ops.c oops.c ooops.c aff.c ops_fun.c visual.c

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc  -o $(NAME) $(OBJ) -l ncurses -L. -lft

lib:
	make -f $(LIB_M)

$(OBJ_DIR)%.o: %.c
	gcc -c $(FLAGS)  $< -o $@  $(INC_DIR) $(INC_DIR_LIB)

clean:
	@rm -f $(OBJ)
	make -f $(LIB_M) clean
fclean: clean
	@rm -f $(NAME)
	make -f $(LIB_M) fclean
clean_all: clean
	@rm -f *~
re: fclean all

vpath %.c $(SRC_DIR)
