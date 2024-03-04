/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:43:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/28 17:21:18 by udumas           ###   ########.fr       */
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
        }
        env = env->next;
	}
	return (1);
}

t_list	*ft_convert_env(char **env)
{
	int		i;
	t_list	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew((char *)env[i], 1, 1));
		i++;
	}
	return (env_list);
}
