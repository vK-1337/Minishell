/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:46:12 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/19 16:40:20 by vda-conc         ###   ########.fr       */
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
	{
		index++;
		while (str[index] != delimiter)
		{
			index++;
			i++;
		}
	}
    else if (delimiter == 40)
    {
        index++;
        while (str[index] != 41)
        {
            index++;
            i++;
        }
    }
	else if (delimiter != 32)
	{
		if (str[index + 1] && str[index + 1] == delimiter)
			i = 2;
		else
			i = 1;
	}
	else
	{
		while (str[index] && str[index] != delimiter)
		{
			if (str[index + 1] == 34 || str[index + 1] == 39
				|| ft_is_operator(str[index + 1]))
			{
				i++;
				index++;
				break ;
			}
			i++;
			index++;
		}
	}
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
