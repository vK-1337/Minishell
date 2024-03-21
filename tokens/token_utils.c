/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:54:23 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/21 15:54:19 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_tokens(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_is_operator(s[i]))
			ft_helper1(&i, &count, s);
		else if ((s[i] == 34 || s[i] == 39))
			ft_helper2(&i, &count, s);
		else if (s[i] == 40)
			ft_helper3(&i, &count, s);
		else if (s[i] != ' ' && ft_is_separator(s[i + 1]))
			ft_helper4(&i, &count);
		else
			i++;
	}
	return (count);
}

int	ft_go_next_parenthesis(const char *str, int index)
{
	int	i;
	int	opening_parenthesis;

	i = 0;
	opening_parenthesis = 0;
	while (str[index] != 41)
	{
		if (str[index] == 40)
		{
			opening_parenthesis++;
		}
		index++;
		i++;
	}
	return (i + 1 + opening_parenthesis);
}

int	ft_go_next(const char *str, int index)
{
	int		i;
	char	go_to;

	i = 0;
	go_to = str[index];
	if (!str[index - 1] || str[index - 1] != go_to)
	{
		i++;
		index++;
		while (str[index])
		{
			if (str[index] == 32 && ft_not_quoted((char *)str, index))
				break ;
			index++;
			i++;
		}
	}
	return (i);
}

int	ft_is_separator(char c)
{
	if ( c == 60 || c == 62 || c == 124 || c == '\0'
		|| c == ' ')
		return (1);
	return (0);
}
