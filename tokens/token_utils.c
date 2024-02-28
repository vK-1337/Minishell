/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:54:23 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/28 16:49:46 by vda-conc         ###   ########.fr       */
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
		{
			i++;
			if (s[i] == s[i - 1])
				i++;
			count++;
		}
		else if ((s[i] == 34 || s[i] == 39))
		{
			if (s[i + 1])
				i += ft_go_next(s, i);
			count++;
		}
		else if (s[i] != ' ' && ft_is_separator(s[i + 1]))
		{
			i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	ft_go_next(const char *str, int index)
{
	int		i;
	char	go_to;

	i = 0;
	go_to = str[index];
	if (str[index - 1] != go_to)
	{
		i++;
		index++;
		while (str[index] != go_to)
		{
			index++;
			i++;
		}
	}
	return (i + 1);
}

int	ft_is_separator(char c)
{
	if (c == 34 || c == 39 || c == 60 || c == 62 || c == 124 || c == '\0'
		|| c == ' ')
		return (1);
	return (0);
}
