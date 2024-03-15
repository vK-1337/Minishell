/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:47:08 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/14 17:50:58 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unclosed_input(char *input)
{
	t_norme	vars;

	if (!input)
		return (0);
	ft_unclosed_input_helper(&vars);
	while (input[++vars.i])
	{
		if (input[vars.i] == 34 && ft_not_single_quoted(input, vars.i))
			vars.l++;
		else if (input[vars.i] == 39 && ft_not_double_quoted(input, vars.i))
			vars.k++;
		else if (input[vars.i] == 40 && ft_not_quoted(input, vars.i))
			vars.j++;
		else if (input[vars.i] == 41 && ft_not_quoted(input, vars.i)
			&& vars.j > 0)
			vars.j--;
	}
	if (vars.l % 2 != 0 || vars.k % 2 != 0)
		return (1);
	else if (vars.j != 0)
		return (1);
	return (0);
}

void	ft_unclosed_input_helper(t_norme *vars)
{
	vars->i = -1;
	vars->j = 0;
	vars->k = 0;
	vars->l = 0;
}

int	ft_not_quoted(char *input, int char_index)
{
	if (ft_not_double_quoted(input, char_index) && ft_not_single_quoted(input,
			char_index))
		return (1);
	return (0);
}

int	ft_not_single_quoted(char *input, int char_index)
{
	int	i;
	int	single_quotes;

	i = 0;
	single_quotes = 0;
	while (i <= char_index)
	{
		if (input[i] == 39 && ft_not_double_quoted(input, i))
			single_quotes++;
		i++;
	}
	if (single_quotes % 2 == 0 || (single_quotes % 2 != 0
			&& input[char_index] == 39))
		return (1);
	return (0);
}

int	ft_not_double_quoted(char *input, int char_index)
{
	int	i;
	int	double_quotes;

	i = 0;
	double_quotes = 0;
	while (i <= char_index)
	{
		if (input[i] == 34 && ft_not_single_quoted(input, i))
			double_quotes++;
		i++;
	}
	if (double_quotes % 2 == 0 || (double_quotes % 2 != 0
			&& input[char_index] == 34))
		return (1);
	else
		return (0);
}

void	ft_trim_quotes(char **input)
{
	int		i;
	int		j;
	int		quotes_number;
	char	*trimed_token;

	i = 0;
	j = 0;
	if (!input)
		return ;
	quotes_number = ft_count_quotes(*input);
	trimed_token = malloc(ft_strlen(*input) - quotes_number + 1);
	if (!trimed_token)
		return ;
	while (i < (int)ft_strlen(*input))
	{
		if (((*input)[i] != 34 && (*input)[i] != 39))
		{
			trimed_token[j] = (*input)[i];
			j++;
		}
		else if (((*input)[i] == 34 || (*input)[i] == 39)
			&& !ft_not_quoted(*input, i))
		{
			trimed_token[j] = (*input)[i];
			j++;
		}
		i++;
	}
	trimed_token[j] = '\0';
	free(*input);
	*input = trimed_token;
}

int	ft_count_quotes(char *input)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (input[i])
	{
		if ((input[i] == 34 || input[i] == 39) && ft_not_quoted(input, i))
			counter++;
		i++;
	}
	return (counter);
}

int	ft_contain_quotes(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
