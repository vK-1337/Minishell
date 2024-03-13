/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:34:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/13 11:05:17 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lexer(char *input, t_list **env)
{
	char	**tokens;
	t_token	*listed_tokens;
	int		status;

	(void)env;
	listed_tokens = NULL;
	tokens = ft_token_split(input);
	if (!tokens)
		return (NULL);
	listed_tokens = ft_convert_tokens(tokens);
	free(tokens);
	if (!listed_tokens)
		return (NULL);
	// ft_print_token_list(&listed_tokens);
	ft_reunite_tokens(&listed_tokens);
	status = ft_redirections(&listed_tokens);
	if (status == -1)
		return (ft_tokenlstclear(&listed_tokens), NULL);
	if (status == -1917)
		return (ft_tokenlstnew(NULL, ERROR));
	return (listed_tokens);
}

void	*ft_reunite_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!*tokens)
		return (NULL);
	curr = *tokens;
	while (curr)
	{
		next = curr->next;
		if (next)
			curr = ft_handle_next_token(tokens, curr, next);
		else
			curr = curr->next;
	}
	return ((void *)1);
}

t_token	*ft_handle_next_token(t_token **tokens, t_token *curr, t_token *next)
{
	if (next->next && curr->type == COMMAND && strncmp(curr->token, "export",
			6) == 0)
		return (ft_handle_command_export(tokens, curr));
	else if (curr->type == OPTION && next->type == OPTION)
		return (ft_handle_option(tokens, curr, next));
	else if (curr->type == OPERATOR && next->type == PATH_FILE)
		return (ft_handle_operator_path_file(tokens, curr, next));
	else
		return (curr->next);
}

t_token	*ft_handle_command_export(t_token **tokens, t_token *curr)
{
	if (ft_join_export(tokens, curr->next, curr->next->next) == NULL)
		return (NULL);
	return (*tokens);
}

t_token	*ft_handle_option(t_token **tokens, t_token *curr, t_token *next)
{
	if (ft_join_options(tokens, curr, next) == NULL)
		return (NULL);
	return (*tokens);
}
