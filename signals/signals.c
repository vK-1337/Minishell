/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:19:24 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/06 16:01:22 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_signals()
{
	signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	wait_p_handler(int signum)
{
    if (signum == SIGINT)
        printf("\n");
    else if (signum == SIGQUIT)
        printf("Quit (core dumped)\n");
}

void	ft_change_signals()
{
	signal(SIGINT, wait_p_handler);
    signal(SIGQUIT, wait_p_handler);
}