/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:03:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 19:40:44 by vda-conc         ###   ########.fr       */
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
