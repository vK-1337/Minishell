/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:45:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 21:03:56 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_build_prompt(t_list **env)
{
	char	*hostname;
	char	*username;
	t_list	*pwd;
	t_list	*user_node;
	char	*final_prompt;

	username = NULL;
	hostname = ft_extract_hostname(ft_find_var(env,
				"$SESSION_MANAGER")->content);
	if (!hostname)
		return (NULL);
	user_node = ft_find_var(env, "$USER");
	if (user_node)
		username = user_node->content;
	pwd = ft_find_var(env, "$PWD");
	final_prompt = ft_strjoin(username, "@", 0);
	final_prompt = ft_strjoin(final_prompt, hostname, 1);
	final_prompt = ft_strjoin(final_prompt, ":", 1);
	final_prompt = ft_strjoin(final_prompt, "~", 1);
	final_prompt = ft_strjoin(final_prompt, trim_pwd(pwd->content), 1);
	final_prompt = ft_strjoin(final_prompt, "$ ", 1);
	if (!final_prompt)
		final_prompt = ft_strdup("minishell>");
	return (free(hostname), final_prompt);
}

char	*ft_extract_hostname(char *session_manager)
{
	char	*end_of_hostname;
	char	*hostname;
	int		i;

	while (*session_manager != '/')
		session_manager++;
	session_manager++;
	end_of_hostname = session_manager;
	i = 0;
	while (i++ < 12)
		end_of_hostname++;
	hostname = malloc((i + 1) * sizeof(char));
	if (!hostname)
		return (NULL);
	i = 0;
	while (session_manager != end_of_hostname)
	{
		hostname[i] = *session_manager;
		session_manager++;
		i++;
	}
	hostname[i] = '\0';
	return (hostname);
}

char	*trim_pwd(char *pwd)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	while (*pwd && *home && *pwd == *home)
	{
		pwd++;
		home++;
	}
	return (pwd);
}
