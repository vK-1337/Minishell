/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:03:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/29 14:50:48 by vda-conc         ###   ########.fr       */
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
	t_norme			vars;

	DIR(*dr) = NULL;
	ft_init_join_matching_dir(&vars, token, &dr, ft_match);
	if (dr == NULL || vars.j == 0)
		return (0);
	de = readdir(dr);
	while (de != NULL)
	{
		if (ft_match(*token, de->d_name))
		{
			vars.str = ft_join_match_helper(vars.str, de->d_name, vars.i,
					vars.j);
			if (vars.str == NULL)
				return (0);
			vars.i++;
		}
		de = readdir(dr);
	}
	free(*token);
	*token = vars.str;
	if (!vars.i)
		return (closedir(dr), 1);
	return (closedir(dr), 0);
}

void	ft_init_join_matching_dir(t_norme *vars, char **token, DIR **dr,
		int (*ft_match)(char *, char *))
{
	vars->str = NULL;
	vars->i = 0;
	vars->j = ft_count_matches(token, ft_match);
	*dr = opendir(".");
	return ;
}
