/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:25:17 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/01 16:40:01 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ltoa_isneg(long n)
{
	if (n < 0)
		return (1);
	return (0);
}

size_t	ft_ltoa_nbrlen(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long n)
{
	size_t	len;
	int		neg;
	char	*number;
	long	nbr;

	nbr = n;
	neg = ft_ltoa_isneg(nbr);
	if (n < 0)
		nbr *= -1;
	len = ft_ltoa_nbrlen(nbr);
	number = malloc((len + 1 + neg) * sizeof(char));
	if (!number)
		return (NULL);
	if (n < 0)
		number[0] = '-';
	number[len + neg] = '\0';
	while (len > 0)
	{
		if (n >= 0)
			number[(len--) - 1] = ((nbr % 10) + '0');
		else
			number[(len--)] = ((nbr % 10) + '0');
		nbr /= 10;
	}
	return (number);
}
