SRCS =			cd/cd.c \
        		ast/create_ast_list.c \
				ast/launch_ast.c \
				ast/ast_utils.c \
				cd/cd_utils.c \
				env/env.c \
				env/export.c \
				env/unset.c \
				exec_command.c \
				expand/expand.c \
				expand/expand_utils.c \
				expand/wildcard.c \
				expand/wildcard_utils.c \
				lexer/lexer.c \
				lexer/lexer_utils.c \
				lexer/quotes.c \
				lexer/syntax.c \
				lexer/handle_redirections.c \
				lst_utils.c \
				main/minishell.c \
				prompt/prompt.c \
				pwd/pwd.c \
				signals/signals.c \
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

CFLAGS = -Wall -Werror -Wextra -g3

LDFLAGS = -L./libft -lft -lreadline

LIBFT = ./libft/libft.a

NAME = minishell

OBJS = $(SRCS:.c=.o) ./libft/libft.a

# COLORS

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

all: $(NAME) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

re: fclean
	make all

.PHONY: all clean fclean re