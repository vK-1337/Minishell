/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/19 17:50:09 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char				*input;
	char				*prompt;
	t_list				*env_list;
	struct sigaction	signals;

	(void)ac;
	(void)av;
	if (!env[0])
		return (0);
	ft_init_signals(&signals);
	signal(SIGQUIT, SIG_IGN);
	rl_bind_key('\t', rl_complete);
	env_list = ft_convert_env(env);
	prompt = ft_build_prompt(&env_list);
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		while (ft_unclosed_input(input))
			input = ft_strjoin(input, readline(">"), 1);
		add_history(input);
		ft_lexer(input, &env_list);
		if (ft_strncmp("env", input, 3) == 0)
			ft_print_env(env_list);
		else if (ft_strncmp("unset", input, 5) == 0)
			ft_unset(&env_list, &input[6]);
		else if (ft_strncmp("export", input, 6) == 0)
			ft_export(&env_list, &input[7]);
		else if (ft_strncmp(input, "exit", 4) == 0)
			break ;
		else if (ft_strncmp("unset", input, 5) == 0)
			env_list = *ft_unset(&env_list, &input[6]);
		else if (ft_strncmp("cd", input, 2) == 0)
		{
			ft_cd(&input[3], &env_list);
			free(prompt);
			prompt = ft_build_prompt(&env_list);
		}
		else if (ft_strncmp("pwd", input, 3) == 0)
			ft_pwd();
		else
			exec_shell_command(input, env_list, &signals);
	}
	ft_free_list(&env_list);
	rl_clear_history();
	free(prompt);
	return (0);
}
