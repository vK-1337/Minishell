/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:19:24 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/05 16:25:57 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_received_sig = 130;
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	wait_p_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_received_sig = 130;
		printf("\n");
	}
	else if (signum == SIGQUIT)
	{
		g_received_sig = 131;
		printf("Quit (core dumped)\n");
	}
}

void	ft_change_signals(void)
{
	signal(SIGINT, wait_p_handler);
	signal(SIGQUIT, wait_p_handler);
}

void	ft_change_xstatus(t_list **env_list)
{
	ft_find_var(env_list, "$?")->xit_status = g_received_sig;
	g_received_sig = 0;
}
