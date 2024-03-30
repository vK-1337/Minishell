/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:28:14 by udumas            #+#    #+#             */
/*   Updated: 2024/03/30 17:39:28 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main_prompt(char **prompt, char **input, t_list **env_list)
{
	*input = readline(*prompt);
	if (*input == NULL)
		return (2);
	while (ft_unclosed_input(*input))
	{
		*input = ft_strjoin(*input, readline(">"), 1);
        if (!*input)
        {
            free(*input);
            ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
            ft_find_var(env_list, "$?")->xit_status = 2;
            return (1);
        }
	}
	if (!(*input)[0])
		ft_find_var(env_list, "$?")->xit_status = 0;
	add_history(*input);
	if (check_syntax(*input) == 0)
    {
		ft_find_var(env_list, "$?")->xit_status = 0;
        return (1);
    }
	return (0);
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

void	final_free(char **prompt, int *last_exit_status, t_list **env_list)
{
	free(*prompt);
	*last_exit_status = ft_find_var(env_list, "$?")->xit_status;
	ft_free_list(env_list);
	rl_clear_history();
}

int	initialize_main(char **prompt, t_list **env_list, char **env)
{
	rl_bind_key('\t', rl_complete);
	*env_list = ft_convert_env(env);
	if (!*env_list)
		return (printf("Error: malloc failed\n"), 1);
	*prompt = ft_build_prompt(env_list);
	if (!*prompt)
		return (printf("Error: malloc failed\n"), ft_free_list(env_list), 1);
	return (0);
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
