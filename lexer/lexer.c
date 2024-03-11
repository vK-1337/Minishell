/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:34:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 16:13:26 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lexer(char *input, t_list **env)
{
	char	**tokens;
	t_token	*listed_tokens;

	(void)env;
	listed_tokens = NULL;
	tokens = ft_token_split(input);
	if (!tokens)
		return (NULL);
	listed_tokens = ft_convert_tokens(tokens);
	free(tokens);
	if (!listed_tokens)
		return (NULL);
	ft_reunite_tokens(&listed_tokens);
	ft_initialize_redirection(&listed_tokens);
	ft_reunite_redirection(&listed_tokens);
	ft_print_token_list(&listed_tokens);
	return (listed_tokens);
}

void	*ft_join_export(t_token **tokens, t_token *curr, t_token *next)
{
	char	*new_token;
	t_token	*new_node;

	new_token = ft_strjoin(curr->token, next->token, 1);
	if (!new_token)
		return (NULL);
	new_node = ft_tokenlstnew(new_token, COMMAND);
	if (!new_node)
		return (NULL);
	new_node->next = next->next;
	if (curr->prev)
	{
		curr->prev->next = new_node;
		new_node->prev = curr->prev;
	}
	else
		*tokens = new_node;
	free(curr);
	free(next);
	return ((void *)1);
}

void	*ft_join_options(t_token **tokens, t_token *curr, t_token *next)
{
	char	*new_token;
	t_token	*new_node;

	new_token = ft_strjoin(curr->token, " ", 0);
	new_token = ft_strjoin(new_token, next->token, 1);
	if (!new_token)
		return (NULL);
	new_node = ft_tokenlstnew(new_token, OPTION);
	if (!new_node)
		return (NULL);
	new_node->next = next->next;
	if (curr->prev)
	{
		curr->prev->next = new_node;
		new_node->prev = curr->prev;
	}
	else
		*tokens = new_node;
	free(curr);
	free(next);
	return ((void *)1);
}

void	ft_join_file_path(t_token *curr, t_token *next)
{
	curr->file_redir = next->token;
	curr->next = next->next;
	if (next->next)
		next->next->prev = curr;
	free(next);
}

t_token	*ft_convert_tokens(char **tokens)
{
	t_norme	(vars) = {0};
	t_ttype	type;
	char	*previous_token;
	t_ttype	previous_type;
	t_token	*tokens_list;

	tokens_list = initialize_tokens_list((int *)&vars.i, (int *)&vars.j,
			&previous_token);
	while (tokens[vars.i])
	{
		type = determine_token_type(tokens, vars.i, vars.j, previous_type,
				previous_token);
		ft_tokenlstadd_back(&tokens_list, ft_tokenlstnew(tokens[vars.i], type));
		update_previous(&previous_token, &previous_type, tokens[vars.i], type);
		vars.i++;
	}
	return (tokens_list);
}
