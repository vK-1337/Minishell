SRCS =			cd/cd.c \
        		ast/create_tree.c \
				ast/build_tree.c \
				ast/ast.c \
				ast/launch_ast.c \
				ast/ast_utils.c \
				ast/ast_utils2.c \
				ast/ast_utils3.c \
				ast/parenthesis.c \
				cd/cd_utils.c \
				echo/echo.c \
				env/env.c \
				env/export.c \
				env/export_utils.c \
				env/export_utils_two.c \
				env/unset.c \
				exec_command/exec_command.c \
				exec_command/exec_redirections.c \
				exec_command/exec_redirections2.c \
				exec_command/exec_utils.c \
				exit/exit.c \
				expand/expand.c \
				expand/expand_utils.c \
				expand/expand_utils_two.c \
				expand/expand_utils_three.c \
				expand/wildcard.c \
				expand/wildcard_utils.c \
				expand/wildcard_utils_two.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				lexer/lexer.c \
				lexer/lexer_utils.c \
				lexer/lexer_utils_two.c \
				lexer/lexer_utils_three.c \
				lexer/quotes.c \
				lexer/syntax.c \
				lexer/syntax_utils.c \
				lexer/handle_redirections.c \
				lexer/handle_redirections_utils.c \
				lexer/split_redirections.c \
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
				tokens/helpers.c \
				tokens/lst_utils.c \
				tokens/token_utils.c \
				tokens/token_utils_two.c \


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