/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:13:22 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 22:58:49 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_handle_next_token(t_token **tokens, t_token *curr, t_token *next)
{
	if (next->next && next->next->type == COMMAND && curr->type == COMMAND
		&& strncmp(curr->token, "export", 6) == 0)
		return (ft_handle_command_export(tokens, curr));
	else if (curr->type == OPTION && next->type == OPTION)
		return (ft_handle_option(tokens, curr, next));
	else if (curr->type == OPERATOR && next->type == PATH_FILE)
		return (ft_handle_operator_path_file(tokens, curr, next));
	else
		return (curr->next);
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
