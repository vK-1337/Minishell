/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:46:12 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 13:06:54 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_token_split(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	words_nbr;
	size_t	word_len;
	char	**words;

	words_nbr = ft_count_tokens(s);
	words = malloc((words_nbr + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i])
		{
			word_len = ft_tokenlen(s, i);
			words[j] = malloc((word_len + 1) * sizeof(char));
			if (!words[j])
				return (free(words), NULL);
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
