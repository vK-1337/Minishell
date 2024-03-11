/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:54:26 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 15:02:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_previous(char **previous_token, t_ttype *previous_type,
		char *current_token, t_ttype current_type)
{
	*previous_token = current_token;
	*previous_type = current_type;
}

t_token	*initialize_tokens_list(int *i, int *first_type_redir,
		char **previous_token)
{
	t_token	*tokens_list;

	*i = 0;
	*first_type_redir = 0;
	*previous_token = NULL;
	tokens_list = NULL;
	return (tokens_list);
}

t_ttype	determine_token_type(char **tokens, int i, int first_type_redir,
		t_ttype previous_type, char *previous_token)
{
	t_ttype	type;

	if (i == 0)
		type = define_first_token_type(tokens[i]);
	else if (first_type_redir == 1 && !ft_is_operator(tokens[i][0])
		&& previous_type != OPERATOR)
		type = COMMAND;
	else
		type = ft_define_ttype(tokens[i], previous_token);
	return (type);
}

t_ttype	define_first_token_type(char *token)
{
	if (token && (token[0] == '<' || token[0] == '>'))
		return (OPERATOR);
	else if (token && token[0] == '(')
		return (PARENTHESIS);
	else if (token && token[0] && !ft_is_operator(token[0]))
		return (COMMAND);
	else
		return (COMMAND);
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
