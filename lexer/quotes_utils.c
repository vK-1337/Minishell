/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:00:30 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 23:41:14 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_trim_quotes_utils(trimed_token, input, &i, &j);
	}
	trimed_token[j] = '\0';
	free(*input);
	*input = trimed_token;
}

void	ft_trim_quotes_utils(char *trimed_token, char **input, int *i, int *j)
{
	if (((*input)[*i] != 34 && (*input)[*i] != 39))
	{
		trimed_token[*j] = (*input)[*i];
		(*j)++;
	}
	else if (((*input)[*i] == 34 || (*input)[*i] == 39)
		&& !ft_not_quoted(*input, *i))
	{
		trimed_token[*j] = (*input)[*i];
		(*j)++;
	}
	(*i)++;
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
