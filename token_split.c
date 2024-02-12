/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:46:12 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/12 17:49:47 by vda-conc         ###   ########.fr       */
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
		if (ft_is_operator(s[i]))
		{
			i++;
			if (s[i + 1] && s[i + 1] == s[i])
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

int ft_define_delimiter(char c)
{
  if (ft_is_operator(c))
    return (c);
  else if (c == 34 || c == 39)
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
			if (str[index + 1] == 34 || str[index + 1] == 39 || ft_is_operator(str[index + 1]))
			{
				i++;
				index++;
				break ;
			}
			i++;
			index++;
		}
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
