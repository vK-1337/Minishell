/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:58:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/09 13:12:17 by udumas           ###   ########.fr       */
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
	if (var[0] == '$')
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
	sorted_list = ft_sort_nodes(env_list);
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

t_list	**ft_copy_env_list(t_list **env_list)
{
	t_list	*curr;
	t_list	**copy;
	t_list	*node_copy;

	curr = *env_list;
	copy = NULL;
	while (curr)
	{
		node_copy = ft_copy_env_node(curr);
		if (!node_copy)
			return (NULL);
		ft_lstadd_back(copy, node_copy);
		curr = curr->next;
	}
	return (copy);
}

t_list	*ft_copy_env_node(t_list *env_node)
{
	t_list	*copy;

	copy = malloc(sizeof(t_list));
	if (!copy)
		return (NULL);
	copy->content = env_node->content;
	copy->var_name = env_node->var_name;
	copy->next = NULL;
	copy->prev = NULL;
	return (copy);
}

t_list	**ft_sort_nodes(t_list **env_list)
{
	t_list	*curr;
	t_list	*tmp;
	t_list	*last_node;
	int		i;

	curr = *env_list;
	curr = curr->next;
	i = 0;
	while (curr)
	{
		tmp = curr->next;
		while (curr->prev && ft_is_prev_greater(curr->var_name,
				curr->prev->var_name))
			ft_swapback_nodes(curr->prev, curr);
		curr = tmp;
		if (curr)
			last_node = curr;
	}
	curr = last_node;
	while (curr)
	{
		last_node = curr;
		curr = curr->prev;
	}
	*env_list = last_node;
	return (env_list);
}
void	ft_swapback_nodes(t_list *prev, t_list *curr)
{
	t_list	*prev_tmp;
	t_list	*next_tmp;

	next_tmp = curr->next;
	prev_tmp = prev->prev;
	if (curr->next)
	{
		curr->next->prev = prev;
	}
	curr->next = prev;
	curr->prev = prev_tmp;
	if (prev->prev)
		prev->prev->next = curr;
	prev->next = next_tmp;
	prev->prev = curr;
}

int	ft_is_prev_greater(char *curr_var, char *prev_var)
{
	int i;

	i = 0;
	if (!prev_var)
		return (0);
	while (curr_var[i] && prev_var[i])
	{
		if (curr_var[i] == prev_var[i])
			i++;
		else if (prev_var[i] > curr_var[i])
			return (1);
		else
			return (0);
	}
	return (1337);
}