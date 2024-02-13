/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:43:40 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/13 09:47:21 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(t_list *env)
{
	while (env)
	{
		printf("%s", (char *)env->var_name);
		printf("=");
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}

t_list	*ft_convert_env(char **env)
{
	int		i;
	t_list	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew((char *)env[i], 1));
		i++;
	}
	return (env_list);
}
