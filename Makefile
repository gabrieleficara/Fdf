# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gficara <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:25:41 by gficara           #+#    #+#              #
#    Updated: 2018/06/28 13:06:06 by gficara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIB = fdf.a

LIB2 = libftprintf/libftprintf.a

LIB3 = minilibx

FRAME = -lmlx -L $(LIB3) -framework OpenGL -framework AppKit

FLAGS = -Wall -Wextra -Werror -g

CC = gcc

INC = -I includes -I libftprintf/includes/ -I $(LIB3)


SRC = sources/fdf.c \
	  sources/parsing.c \
	  sources/parsing_b.c \
	  sources/d_line.c \
	  sources/p_map.c \
	  sources/key.c \
	  sources/img.c

OBJ = $(SRC:.c=.o)

.PHONY: clean all fclean re

all : $(NAME)

$(NAME) : $(OBJ) Makefile
	@make -C libftprintf
	@make -C $(LIB3) 
	@ar rc $(LIB) $(OBJ)
	@ranlib $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(LIB) $(LIB2) $(LIB3)/libmlx.a $(FRAME)
	@echo "Creating $(NAME)"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean :
	@make clean -C libftprintf
	@make clean -C $(LIB3) 
	@rm -rf $(OBJ)
	@echo "Removing $(NAME) objects"

fclean : clean
	@make fclean -C libftprintf
	@rm -rf $(NAME) $(LIB)
	@echo "Removing $(LIB) and $(NAME)"

re: fclean all
