/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:43:33 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/23 15:28:43 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_parentheses(const char *str, int index)
{
	int	i;
	int	opening_parenthesis;

	i = 0;
	opening_parenthesis = 1;
	index++;
	while (str[index])
	{
		if (str[index] == 41)
			opening_parenthesis--;
		if (str[index] == 40)
		{
			i++;
			opening_parenthesis++;
		}
		if (str[index] == 41 && opening_parenthesis == 0)
			break ;
		index++;
		i++;
	}
	return (i);
}

int	handle_non_space_delimiter(const char *str, int index, int delimiter)
{
	if (str[index + 1] && str[index + 1] == delimiter)
		return (2);
	else
		return (1);
}

int	handle_space_delimiter(const char *str, int index, int delimiter)
{
	int	i;

	i = 0;
	while (str[index] && str[index] != delimiter)
	{
		if (ft_is_operator(str[index + 1]))
		{
			i++;
			index++;
			break ;
		}
		i++;
		index++;
	}
	return (i);
}

int	determine_return_value(int delimiter, int i)
{
	if (delimiter == 34 || delimiter == 39 || delimiter == 40)
		return (i + 2);
	else
		return (i);
}

void	ft_print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token numero |%d| => |%s|\n", i + 1, tokens[i]);
		i++;
	}
}
