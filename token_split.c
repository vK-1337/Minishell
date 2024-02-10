/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:46:12 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/10 11:25:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_tokens(char const *s)
{
	int	i;
	int	count;
	int	double_quotes;
	int	single_quotes;

	i = 0;
	count = 0;
	double_quotes = 0;
	single_quotes = 0;
	while (s[i])
	{
		if (s[i] == 34)
			double_quotes += ft_decr_incr(double_quotes);
		if (s[i] == 39)
			single_quotes += ft_decr_incr(single_quotes);
		if (s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0'))
		{
			if (single_quotes == 0 && double_quotes == 0)
				count++;
		}
		i++;
	}
	return (count);
}

char	**ft_token_split(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	words_nbr;
	size_t	word_len;
	char	**words;

	words_nbr = ft_count_tokens(s);
	words = malloc((words_nbr + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i])
		{
			word_len = ft_tokenlen(s, i);
			words[j] = malloc((word_len + 1) * sizeof(char));
			ft_add_token(words[j], s, i, word_len);
			i += (word_len - 1);
			j++;
		}
		i++;
	}
	words[words_nbr] = NULL;
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

int	ft_tokenlen(const char *str, int index)
{
	int	i;
	int	delimiter;

	i = 0;
	if (str[index] == 34 || str[index] == 39)
	{
		delimiter = str[index];
		index++;
	}
	else
		delimiter = ' ';
	while (str[index] != delimiter && str[index])
	{
		i++;
		index++;
	}
	if (delimiter == 34 || delimiter == 39)
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
