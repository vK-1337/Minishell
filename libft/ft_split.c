/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:36:55 by vda-conc          #+#    #+#             */
/*   Updated: 2023/11/14 15:55:48 by vda-conc         ###   ########.fr       */
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
	while (i < len && src[index])
		element[i++] = src[index++];
	element[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	words_nbr;
	size_t	word_len;
	char	**words;

	words_nbr = ft_count_words(s, c);
	words = malloc((words_nbr + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			word_len = ft_wordlen(s, c, i);
			words[j] = malloc((word_len + 1) * sizeof(char));
			ft_fill_element(words[j], s, i, word_len);
			i += (word_len - 1);
			j++;
		}
		i++;
	}
	words[words_nbr] = NULL;
	return (words);
}
