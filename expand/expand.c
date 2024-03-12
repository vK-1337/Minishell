/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:36:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 14:16:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_contain_variables(char *input)
{
	int	i;
	int	j;
	int	variable_count;

	i = 0;
	variable_count = 0;
	j = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1]) || (input[i
						+ 1] == '?')))
			variable_count++;
		if (input[i] == '$' && input[i + 1] == '{')
		{
			j = i + 2;
			while ((ft_isalnum(input[j]) || input[j] == '_'))
				j++;
			if (input[j] == '}')
				variable_count++;
		}
		i++;
	}
	return (variable_count);
}

int	*ft_is_expandable(char *input, int variable_count)
{
	t_norme(vars) = {0};
	vars.tab = malloc((variable_count) * sizeof(int));
	while (input[vars.i])
	{
		if (input[vars.i] == 39 && vars.l == 0)
			vars.k += ft_decr_incr(vars.k);
		else if (input[vars.i] == 34 && vars.k == 0)
			vars.l += ft_decr_incr(vars.l);
		else if (input[vars.i] == 36 && (ft_isalpha(input[vars.i + 1])
				|| input[vars.i + 1] == '?'))
		{
			vars.tab[vars.index] = ft_should_expand(vars.k, vars.l);
			vars.index++;
		}
		else if (input[vars.i] == 36 && input[vars.i + 1] == '{')
			is_expandable_helper(&vars, input);
		vars.i++;
	}
	return (vars.tab);
}

int	ft_decr_incr(int condition)
{
	if (condition == 1)
		return (-1);
	else if (condition == 0)
		return (1);
	return (1337);
}

int	ft_should_expand(int single_quotes, int double_quotes)
{
	if (double_quotes == 0 && single_quotes == 0)
		return (1);
	else if (double_quotes == 1 && single_quotes == 0)
		return (1);
	else if (double_quotes == 0 && single_quotes == 1)
		return (0);
	return (1337);
}

char	*ft_expand(char *input, t_list **env)
{
	t_norme	vars;

	vars.i = 0;
	vars.j = 0;
	vars.k = ft_contain_variables(input);
	if (!vars.k)
		return (input);
	vars.tab = ft_is_expandable(input, vars.k);
	vars.str = NULL;
	while (input[vars.i])
	{
		if (input[vars.i] != 36)
			vars.str = ft_char_join(vars.str, input[vars.i]);
		else if (input[vars.i] == 36 && (ft_isalpha(input[vars.i + 1])
				|| input[vars.i + 1] == '?'))
			ft_expand_helper1(&vars, input, env);
		else if (input[vars.i] == 36 && input[vars.i + 1] == '{')
			ft_expand_helper2(&vars, input, env);
		vars.i++;
	}
	free(input);
	free(vars.tab);
	return (vars.str);
}
