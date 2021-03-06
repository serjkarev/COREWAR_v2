# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/19 18:54:02 by kmerkulo          #+#    #+#              #
#    Updated: 2019/03/19 18:54:04 by kmerkulo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		corewar

CC = 			clang
CFLAGS = 		-Werror -Wextra -Wall
LIB_DIR =		libft/
LIBC =			libft.a

INC_DIR := 		inc/
INC_DIR_LIB := 	-I ./libft/

SRC_DIR = 		src/
OBJ_DIR = 		obj/

SRC = 			error.c init.c read_bytecode.c read_file.c main.c battle.c print.c free.c \
				ops.c oops.c ooops.c aff.c ops_fun.c vizo_init.c vizo_tools.c vizo_print_1.c vizo_print_2.c

OBJ = 			$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

.PHONY: 		all

all: 			$(NAME)
	@:

$(LIBC):
	@$(MAKE) -C libft

$(NAME): 		$(LIBC) $(OBJ)
	@$(CC)  -o $(NAME) $(OBJ) -l ncurses -L$(LIB_DIR) -lft
	@echo "\033[34mCorewar compiled!\033[0m"

$(OBJ):			| $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c $(INC_DIR)*.h
	@echo "\033[33mCompiling $<...\033[0m"
	@$(CC) -c $(CFLAGS) $< -o $@ -I $(INC_DIR) $(INC_DIR_LIB)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C libft
	@echo "\033[32mCleaned!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft

clean_all: clean
	@rm -f *~

re: fclean all

vpath %.c $(SRC_DIR)
