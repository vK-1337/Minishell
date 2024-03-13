/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:17:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/13 17:14:22 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **str, char *brut_input)
{
	int	i;
	int	n_option;
	int	print_start;

	i = 1;
	n_option = 0;
	print_start = 0;
	while (str[i] && ft_is_n_option(str[i]))
	{
		print_start += ft_strlen(str[i]);
		i++;
		n_option = 1;
	}
	ft_putstr_fd(brut_input + 5 + print_start, 1);
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_is_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i] != 'n')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
