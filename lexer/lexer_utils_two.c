/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:31 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/30 12:58:33 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_convert_tokens(char **tokens, t_list **env)
{
	t_norme	vars;
	t_ttype	type;
	t_ttype	p;

	t_token(*tokens_list) = NULL;
	ft_init_convert_helper(&vars, &type, tokens);
	while (tokens[++vars.i])
	{
		if (vars.i == 0 && ft_contain_variables(tokens[vars.i])
			&& ft_empty_expand(tokens[vars.i], env))
		{
			free(tokens[vars.i]);
			vars.i = -1;
			tokens++;
			continue ;
		}
		if (vars.i == 0)
			type = ft_define_first_token_type(tokens, vars.j, type);
		else
			type = ft_define_subsequent_token_type(tokens, vars.i, vars.j, p);
		ft_tokenlstadd_back(&tokens_list, ft_tokenlstnew(tokens[vars.i], type));
		vars.str = tokens[vars.i];
		p = type;
	}
	return (tokens_list);
}

void	ft_init_convert_helper(t_norme *vars, t_ttype *type, char **tokens)
{
	vars->str = NULL;
	vars->j = ft_check_first_redir(tokens, type);
	vars->i = -1;
}

int	ft_empty_expand(char *token, t_list **env)
{
	t_list	*env_var;

	env_var = ft_find_var(env, token);
	if (env_var == NULL)
		return (1);
	return (0);
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
