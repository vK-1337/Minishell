/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:31 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/17 13:03:16 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_convert_tokens(char **tokens)
{
	t_norme	vars;
	t_ttype	type;
	t_ttype	previous_type;
	t_token	*tokens_list;

	tokens_list = NULL;
	vars.j = ft_check_first_redir(tokens, &type);
	vars.str = NULL;
	vars.i = 0;
	while (tokens[vars.i])
	{
		if (vars.i == 0)
			type = ft_define_first_token_type(tokens, vars.j, type);
		else
			type = ft_define_subsequent_token_type(tokens, vars.i, vars.j,
					previous_type);
		ft_tokenlstadd_back(&tokens_list, ft_tokenlstnew(tokens[vars.i], type));
		vars.str = tokens[vars.i];
		previous_type = type;
		vars.i++;
	}
	// ft_print_token_list(&tokens_list);
	return (tokens_list);
}

int	ft_token_empty(char *token)
{
	if (token[0] == 0)
		return (1);
	else if (token[0] == 39 && token[1] == 39)
		return (1);
	else if (token[0] == 34 && token[1] == 34)
		return (1);
	else if (ft_only_spaces_between(token) == 1 && (token[0] == 34
			|| token[0] == 39))
		return (1);
	return (0);
}

int	ft_only_spaces_between(char *token)
{
	int	i;
	int	delimiter;

	i = 0;
	delimiter = token[0];
	while (token[++i] != delimiter)
	{
		if (token[i] != ' ')
			return (0);
	}
	return (1);
}

int	ft_check_first_redir(char **tokens, t_ttype *type)
{
	if (tokens[0] && (tokens[0][0] == '<' || tokens[0][0] == '>'))
	{
		*type = OPERATOR;
		return (1);
	}
	return (0);
}

t_ttype	ft_define_first_token_type(char **tokens, int first_type_redir,
		t_ttype type)
{
	if (first_type_redir)
		return (type);
	else if (tokens[0] && tokens[0][0] == '(')
		return (PARENTHESIS);
	else if (tokens[0] && tokens[0][0] && !ft_is_operator(tokens[0][0]))
		return (COMMAND);
	return (type);
}

t_ttype	ft_define_subsequent_token_type(char **tokens, int i,
		int first_type_redir, t_ttype previous_type)
{
	if (first_type_redir == 1 && !ft_is_operator(tokens[i][0])
		&& previous_type != OPERATOR)
		return (COMMAND);
	return (ft_define_ttype(tokens[i], tokens[i - 1]));
}

t_ttype	ft_define_ttype(char *token, char *previous_token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!token)
		return (0);
	if (token[i] == 40)
		return (PARENTHESIS);
	if (ft_is_operator(token[i]))
		return (OPERATOR);
	if (token[i] == 34 || token[i] == 39)
		i++;
	if (ft_is_option(token))
		return (OPTION);
	if (previous_token)
	{
		if (previous_token[j] == 34 || previous_token[j] == 39)
			j++;
		if (previous_token[j] == '>' || previous_token[j] == '<')
			return (PATH_FILE);
		if (previous_token[j] == 38 || previous_token[j] == 124)
			return (COMMAND);
	}
	return (COMMAND);
}
