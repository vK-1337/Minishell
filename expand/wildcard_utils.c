/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:57:39 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/17 17:10:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_next_char_found(char pattern_char, char *name)
{
    int i;

    i = 0;
    while (name[i])
    {
        if (name[i] == pattern_char)
            return (i);
        i++;
    }
    return (0);
}
