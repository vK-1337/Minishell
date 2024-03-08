/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:43:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/08 19:45:48 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_env(t_list *env)
{
	if (env == NULL)
		return (0);
	while (env)
	{
		if (env->env_print == 1)
		{
			printf("%s", (char *)env->var_name);
			printf("=");
			printf("%s\n", (char *)env->content);
			printf("%d\n", env->xit_status);
		}
		env = env->next;
	}
	return (0);
}

t_list	*ft_convert_env(char **env)
{
	int		i;
	t_list	*env_list;
	t_list	*tmp_new;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		tmp_new = ft_lstnew((char *)env[i], 1, 1);
		if (!tmp_new)
			return (NULL);
		ft_lstadd_back(&env_list, tmp_new);
		i++;
	}
	ft_lstadd_back(&env_list, ft_exit_variable());
	return (env_list);
}

t_list	*ft_exit_variable(void)
{
	t_list	*exit_variable;

	exit_variable = malloc(sizeof(t_list));
	if (!exit_variable)
		return (NULL);
	exit_variable->var_name = ft_strdup("?");
	exit_variable->content = ft_strdup("0");
	exit_variable->env_print = 1;
	exit_variable->next = NULL;
	exit_variable->prev = NULL;
    exit_variable->xit_status = 0;
	return (exit_variable);
}