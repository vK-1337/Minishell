/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:36:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/02 18:37:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_export_cw(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] == c && ft_not_quoted((char *)s, i + 1))
				|| s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

size_t	e_wlen(char const *s, char c, size_t index)
{
	size_t	i;

	i = 0;
	while (s[index] != c && s[index])
	{
		i++;
		index++;
		while (s[index] == c && !ft_not_quoted((char *)s, index))
		{
			i++;
			index++;
		}
	}
	return (i);
}

void	ft_export_e(char *element, const char *src, size_t index, size_t len)
{
	size_t	i;

	i = 0;
	if (!element)
		return ;
	while (i < len && src[index])
		element[i++] = src[index++];
	element[i] = '\0';
}

char	**ft_export_split(char *s, char c)
{
	t_norme	vars;
	char	**words;

	if (!s)
		return (NULL);
	words = malloc((ft_export_cw(s, c) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	vars.i = 0;
	vars.j = 0;
	while (s[vars.i] != '\0')
	{
		if (s[vars.i] != c && s[vars.i] != '\0')
		{
			words[vars.j] = malloc((e_wlen(s, c, vars.i) + 1) * sizeof(char));
			if (!words[vars.j])
				return (ft_free_char_tab(words), NULL);
			ft_export_e(words[vars.j], s, vars.i, e_wlen(s, c, vars.i));
			vars.i += (e_wlen(s, c, vars.i) - 1);
			vars.j++;
		}
		vars.i++;
	}
	words[ft_export_cw(s, c)] = NULL;
	return (ft_trim_all_export(words), words);
}

void	ft_trim_all_export(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_trim_quotes(&words[i]);
		i++;
	}
}
