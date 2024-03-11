/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 07:56:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 15:09:04 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_replace_var(t_list **env_list, char *new_var)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = *env_list;
	while (new_var[i])
	{
		if (new_var[i] == '=')
			break ;
		i++;
	}
	while (curr)
	{
		if (strncmp(curr->var_name, new_var, i) == 0
			&& curr->var_name[i] == '\0')
		{
			curr->content = ft_strdup(new_var + i + 1);
			return ;
		}
		curr = curr->next;
	}
}

void	ft_display_export(t_list **env_list)
{
	t_list	*curr;
	t_list	**list_copy;
	t_list	**sorted_list;

	list_copy = ft_copy_env_list(env_list);
	sorted_list = ft_sort_nodes(list_copy);
	curr = *sorted_list;
	while (curr)
	{
		if (curr->content)
			printf("declare -x %s=\"%s\"\n", curr->var_name, curr->content);
		else if (curr->var_name[0] == '?')
		{
			curr = curr->next;
			continue ;
		}
		else
			printf("declare -x %s\n", curr->var_name);
		curr = curr->next;
	}
}

void	ft_expand_helper1(t_norme *vars, char *input, t_list **env)
{
	if (vars->j < vars->k && vars->tab[vars->j] == 1)
		ft_handle_classic_variables((int *)&vars->i, input, env, &vars->str);
	else
		vars->str = ft_char_join(vars->str, input[vars->i]);
	vars->j++;
}

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
