/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:44 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/14 13:58:17 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(char **command, t_list **env_list)
{
    int exit_status;

    exit_status = ft_atoi(ft_find_var(env_list, "$?")->content);
    if (ft_tablen(command) > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        return (1);
    }
    else if (command[1] != NULL)
    {
        if (ft_isnumber(command[1]) == 0)
        {
            ft_putstr_fd(" numeric argument required\n", 2);
            return (2);
        }
        else
        {
            exit_status = ft_atoi(command[1]);
            if (exit_status > 255 || exit_status < -255)
                exit_status = exit_status % 256;
            if (exit_status < 0)
                exit_status = (256 + exit_status) % 256;
        }
    }
    return (exit_status);
}

int ft_isnumber(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+' && str[i] != ' ' && str[i] != '"')
            return (0);
        i++;
    }
    return (1);
}