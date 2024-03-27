/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:03:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 22:59:14 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_join_matching_dir(char **token, int (*ft_match)(char *, char *))
{
	struct dirent	*de;
	DIR				*dr;
	int				count;
	char			*new_token;
	int				total_matches;

	count = 0;
	total_matches = ft_count_matches(token, ft_match);
	if (total_matches == 0)
		return (0);
	dr = opendir(".");
	if (dr == NULL)
		return (0);
	de = readdir(dr);
	while (de != NULL)
	{
		if (ft_match(*token, de->d_name))
		{
			new_token = ft_join_match_helper(new_token, de->d_name, count,
					total_matches);
			if (new_token == NULL)
				return (0);
			count++;
		}
		de = readdir(dr);
	}
	*token = new_token;
	if (!count)
		return (closedir(dr), 1);
	return (closedir(dr), 0);
}
