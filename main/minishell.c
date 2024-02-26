/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/26 18:02:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	main(int ac, char **av, char **env)
{

	char				*input;
	char				*prompt;
	t_list				*env_list;

	(void)ac;
	(void)av;
    rl_catch_signals = 0;
	if (!env[0])
		return (0);
	rl_bind_key('\t', rl_complete);
	env_list = ft_convert_env(env);
	prompt = ft_build_prompt(&env_list);
	while (1)
	{
        ft_init_signals();
		input = readline(prompt);
        printf("Input: %s\n", input);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		while (ft_unclosed_input(input))
			input = ft_strjoin(input, readline(">"), 1);
		add_history(input);
        ft_change_signals();
        printf("Input: %s\n", input);
        printf("Input[7]: %s\n", &input[7]);
        ft_lexer(input, &env_list);
		// t_ast *test;
		// test = NULL;
		// create_ast_list(&test, ft_lexer(input, &env_list));
		// read_ast(test, 0);
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
			exec_shell_command(input, env_list);
	}
	ft_free_list(&env_list);
	rl_clear_history();
	free(prompt);
	return (0);
}
