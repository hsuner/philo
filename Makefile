NAME	= philo
NAME_2	= philo.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar rc
SOURCES	=	./main.c			\
			./arg_check.c		\
			./destroy.c			\
			./general_conf.c	\
			./philo_actions.c	\
			./philo_life.c		\
			./utils_libft.c		\
			./utils.c

OBJ = $(SOURCES:.c=.o)

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \033[34;1m
RESET = \x1b[0m

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@$(AR) $(NAME_2) $(OBJ)
	@$(CC) $(CFLAGS) $(NAME_2) -o $(NAME)
	@printf "$(GREEN) Executable named philo created$(RESET)\n"

clean:
	@$(RM) $(OBJ)
	@printf "$(BLUE) deleting object files$(RESET)\n"

fclean: clean
	@$(RM) $(NAME_2)
	@$(RM) $(NAME)
	@printf "$(RED) deleting executable philo$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
