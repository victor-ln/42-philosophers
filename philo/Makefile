NAME	=	philo

CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra -O3 -g3 -fsanitize=address
LINKS	=	-pthread -I ./inc

RM		=	rm -rf

FILES	=	init_data.c \
			main.c \
			utils.c \

SRC		=	$(addprefix src/, $(FILES))
OBJ		=	$(addprefix obj/, $(FILES:.c=.o))

all:		$(NAME)

obj/%.o:	src/%.c
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
