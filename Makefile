SRCS =	env.c \
				prompt.c \
				parser.c \
				minishell.c \
				env_utils.c \
				lst_utils.c \
				expand.c \

OBJS = $(SRCS:.c=.o) ./libft/libft.a

NAME = minishell

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -L./libft -lft -lreadline

# colors
GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "	 			+---------------------+\n \
					|  $(YELLOW)  MINISHELL $(GREEN)[OK]$(NC)   |\n \
					+---------------------+"

$(LIBFT):
	make -C ./libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean
	make all

.PHONY: all clean fclean re