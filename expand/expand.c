/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:36:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/13 10:08:08 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_contain_variables(char *input)
{
	int	i;
	int	variable_count;
	int	j;

	i = 0;
	variable_count = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && (ft_isalpha(input[i + 1])))
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
	int	i;
	int	j;
	int	index;
	int	single_quotes;
	int	double_quotes;
	int	*expand_infos;

	i = 0;
	index = 0;
	single_quotes = 0;
	double_quotes = 0;
	expand_infos = malloc((variable_count) * sizeof(int));
	while (input[i])
	{
		if (input[i] == 39 && double_quotes == 0)
			single_quotes += ft_decr_incr(single_quotes);
		else if (input[i] == 34 && single_quotes == 0)
			double_quotes += ft_decr_incr(double_quotes);
		else if (input[i] == 36 && ft_isalpha(input[i + 1]))
		{
			expand_infos[index] = ft_should_expand(single_quotes,
					double_quotes);
			index++;
		}
		else if (input[i] == 36 && input[i + 1] == '{')
		{
			j = i + 2;
			while ((ft_isalnum(input[j]) || input[j] == '_'))
				j++;
			if (input[j] == '}')
				expand_infos[index] = ft_should_expand(single_quotes,
						double_quotes);
		}
		i++;
	}
	return (expand_infos);
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
	int		i;
	int		j;
	int		*vars;
	int		vars_number;
	char	*final_input;
	int		var_idx;

	i = 0;
	var_idx = 0;
	vars_number = ft_contain_variables(input);
	vars = ft_is_expandable(input, vars_number);
	final_input = NULL;
	while (input[i])
	{
		if (input[i] != 36)
			final_input = ft_char_join(final_input, input[i]);
		else if (input[i] == 36 && ft_isalpha(input[i + 1]))
		{
			if (var_idx < vars_number && vars[var_idx] == 1)
			{
				if (ft_var_exists(env, &input[i]))
					final_input = ft_join_var(env, final_input, &input[i]);
				while (input[i + 1] && (ft_isalnum(input[i + 1])))
					i++;
			}
			else
				final_input = ft_char_join(final_input, input[i]);
			var_idx++;
		}
		else if (input[i] == 36 && input[i + 1] == '{')
		{
			if (var_idx < vars_number && vars[var_idx] == 1)
			{
				j = i + 2;
				while ((ft_isalnum(input[j]) || input[j] == '_'))
					j++;
				if (input[j] == '}' && ft_var_exists(env, &input[i + 1]))
				{
					final_input = ft_join_var(env, final_input, &input[i + 1]);
					while (input[i + 1] && input[i] != '}')
						i++;
				}
			}
			else
				final_input = ft_char_join(final_input, input[i]);
			var_idx++;
		}
		i++;
	}
	free(input);
	free(vars);
	return (final_input);
}
