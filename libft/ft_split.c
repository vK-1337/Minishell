/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:36:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 15:14:28 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

size_t	ft_wordlen(char const *s, char c, size_t index)
{
	size_t	i;

	i = 0;
	while (s[index] != c && s[index])
	{
		i++;
		index++;
	}
	return (i);
}

void	ft_fill_element(char *element, const char *src, size_t index,
		size_t len)
{
	size_t	i;

	i = 0;
	if (!element)
		return ;
	while (i < len && src[index])
		element[i++] = src[index++];
	element[i] = '\0';
}

char	**ft_split(char *s, char c)
{
	char	**words;

	t_norme (vars) = {0};
	vars.l = ft_count_words(s, c);
	words = malloc((vars.l + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (s[vars.i] != '\0')
	{
		if (s[vars.i] != c && s[vars.i] != '\0')
		{
			vars.k = ft_wordlen(s, c, vars.i);
			words[vars.k] = malloc((vars.k + 1) * sizeof(char));
			if (!words[vars.k])
				return (free(words), NULL);
			ft_fill_element(words[vars.k], s, vars.i, vars.j);
			vars.i += (vars.j - 1);
			vars.k++;
		}
		vars.i++;
	}
	words[vars.l] = NULL;
	return (words);
}
