/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:45:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/13 10:19:15 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_join_matching_dir(char **token, int (*ft_match)(char *, char *))
{
	struct dirent	*de;
	DIR				*dr;
	int				count;

	count = 0;
	dr = opendir(".");
	if (dr == NULL)
		return (0);
	de = readdir(dr);
	while (de != NULL)
	{
		if (ft_match(*token, de->d_name))
		{
			*token = ft_join_match_helper(*token, de->d_name, count);
			if (token == NULL)
				return (0);
			count++;
		}
		de = readdir(dr);
	}
	if (!count)
		return (closedir(dr), 1);
	return (closedir(dr), 0);
}

char	*ft_join_match_helper(char *token, char *de_name, int count)
{
	if (count == 0)
	{
		token = ft_strjoin(de_name, " ", 0);
		if (token == NULL)
			return (NULL);
	}
	else
	{
		token = ft_strjoin(token, de_name, 1);
		token = ft_strjoin(token, " ", 1);
		if (token == NULL)
			return (NULL);
	}
	return (token);
}

int	ft_replace_wildcards(char *token)
{
	int	contain_wc;

	contain_wc = ft_contain_wildcards(*token);
	if (contain_wc == 1)
		return (ft_join_matching_dir(token, ft_match_single_wc));
	else if (contain_wc > 1)
		return (ft_join_matching_dir(token, ft_match_multiple_wc));
	return (0);
}

int	ft_contain_wildcards(char *input)
{
	int	i;
	int	single_quotes;
	int	double_quotes;
	int	counter;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	counter = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == 34)
			single_quotes += ft_decr_incr(single_quotes);
		if (input[i] == 39)
			double_quotes += ft_decr_incr(double_quotes);
		if (input[i] == 42 && !double_quotes && !single_quotes)
			counter++;
		i++;
	}
	return (counter);
}

int	ft_match_multiple_wc(char *pattern, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i] && name[j])
	{
		if (pattern[i] != '*' && pattern[i] != name[j])
			return (0);
		else if (pattern[i] == '*' && pattern[i + 1])
		{
			if (ft_next_char_found(pattern[i + 1], &name[j]))
				j += ft_next_char_found(pattern[(i++) + 1], &name[j]);
			else
				return (0);
		}
		else if (pattern[i] == name[j] && name[j] != '*')
		{
			i++;
			j++;
		}
		if (!pattern[i + 1])
			return (1);
	}
	return (1);
}
