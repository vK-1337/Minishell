/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:58:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 10:56:08 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_list **env_list, char *new_var)
{
	if (!env_list)
		return (1);
	if (!new_var)
		return (ft_display_export(env_list), 1);
	if (ft_correct_format(new_var))
	{
		if (ft_var_exists(env_list, new_var))
			ft_replace_var(env_list, new_var);
		else if (ft_contain_equal(new_var))
			ft_lstadd_back(env_list, ft_lstnew(new_var, 1, 1));
		else
			ft_lstadd_back(env_list, ft_lstnew(new_var, 1, 0));
		return (0);
	}
	else
		return (1);
}

int	ft_contain_equal(char *new_var)
{
	int	i;

	i = 0;
	while (new_var[i])
	{
		if (new_var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_correct_format(char *new_var)
{
	int	i;

	i = 0;
	if (!new_var)
		return (0);
	if (!(ft_isalpha(new_var[i])) && new_var[i] != '_')
	{
		printf("`%s': not a valid identifier\n", new_var);
		return (0);
	}
	while (new_var[i])
	{
		if (ft_forbidden_char(new_var[i]))
		{
			printf("`%s': not a valid identifier\n", new_var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_forbidden_char(char c)
{
	int		i;
	char	*charset;

	i = 0;
	charset = "!@#$%^&*(){}[]|;:<>,?/";
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_var_exists(t_list **env_list, char *var)
{
	t_list	*curr;
	int		i;

	curr = *env_list;
	i = 0;
	while (ft_isalnum(var[i + 1]) || var[i + 1] == '_' || var[i + 1] == '?')
		i++;
	if (var[0] == '$' || var[0] == '{')
		var++;
	else
		i++;
	while (curr)
	{
		if (ft_strncmp(curr->var_name, var, i) == 0
			&& curr->var_name[i] == '\0')
			return (1);
		curr = curr->next;
	}
	return (0);
}
