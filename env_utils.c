/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:58:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 14:05:40 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_list **env_list, char *new_var)
{
	if (!new_var || !env_list)
		return ;
	if (ft_correct_format(new_var))
	{
		if (ft_var_exists(env_list, new_var))
			ft_replace_var(env_list, new_var);
		else
			ft_lstadd_back(env_list, ft_lstnew(new_var));
	}
	else
		return ;
}

int	ft_correct_format(char *new_var)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(new_var[i])) && new_var[i] != '_')
	{
		printf("`%s': not a valid identifier\n", new_var);
		return (0);
	}
	while (new_var[i])
	{
		if (forbidden_char(new_var[i]))
		{
			printf("`%s': not a valid identifier\n", new_var);
			return (0);
		}
		if (new_var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	forbidden_char(char c)
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
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	while (curr)
	{
		if (strncmp(curr->content, var, i) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}

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
		if (strncmp(curr->content, new_var, i) == 0)
		{
			curr->content = new_var;
			return ;
		}
		curr = curr->next;
	}
}

t_list	**ft_unset(t_list **env_list, char *var_to_del)
{
	t_list	*curr;

	curr = *env_list;
	while (curr)
	{
		if (strncmp(curr->content, var_to_del, ft_strlen(var_to_del)) == 0)
		{
			if (curr->prev == NULL)
			{
				env_list = &curr->next;
				return (env_list);
			}
			else if (curr->next == NULL)
				return (ft_delete_last(curr), env_list);
			else
				return (ft_delete_connect(curr), env_list);
		}
		curr = curr->next;
	}
	return (NULL);
}
