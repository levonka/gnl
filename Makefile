# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/08 15:24:16 by agottlie          #+#    #+#              #
#    Updated: 2018/12/14 09:56:48 by agottlie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

FLAGS = -Wall -Wextra -Werror

SRC = libft/ft_*.c

OBJ = ft_*.o

INC = libft/libft.h

all: $(NAME)

$(NAME): fclean
	@gcc $(FLAGS) -c $(SRC) -I $(INC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@gcc $(FLAGS) -L. $(NAME) get_next_line.c
	@/bin/rm -f $(OBJ)

m: all
	./a.out Makefile

s: all
	./a.out sample.txt

s2: all
	./a.out sample2.txt

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out

re: fclean all

