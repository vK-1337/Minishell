/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:38:41 by udumas            #+#    #+#             */
/*   Updated: 2024/03/27 04:50:24 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*take_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	ft_free_char_tab(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*add_slash(char *cmd1)
{
	int		i;
	char	*cmd_slash;

	i = 0;
	while (cmd1[i])
		i++;
	cmd_slash = malloc(sizeof(char) * i + 2);
	i = 0;
	while (cmd1[i])
	{
		cmd_slash[i] = cmd1[i];
		i++;
	}
	cmd_slash[i] = '/';
	cmd_slash[i + 1] = '\0';
	return (cmd_slash);
}

int	check_env(t_list *env, t_list **env_node, char **env_str)
{
	if (!env)
		return (-1);
	*env_node = env;
	*env_str = ft_strdup("");
	if (!*env_str)
		return (-1);
	return (0);
}

char	**redo_env(t_list *env)
{
	t_list	*env_node;
	char	*env_str;
	char	*temp;
	char	**split_env;

	if (check_env(env, &env_node, &env_str) == -1)
	{
		return (NULL);
	}
	while (env_node)
	{
		temp = ft_strjoin(env_node->var_name, "=", 0);
		if (!temp)
			return (free(env_str), NULL);
		env_str = ft_strjoin(env_str, temp, 1);
		free(temp);
		env_str = ft_strjoin(env_str, env_node->content, 1);
		env_str = ft_strjoin(env_str, "\n", 1);
		if (!env_str)
			return (NULL);
		env_node = env_node->next;
	}
	split_env = ft_split(env_str, '\n');
	free(env_str);
	return (split_env);
}
