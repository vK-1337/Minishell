/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:57:39 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 14:36:37 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_next_char_found(char pattern_char, char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == pattern_char)
			return (i);
		i++;
	}
	return (0);
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
