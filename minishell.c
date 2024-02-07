/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:36:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/07 15:50:52 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*prompt;
	t_list	*env_list;

	(void)ac;
	(void)av;
	if (!env[0])
		return (0);
	prompt = ft_build_prompt();
	rl_bind_key('\t', rl_complete);
	env_list = ft_convert_env(env);
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
    input = ft_expand(input, &env_list);
    printf("%s\n", input);
		if (strncmp("env", input, 3) == 0)
			ft_print_env(env_list);
		else if (strncmp("unset", input, 5) == 0)
			ft_unset(&env_list, &input[6]);
		else if (strncmp("export", input, 6) == 0)
			ft_export(&env_list, &input[7]);
		else if (ft_strncmp(input, "exit", 4) == 0)
			break ;
		else if (strncmp("unset", input, 5) == 0)
			env_list = *ft_unset(&env_list, &input[6]);
		else if (strncmp ("cd", input, 2) == 0)
			change_directory(&prompt, input);
	}
	ft_free_list(&env_list);
	rl_clear_history();
	free(prompt);
	return (0);
}
