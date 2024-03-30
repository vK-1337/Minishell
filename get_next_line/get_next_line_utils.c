/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:25:30 by udumas            #+#    #+#             */
/*   Updated: 2024/01/31 13:58:52 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_isnewline(t_stock *stash)
{
	int		i;
	t_stock	*node;

	i = 0;
	if (stash == NULL)
		return (0);
	node = ft_stashlast(stash);
	if (node->content == 0)
		return (0);
	while (node->content[i] != '\0')
	{
		if (node->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_stock	*ft_stashlast(t_stock *stash)
{
	if (!stash)
		return (NULL);
	else
	{
		while (stash->next != NULL)
			stash = stash->next;
	}
	return (stash);
}

void	ft_cleanstash(t_stock *stash)
{
	t_stock	*travel;
	t_stock	*temp;

	travel = stash;
	while (travel)
	{
		temp = travel->next;
		free(travel->content);
		free(travel);
		travel = temp;
	}
}

void	ft_malloc_line(char **line, t_stock *stash)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				j++;
				break ;
			}
			i++;
			j++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * j + 1);
}

int	ft_malloc_static(t_stock *last, t_stock *new)
{
	int		total_len;
	int		len_static;

	len_static = 0;
	total_len = 0;
	while (last->content[total_len])
		total_len++;
	while (last->content[len_static] && last->content[len_static] != '\n')
		(len_static)++;
	if (last->content && last->content[len_static] == '\n')
		(len_static)++;
	new->content = malloc(sizeof(char) * (total_len - len_static + 1));
	return (len_static);
}
