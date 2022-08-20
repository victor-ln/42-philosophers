NAME	=	philo_bonus

CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra -O3 -g3
LINKS	=	-pthread -I ./inc

RM		=	rm -rf

FILES	=	init_data_bonus.c \
			main_bonus.c \
			threads_bonus.c \
			utils_bonus.c \

SRC		=	$(addprefix src/, $(FILES))
OBJ		=	$(addprefix obj/, $(FILES:.c=.o))

all:		$(NAME)

obj/%_bonus.o:	src/%_bonus.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(LINKS) -c $< -o $@

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(LINKS) $(OBJ) -o $@

clean:
	@$(RM) obj

fclean:		clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
