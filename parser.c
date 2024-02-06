/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:47:08 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 14:08:00 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unclosed_input(char *input)
{
	int	i;
	int	simple_quotes;
	int	double_quotes;
	int	parenthesis;

	i = -1;
	parenthesis = 0;
	double_quotes = 0;
	simple_quotes = 0;
	if (!input)
		return (0);
	while (input[++i])
	{
		if (input[i] == 34 && ft_not_single_quoted(input, i))
			double_quotes++;
		else if (input[i] == 39 && ft_not_double_quoted(input, i))
			simple_quotes++;
		else if (input[i] == 40 && ft_not_quoted(input, i))
			parenthesis++;
		else if (input[i] == 41 && ft_not_quoted(input, i))
			parenthesis--;
	}
	if (double_quotes % 2 != 0 || simple_quotes % 2 != 0)
		return (1);
	else if (parenthesis != 0)
		return (1);
	return (0);
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
	while (i < char_index)
	{
		if (input[i] == 39 && ft_not_double_quoted(input, i))
			single_quotes++;
		i++;
	}
	if (single_quotes % 2 == 0)
		return (1);
	return (0);
}

int	ft_not_double_quoted(char *input, int char_index)
{
	int i;
	int double_quotes;

	i = 0;
	double_quotes = 0;
	while (i < char_index)
	{
		if (input[i] == 34 && ft_not_single_quoted(input, i))
			double_quotes++;
		i++;
	}
	if (double_quotes % 2 == 0)
		return (1);
	return (0);
}