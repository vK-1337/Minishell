/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:45:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/17 17:10:21 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_replace_wildcards(char *token)
{
	struct dirent	*de;
	DIR				*dr;
	int				contain_wc;

	dr = opendir(".");
	if (dr == NULL)
		return (printf("Could not open current directory"), 0);
	contain_wc = ft_contain_wildcards(token);
	if (contain_wc == 1)
	{
		while ((de = readdir(dr)) != NULL)
		{
			if (ft_match_single_wc(token, de->d_name))
				printf("%s ", de->d_name);
		}
	}
	else if (contain_wc > 1)
	{
		while ((de = readdir(dr)) != NULL)
		{
			if (ft_match_multiple_wc(token, de->d_name))
				printf("%s ", de->d_name);
		}
	}
	return (closedir(dr), 0);
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

int	ft_match_single_wc(char *pattern, char *name)
{
	int	wildcard_index;
	int	patt_len;
	int	after_wild;

	patt_len = ft_strlen(pattern);
	wildcard_index = 0;
	while (pattern[wildcard_index] != 42)
		wildcard_index++;
	after_wild = patt_len - wildcard_index;
	if ((unsigned long)wildcard_index == (ft_strlen(pattern) - 1))
		return (ft_starting_match(pattern, name));
	else if (wildcard_index == 0)
		return (ft_ending_match(pattern, name));
	else
		return (ft_both_match(pattern, name));
}

int	ft_starting_match(char *pattern, char *name)
{
	int	i;

	i = 0;
	if (name[0] == '.')
		return (0);
	while (pattern[i] != '*' && name[i])
	{
		if (pattern[i] != name[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_ending_match(char *pattern, char *name)
{
	int	patt_len;
	int	name_len;

	name_len = ft_strlen(name) - 1;
	patt_len = ft_strlen(pattern) - 1;
	if (name[0] == '.')
		return (0);
	while (pattern[patt_len] != '*' && name[name_len])
	{
		if (pattern[patt_len] != name[name_len])
			return (0);
		patt_len--;
		name_len--;
	}
	return (1);
}

int	ft_both_match(char *pattern, char *name)
{
	if (ft_starting_match(pattern, name) && ft_ending_match(pattern, name))
		return (1);
	return (0);
}
