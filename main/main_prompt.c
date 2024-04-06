/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:28:14 by udumas            #+#    #+#             */
/*   Updated: 2024/04/05 17:10:50 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main_prompt(char **prompt, char **input, t_list **env_list)
{
	char	*tmp;

	*input = readline(*prompt);
	if (*input == NULL)
		return (2);
	if (g_received_sig != 0)
		ft_change_xstatus(env_list);
	while (ft_unclosed_input(*input))
	{
		tmp = *input;
		*input = ft_strjoin(*input, readline(">"), 1);
		if (!*input)
		{
			ft_putstr_fd("bash: syntax error: unexpected end of file\n",
				STDERR_FILENO);
			ft_find_var(env_list, "$?")->xit_status = 2;
			return (free(tmp), free(*input), 1);
		}
	}
	if (!(*input)[0])
		ft_find_var(env_list, "$?")->xit_status = 0;
	if (check_syntax(*input) == 0)
		return (main_prompt_helper(env_list, input), 1);
	return (add_history(*input), 0);
}

int	rebuild_prompt(char **prompt, char **input, t_list **env_list)
{
	free(*input);
	free(*prompt);
	*prompt = ft_build_prompt(env_list);
	if (!*prompt)
		return (printf("Error: malloc failed\n"), ft_free_list(env_list), 1);
	return (0);
}

int	initialize_main(char **prompt, t_list **env_list, char **env)
{
	*env_list = ft_convert_env(env);
	if (!*env_list)
		return (printf("Error: malloc failed\n"), 1);
	*prompt = ft_build_prompt(env_list);
	if (!*prompt)
		return (printf("Error: malloc failed\n"), ft_free_list(env_list), 1);
	return (0);
}

void	main_prompt_helper(t_list **env_list, char **input)
{
	ft_find_var(env_list, "$?")->xit_status = 2;
	add_history(*input);
}

void	manage_main_args(int ac, char **av)
{
	if (ac > 1)
	{
		printf("minishell: too many arguments\n");
		exit(1);
	}
	if (ac == 1)
		return ;
	if (ft_strcmp(av[1], "-h") == 0)
	{
		printf("Usage: minishell\n");
		exit(0);
	}
	printf("minishell: invalid option\n");
	exit(1);
}
