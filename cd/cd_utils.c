/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:09:27 by udumas            #+#    #+#             */
/*   Updated: 2024/04/01 13:44:48 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_current_directory(char *current_directory)
{
	current_directory = malloc(sizeof(char) * SIZE);
	if (current_directory == NULL)
		return (perror("malloc() error"), NULL);
	if (getcwd(current_directory, SIZE) == NULL)
	{
		return (perror("getcwd() error"), free(current_directory), NULL);
	}
	return (current_directory);
}

int	ft_set_pwd(t_list **env)
{
	t_list	*pwd;
	char	*current_directory;

	pwd = ft_find_var(env, "$PWD");
	if (pwd == NULL)
	{
		ft_lstadd_back(env, ft_lstnew("PWD", 1, 1));
		pwd = ft_find_var(env, "$PWD");
	}
	free(pwd->content);
	current_directory = NULL;
	current_directory = ft_get_current_directory(current_directory);
	if (current_directory == NULL)
		return (0);
	pwd->content = ft_strdup(current_directory);
	free(current_directory);
	return (1);
}

int	ft_replace_pwd(t_list **env)
{
	t_list	*pwd;
	t_list	*old_pwd;
	char	*current_directory;

	current_directory = NULL;
	current_directory = ft_get_current_directory(current_directory);
	if (current_directory == NULL)
		return (0);
	old_pwd = ft_find_var(env, "$OLDPWD");
	if (old_pwd == NULL)
	{
		ft_lstadd_back(env, ft_lstnew("OLDPWD", 1, 1));
		old_pwd = ft_find_var(env, "$OLDPWD");
	}
	free(old_pwd->content);
	pwd = ft_find_var(env, "$PWD");
	old_pwd->content = ft_strdup(pwd->content);
	free(pwd->content);
	pwd->content = ft_strdup(current_directory);
	return (free(current_directory), 1);
}

void	ft_print_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory \n", STDERR_FILENO);
}
