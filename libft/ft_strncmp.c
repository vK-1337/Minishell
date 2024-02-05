/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:28:21 by vk                #+#    #+#             */
/*   Updated: 2023/11/14 16:14:36 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	int		cmp_count;
	size_t	i;

	if ((!first && !second) || length == 0)
		return (0);
	i = 0;
	cmp_count = 0;
	while (i < length && (first[i] || second[i]))
	{
		if (first[i] != second[i])
			return ((unsigned char)(first[i]) - (unsigned char)(second[i]));
		i++;
	}
	return (0);
}
