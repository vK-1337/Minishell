/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:45:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/03 16:52:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_matches(char **token, int (*ft_match)(char *, char *))
{
	int				count;
	struct dirent	*de;
	DIR				*dr;

	count = 0;
	dr = opendir(".");
	if (dr == NULL)
		return (0);
	de = readdir(dr);
	while (de != NULL)
	{
		if (ft_match(*token, de->d_name))
			count++;
		de = readdir(dr);
	}
    free(de);
	closedir(dr);
	return (count);
}

char	*ft_join_match_helper(char *prev_new_token, char *de_name, int count,
		int total_count)
{
	char	*new_token;

	new_token = NULL;
	if (count == 0)
	{
		if (total_count == 1)
			new_token = ft_strjoin(de_name, "", 0);
		else
			new_token = ft_strjoin(de_name, " ", 0);
		if (new_token == NULL)
			return (NULL);
	}
	else
	{
		new_token = ft_strjoin(prev_new_token, de_name, 1);
		if (count != total_count - 1)
			new_token = ft_strjoin(new_token, " ", 1);
		if (new_token == NULL)
			return (NULL);
	}
	return (new_token);
}

int	ft_replace_wildcards(char **token)
{
	int	contain_wc;

	contain_wc = ft_contain_wildcards(*token);
	if (ft_contain_quotes(*token) && !ft_is_export_var(*token))
		ft_trim_quotes(token);
	if (contain_wc == 1)
		return (ft_join_matching_dir(token, ft_match_single_wc));
	else if (contain_wc > 1)
		return (ft_join_matching_dir(token, ft_match_multiple_wc));
	return (0);
}

int	ft_is_export_var(char *token)
{
	if (!ft_isalnum(*token) && *token != '_')
		return (0);
	token++;
	if (!ft_strchr(token, '='))
		return (0);
	if (ft_after_equal(token) == 0)
		return (0);
	return (1);
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
