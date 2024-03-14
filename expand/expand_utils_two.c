/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 08:48:18 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/14 12:19:58 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_find_var(t_list **env, char *input)
{
	int		i;
	t_list	*curr;

	i = 0;
	input++;
	while (input[i])
	{
		if (!ft_isalnum(input[i]))
			break ;
		i++;
	}
	if (input[0] == '?')
		i = 1;
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->var_name, input, i) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	ft_handle_brackets(int *i, char *input, t_list **env,
		char **final_input)
{
	int	j;

	j = *i + 2;
	while ((ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	if (input[j] == '}' && ft_var_exists(env, &input[*i + 1]))
	{
		*final_input = ft_join_var(env, *final_input, &input[*i + 1]);
		while (input[*i + 1] && input[*i] != '}')
			*i = *i + 1;
	}
	else
		*final_input = ft_char_join(*final_input, input[*i]);
}

void	ft_handle_classic_variables(int *i, char *input, t_list **env,
		char **final_input)
{
	if (ft_var_exists(env, &input[*i]))
		*final_input = ft_join_var(env, *final_input, &input[*i]);
	while (input[*i + 1] && (ft_isalnum(input[*i + 1]) || input[*i + 1] == '?'))
		*i = *i + 1;
}

void	ft_expand_helper1(t_norme *vars, char *input, t_list **env)
{
	if (vars->j < vars->k && vars->tab[vars->j] == 1)
		ft_handle_classic_variables((int *)&vars->i, input, env, &vars->str);
	else
		vars->str = ft_char_join(vars->str, input[vars->i]);
	vars->j++;
}
