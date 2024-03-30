/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:36:17 by udumas            #+#    #+#             */
/*   Updated: 2024/01/15 16:15:56 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int status)
{
	static t_stock	*stash;
	char			*line;

	if (status == 0)
	{
		ft_cleanstash(stash);
		stash = NULL;
		return (NULL);
	}
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	ft_stock_in_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	ft_getline(stash, &line);
	ft_clean(&stash);
	if (line[0] == '\0')
	{
		ft_cleanstash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_stock_in_stash(int fd, t_stock **stash)
{
	char	*buf;
	int		readstatus;

	readstatus = 1;
	while (!ft_isnewline(*stash) && readstatus != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readstatus = read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && readstatus == 0) || readstatus == -1)
		{
			free(buf);
			return ;
		}
		buf[readstatus] = '\0';
		ft_add_newread(buf, stash, readstatus);
		free(buf);
	}
}

void	ft_add_newread(char *buf, t_stock **stash, int readstatus)
{
	t_stock	*new_content;
	t_stock	*last;
	int		i;

	new_content = malloc(sizeof(t_stock) * 1);
	if (!new_content)
		return ;
	new_content->next = NULL;
	i = 0;
	new_content->content = malloc(sizeof(char) * (readstatus + 1));
	if (new_content->content == NULL)
		return ;
	while (buf[i] != '\0' && i < readstatus)
	{
		new_content->content[i] = buf[i];
		i++;
	}
	new_content->content[i] = '\0';
	if (!*stash)
	{
		*stash = new_content;
		return ;
	}
	last = ft_stashlast(*stash);
	last->next = new_content;
}

void	ft_getline(t_stock *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	i = 0;
	ft_malloc_line(line, stash);
	if ((*line) == NULL)
		return ;
	while (stash)
	{
		j = 0;
		while (stash->content[j] != '\0')
		{
			if (stash->content[j] == '\n')
			{
				(*line)[i++] = stash->content[j];
				break ;
			}
			(*line)[i++] = stash->content[j++];
		}
		stash = stash->next;
	}
	(*line)[i] = '\0';
}

void	ft_clean(t_stock **stash)
{
	t_stock		*last;
	t_stock		*new;
	int			i;
	int			j;

	j = 0;
	new = malloc(sizeof(t_stock));
	if (!new || !stash)
		return ;
	new->next = NULL;
	last = ft_stashlast(*stash);
	i = ft_malloc_static(last, new);
	if (new->content == NULL)
		return ;
	while (last->content[i])
	{
		new->content[j] = last->content[i];
		i++;
		j++;
	}
	new->content[j] = '\0';
	ft_cleanstash(*stash);
	*stash = new;
}
