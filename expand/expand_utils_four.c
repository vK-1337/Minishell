/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:55:47 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 23:57:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_join_helper3(char *input, char *new_str, int *i, int *j)
{
	*i = 2;
	while (input[*i])
	{
		new_str[*j] = input[*i];
		(*j)++;
		(*i)++;
	}
}

void	ft_join_helper2(char *itoa, char *new_str, int *i, int *j)
{
	while (itoa[*i])
	{
		new_str[*j] = itoa[*i];
		(*j)++;
		(*i)++;
	}
}

void	ft_join_helper(int *j, char *new_str, char *final_input)
{
	while (final_input[*j])
	{
		new_str[*j] = final_input[*j];
		(*j)++;
	}
	free(final_input);
}
