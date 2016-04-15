# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/28 13:53:34 by jdhaisne          #+#    #+#              #
#    Updated: 2016/04/15 13:59:50 by jdhaisne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = main.c \
	  env.c \
	  setenv.c \
	  unsetenv.c \
	  ft_cd.c \
	  ft_cd3.c \
	  ft_cd2.c \
	  ft_cd_check.c \
	  exit.c \
	  read.c \
	  gnl/get_next_line.c

OBJ = main.o \
	  env.o \
	  setenv.o \
	  unsetenv.o \
	  ft_cd_check.o \
	  ft_cd3.o \
	  ft_cd.o \
	  ft_cd2.o \
	  exit.o \
	  read.o \
	  get_next_line.o

LIB = libft.a

CFLAG = -Wall -Werror -Wextra

LIBFT_DIR = libft

all : $(NAME)

$(NAME) :
	make -C $(LIBFT_DIR) re
	gcc -c $(SRC) $(CFLAG)
	gcc -o $(NAME) $(OBJ) $(LIBFT_DIR)/$(LIB)

.PHONY:clean
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
