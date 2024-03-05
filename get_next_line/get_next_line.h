/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:36:54 by udumas            #+#    #+#             */
/*   Updated: 2024/01/15 16:16:46 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_stock
{
	char			*content;
	struct s_stock	*next;
}					t_stock;

int					ft_isnewline(t_stock *stash);
t_stock				*ft_stashlast(t_stock *stash);
void				ft_cleanstash(t_stock *stash);
int					ft_malloc_static(t_stock *last, t_stock *new);
void				ft_malloc_line(char **line, t_stock *stash);

void				ft_stock_in_stash(int fd, t_stock **stash);
void				ft_add_newread(char *buf, t_stock **stash, int readstatus);
void				ft_getline(t_stock *stash, char **line);
void				ft_clean(t_stock **stash);
char				*get_next_line(int fd, int status);
#endif