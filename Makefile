# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elebouch <elebouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 15:25:29 by elebouch          #+#    #+#              #
#    Updated: 2018/05/06 09:22:51 by elebouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRC_DIR = ./src/
OBJ_DIR = ./obj/
CC = gcc
CFLAGS = -Wall -Werror -Wextra $(INCLUDE) -g
CPPFLAGS = -I./inc -I./libft/inc
LDFLAGS = -L libft/
LDLIBS = -lft
LIB = libft/libft.a
MAKE = make
RM = rm -f

HEADER = \
		inc/minishell.h \

SRC= \
	execute.c \
	free.c \
	launch.c \
	main.c \
	parser.c \
	bltin_cd.c \
	bltin_echo.c \
	bltin_env.c \
	bltin_setenv.c \
	bltin_unsetenv.c \
	bltin_exit.c \
	env.c \
	getpath.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: 
	@$(MAKE) libs 
	@$(MAKE) $(NAME)

$(NAME): $(LIB) $(OBJ)
	@echo "\n\033[94mCompiling minishell\033[0m"
	@$(CC) $(CFLAGS) $(CPPFLAGS)  $(OBJ)  -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@echo  "\033[34mDone\033[0m"

$(LIB):;

libs:
	@$(MAKE) -C libft/

obj/%.o: src/%.c $(HEADER)
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ -c $<

clean:
	@$(MAKE) clean -C libft/
	@$(RM) $(OBJ)
	@rmdir  $(OBJ_DIR) 2> /dev/null || true

fclean: clean
	@$(MAKE) fclean -C libft/
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: clean fclean re all libs
