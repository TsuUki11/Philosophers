# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 19:42:03 by aaitoual          #+#    #+#              #
#    Updated: 2022/03/21 19:42:07 by aaitoual         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
NAME_BONUS = philosophers_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
OBJ = ./mandatory/obj

FILE =  ./mandatory/philo.c ./mandatory/philo_utils_1.c ./mandatory/philo_utils_2.c ./mandatory/philo_utils_3.c ./mandatory/philo_utils_4.c \

FILE_BONUS =  ./bonus/philo_bonus.c ./bonus/philo_bonus_utils_1.c ./bonus/philo_bonus_utils_2.c \

FILE1 = $(FILE:.c=.o)

FILE1_BONUS = $(FILE_BONUS:.c=.o)

LIB = ./mandatory/philosophers_lib.h \

LIB_BONUS = ./bonus/philosophers_bonus_lib.h \

all: $(NAME)

$(NAME): $(FILE1) $(LIB)
	@$(CC) $(FILE1) -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(FILE1_BONUS) $(LIB_BONUS) $(NAME)
	@$(CC) $(FILE1_BONUS) -o $@

%.o : %.c
	@$(CC) -o $@  -c $^

clean:
	@rm -f $(FILE1) $(FILE1_BONUS)

fclean: clean
	@rm -f $(NAME)
re: fclean all
