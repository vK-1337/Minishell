/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:50:38 by vda-conc          #+#    #+#             */
/*   Updated: 2023/11/11 11:33:15 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char const c1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_get_index(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ft_isset(s1[i], set))
	{
		i++;
	}
	return (i);
}

size_t	ft_get_indexr(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (ft_isset(s1[i - 1], set))
	{
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s2;

	i = ft_get_index(s1, set);
	if (i == strlen(s1) || !s1)
	{
		s2 = malloc(sizeof(char));
		s2[0] = '\0';
		return (s2);
	}
	j = ft_get_indexr(s1, set);
	s2 = malloc((j - i + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	k = 0;
	while (i < j)
	{
		s2[k++] = s1[i++];
	}
	s2[k] = '\0';
	return (s2);
}
