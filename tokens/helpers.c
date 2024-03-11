/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:17:25 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 05:42:45 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_helper1(int *i, int *count, char const *s)
{
	(*i)++;
	if (s[*i] == s[*i - 1])
		(*i)++;
	(*count)++;
}

void	ft_helper2(int *i, int *count, char const *s)
{
	if (s[*i + 1])
		*i += ft_go_next(s, *i);
	(*count)++;
}

void	ft_helper3(int *i, int *count, char const *s)
{
	*i += ft_go_next_parenthesis(s, *i);
	(*count)++;
}

void	ft_helper4(int *i, int *count)
{
	(*i)++;
	(*count)++;
}
