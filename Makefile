SRCS =			env/env.c \
				prompt/prompt.c \
				lexer/quotes.c \
				main/minishell.c \
				env/export.c \
				env/unset.c \
				lst_utils.c \
				expand/expand.c \
				expand/expand_utils.c \
				cd/cd.c \
				cd/cd_utils.c \
				pwd/pwd.c \
				exec_command.c \
				tokens/token_split.c \
				tokens/ft_tokenlstadd_front.c \
				tokens/ft_tokenlstclear.c \
				tokens/ft_tokenlstdelone.c \
				tokens/ft_tokenlstiter.c \
				tokens/ft_tokenlstlast.c \
				tokens/ft_tokenlstmap.c \
				tokens/ft_tokenlstnew.c \
				tokens/ft_tokenlstsize.c \
				tokens/ft_tokenlstadd_back.c \
				tokens/token_utils.c \
				lexer/lexer.c \
				lexer/lexer_utils.c \

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