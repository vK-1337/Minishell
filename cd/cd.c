/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:48:58 by udumas            #+#    #+#             */
/*   Updated: 2024/03/23 15:45:45 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *path, t_list **env)
{
	int	status;

	if (ft_set_pwd(env) == 0)
		return (0);
	status = old_pwd_use(path, env);
	if (status != 1)
		return (status);
	status = back_home(path, env);
	if (status != 1)
		return (status);
	if (chdir(path) == -1)
	{
		if (cdpath_find(path, env) == 0)
			return (0);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory \n", 2);
		return (1);
	}
	else
	{
		ft_replace_pwd(env);
		if (ft_find_var(env, "$PWD") == NULL)
			return (perror("PWD not created: error"), 1);
	}
	return (0);
}

int	old_pwd_use(char *path, t_list **env)
{
	t_list	*old_pwd;
	char	*old_pwd_content;

	if (path == NULL)
		return (1);
	while (*path == ' ')
		(*path)++;
	if (ft_strncmp(path, "-", 1) == 0)
	{
		old_pwd = ft_find_var(env, "$OLDPWD");
		if (old_pwd == NULL || old_pwd->content == NULL)
		{
			printf("cd: OLDPWD not set\n");
			return (-1);
		}
		else
		{
			old_pwd_content = ft_strdup(old_pwd->content);
			if (ft_cd(old_pwd->content, env) == 0)
				printf("%s\n", old_pwd_content);
			free(old_pwd_content);
			return (0);
		}
	}
	return (1);
}

int	back_home(char *path, t_list **env)
{
	t_list	*home;

	if (path == NULL)
		return (1);
	while (*path == ' ')
		(*path)++;
	if (ft_strncmp(path, "~", 1) == 0)
	{
		home = ft_find_var(env, "$HOME");
		if (home == NULL || home->content == NULL)
		{
			printf("cd: HOME not set\n");
			return (-1);
		}
		else
		{
			if (ft_cd(home->content, env) == 0)
				return (0);
			return (-1);
		}
	}
	return (1);
}

int	cdpath_find(char *path, t_list **env)
{
	t_list	*cdpath;
	char	**cdpath_split;
	char	*temp;
	int		i;

	cdpath = ft_find_var(env, "$CDPATH");
	if (cdpath == NULL || cdpath->content == NULL)
		return (-1);
	cdpath_split = ft_split(cdpath->content, ':');
	i = 0;
	while (cdpath_split[i])
	{
		temp = add_slash(cdpath_split[i++]);
		temp = ft_strjoin(temp, path, 1);
		if (chdir(temp) == 0)
		{
			ft_replace_pwd(env);
			printf("%s\n", ft_find_var(env, "$PWD")->content);
			free(temp);
			ft_free_char_tab(cdpath_split);
			return (0);
		}
		free(temp);
	}
	return (free(cdpath_split), -1);
}
