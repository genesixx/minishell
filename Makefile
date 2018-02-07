# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elebouch <elebouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 15:25:29 by elebouch          #+#    #+#              #
#    Updated: 2018/02/07 16:34:22 by elebouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRC_DIR = ./src/
OBJ_DIR = ./obj/
CC = gcc
CFLAGS = -Wall -Werror -Wextra $(INCLUDE)
CPPFLAGS = -I./inc -I./libft/includes
LDFLAGS = -Llibft/
LDLIBS = -lftprintf
MAKE = make
RM = rm -f

HEADER = \
		inc/minishell.h \

SRC= \
	 main.c \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: lib $(NAME)

$(NAME):  $(OBJ)
	@echo "\033[94mCompiling ft_ls\033[0m"
	@$(CC) $(CFLAGS) $(CPPFLAGS)  $(OBJ)  -o $(NAME) $(LDFLAGS) $(LDLIBS)
	@echo  "\033[34mDone\033[0m"

lib:
	@echo "\033[94mCompiling libft and printf\033[0m"
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

.PHONY: clean fclean re all lib

