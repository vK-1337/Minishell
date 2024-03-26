/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/26 13:40:08 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*prompt;
	t_list	*env_list;
	int		last_exit_status;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	if (!env[0])
		return (0);
	rl_bind_key('\t', rl_complete);
	env_list = ft_convert_env(env);
	if (!env_list)
		return (printf("Error: malloc failed\n"), 1);
	prompt = ft_build_prompt(&env_list);
	if (!prompt)
		return (printf("Error: malloc failed\n"), ft_free_list(&env_list), 1);
	while (1)
	{
		ft_init_signals();
		input = readline(prompt);
		if (input == NULL)
			break ;
		while (ft_unclosed_input(input))
		{
			input = ft_strjoin(input, readline(">"), 1);
			if (!input)
				return (printf("Error: malloc failed\n"),
					ft_free_list(&env_list), free(prompt), 1);
		}
		if (!input[0])
		{
			ft_find_var(&env_list, "$?")->xit_status = 0;
			continue ;
		}
		add_history(input);
		if (check_syntax(input) == 0)
		{
			ft_find_var(&env_list, "$?")->xit_status = 2;
			continue ;
		}
		ft_change_signals();
		launch_ast(input, &env_list, &ft_find_var(&env_list, "$?")->xit_status);
		if (ft_find_var(&env_list, "$?")->should_end == 1)
			break ;
		free(prompt);
		free(input);
		prompt = ft_build_prompt(&env_list);
		if (!prompt)
			return (printf("Error: malloc failed\n"), ft_free_list(&env_list),
				1);
	}
	free(prompt);
	last_exit_status = ft_find_var(&env_list, "$?")->xit_status;
	ft_free_list(&env_list);
	rl_clear_history();
	exit(last_exit_status);
}
