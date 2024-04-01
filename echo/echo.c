/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:17:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/01 18:05:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **str, char *brut_input, t_ast *ast)
{
	t_norme	vars;

	ft_init_echo_vars(&vars);
	ast++;
	if (str[1] == NULL)
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	while (str[vars.i] && ft_is_n_option(str[vars.i]))
	{
		vars.k += ft_strlen(str[vars.i]) + 1;
		vars.i++;
		vars.j = 1;
	}
	if (str[vars.i])
	{
		if (vars.j >= 1)
			vars.k++;
		if (str[vars.i] && vars.j >= 1)
        {
            printf("Je passe ici\n");
			ft_putstr_fd(brut_input + 4 + vars.k, STDOUT_FILENO);
        }
		else
        {
			ft_putstr_fd(brut_input + 5 + vars.k, STDOUT_FILENO);
        }
	}
	if (!vars.j)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

void	ft_init_echo_vars(t_norme *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
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
