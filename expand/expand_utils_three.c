/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:07:39 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/12 14:08:04 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_helper2(t_norme *vars, char *input, t_list **env)
{
	if (vars->j < vars->k && vars->tab[vars->j] == 1)
		ft_handle_brackets((int *)&vars->i, input, env, &vars->str);
	else
		vars->str = ft_char_join(vars->str, input[vars->i]);
	vars->j++;
}

void	is_expandable_helper(t_norme *vars, char *input)
{
	vars->j = vars->i + 2;
	while ((ft_isalnum(input[vars->j]) || input[vars->j] == '_'))
		vars->j++;
	if (input[vars->j] == '}')
		vars->tab[vars->index] = ft_should_expand(vars->k, vars->l);
}
