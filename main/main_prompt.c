/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:28:14 by udumas            #+#    #+#             */
/*   Updated: 2024/03/28 04:38:40 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main_prompt(char **prompt, char **input, t_list **env_list)
{
	*input = readline(*prompt);
	if (*input == NULL)
		return (1);
	while (ft_unclosed_input(*input))
	{
		*input = ft_strjoin(*input, readline(">"), 1);
		if (!*input)
			return (printf("Error: malloc failed\n"), 1);
	}
	if (!(*input)[0])
		ft_find_var(env_list, "$?")->xit_status = 0;
	add_history(*input);
	if (check_syntax(*input) == 0)
		ft_find_var(env_list, "$?")->xit_status = 2;
    return (0);
}

