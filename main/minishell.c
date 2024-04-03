/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/03 16:49:15 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*prompt;
	t_list	*env_list;
	int		last_exit_status;

	manage_main_args(ac, av);
	rl_catch_signals = 0;
	if (!env[0])
		return (0);
	if (initialize_main(&prompt, &env_list, env) == 1)
		return (1);
	if (minishell(&prompt, &input, &env_list) == 1)
		return (1);
	final_free(&prompt, &last_exit_status, &env_list);
	exit(last_exit_status);
}

int	minishell(char **prompt, char **input, t_list **env_list)
{
	int	main_prompt_ret;

	while (1)
	{
		ft_init_signals();
		main_prompt_ret = main_prompt(prompt, input, env_list);
		if (main_prompt_ret == 2)
			break ;
		else if (main_prompt_ret == 1)
			continue ;
		ft_change_signals();
		launch_ast(*input, env_list, &ft_find_var(env_list, "$?")->xit_status);
		if (ft_find_var(env_list, "$?")->should_end == 1)
		{
			free(*input);
			break ;
		}
		if (rebuild_prompt(prompt, input, env_list) == 1)
			return (1);
	}
	return (0);
}
