/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:21:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/01 16:40:31 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atol(const char *str)
{
	int		i;
	long	j;
	int		sign;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	j = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		j = j * 10 + (str[i] - '0');
		i++;
	}
	return (j * sign);
}
