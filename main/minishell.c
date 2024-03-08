/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/06 17:37:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*prompt;
	t_list	*env_list;

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
		{
			printf("exit\n");
			break ;
		}
		while (ft_unclosed_input(input))
		{
			input = ft_strjoin(input, readline(">"), 1);
			if (!input)
				return (printf("Error: malloc failed\n"), ft_free_list(&env_list), free(prompt), 1);
		}
		add_history(input);
		if (check_syntax(input) == 0)
			continue ;
		ft_change_signals();
		if (launch_ast(input, env_list) == 1917 || launch_ast(input, env_list) == -1917)
			break ;
		free(prompt);
		prompt = ft_build_prompt(&env_list);
		if (!prompt)
			return (printf("Error: malloc failed\n"), ft_free_list(&env_list), 1);
	}
	ft_free_list(&env_list);
	rl_clear_history();
	free(prompt);
	return (0);
}
