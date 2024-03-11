/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:46:12 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 16:05:04 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_token_split(char const *s)
{
	char	**words;

	t_norme(vars) = {0};
	vars.k = ft_count_tokens(s);
	words = malloc((vars.k + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (s[(size_t)vars.i])
	{
		if (s[(size_t)vars.i] != ' ' && s[(size_t)vars.i])
		{
			vars.l = ft_tokenlen(s, vars.i);
			words[(size_t)vars.j] = malloc(((size_t)vars.l + 1) * sizeof(char));
			if (!words[(size_t)vars.j])
				return (free(words), NULL);
			ft_add_token(words[(size_t)vars.j], s, (size_t)vars.i,
				(size_t)vars.l);
			vars.i += ((size_t)vars.l - 1);
			vars.j++;
		}
		vars.i++;
	}
	words[(size_t)vars.k] = NULL;
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

	i = 0;
	index++;
	while (str[index] != delimiter)
	{
		index++;
		i++;
	}
	return (i);
}
