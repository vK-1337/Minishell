/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:56:17 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 08:19:07 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_token_list(t_token **tokens)
{
	t_token	*curr;
	int		i;

	curr = *tokens;
	i = 1;
	while (curr)
	{
		printf("\nNoeud numero |%d|\n", i++);
		printf("Token => |%s|\n", curr->token);
		printf("Type => |%s|\n", ft_print_type(curr->type));
		if (curr->file_redir)
			printf("File redir => |%s|\n", curr->file_redir);
		if (curr->file_redir_out)
			printf("File redir out => |%s|\n", curr->file_redir_out->token);
        if (curr->file_redir_in)
            printf("File redir in => |%s|\n", curr->file_redir_in->token);
		curr = curr->next;
	}
}

char	*ft_print_type(t_ttype type)
{
	if (type == COMMAND)
		return ("Command");
	if (type == OPTION)
		return ("Option");
	if (type == CMD_ARG)
		return ("command arg");
	if (type == OPERATOR)
		return ("Operator");
	if (type == PATH_FILE)
		return ("Path file");
	if (type == PARENTHESIS)
		return ("Parenthesis");
	return ("1337");
}

int	ft_is_operator(char c)
{
	if (c == 38 || c == 60 || c == 62 || c == 124)
		return (1);
	return (0);
}

int	ft_is_file(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_option(char *token)
{
	int	i;

	i = 0;
	if (token[0] != '-')
		return (0);
	else
		i++;
	while (token[i])
	{
		if (!ft_isalnum(token[i]))
			return (0);
		i++;
	}
	return (1);
}
