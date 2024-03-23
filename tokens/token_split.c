/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:46:12 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/23 15:04:35 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_token_split(char const *s)
{
	t_norme	vars;
	char	**words;

	vars.k = ft_count_tokens(s);
	words = malloc((vars.k + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	vars.i = 0;
	vars.j = 0;
	while (s[vars.i])
	{
		if (s[vars.i] != ' ' && s[vars.i])
		{
			vars.l = ft_tokenlen(s, vars.i);
			words[vars.j] = malloc((vars.l + 1) * sizeof(char));
			if (!words[vars.j])
				return (free(words), NULL);
			ft_add_token(words[vars.j], s, vars.i, vars.l);
			vars.i += (vars.l - 1);
			vars.j++;
		}
		vars.i++;
	}
	words[vars.k] = NULL;
	return (words);
}

void	ft_add_token(char *element, const char *src, size_t index, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[index])
		element[i++] = src[index++];
	element[i] = '\0';
}

int	ft_define_delimiter(char c)
{
	if (ft_is_operator(c))
		return (c);
	else if (c == 34 || c == 39)
		return (c);
	else if (c == 40)
		return (c);
	else
		return (32);
}

int	ft_tokenlen(const char *str, int index)
{
	int	i;
	int	delimiter;

	i = 0;
	delimiter = ft_define_delimiter(str[index]);
	if (delimiter == 34 || delimiter == 39)
		i = handle_quotes(str, index, delimiter);
	else if (delimiter == 40)
		i = handle_parentheses(str, index);
	else if (delimiter != 32)
		i = handle_non_space_delimiter(str, index, delimiter);
	else
		i = handle_space_delimiter(str, index, delimiter);
	return (determine_return_value(delimiter, i));
}

int	handle_quotes(const char *str, int index, int delimiter)
{
	int	i;

	(void)delimiter;
	i = 0;
	index++;
	while (str[index])
	{
		if (!str[index + 1] || (ft_not_quoted((char *)str, index + 1)
				&& str[index + 1] == 32) || (ft_is_operator(str[index + 1]
					&& ft_not_quoted((char *)str, index + 1))))
		{
			break ;
		}
		index++;
		i++;
	}
	return (i);
}
