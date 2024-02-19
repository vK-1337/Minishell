/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:19:24 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/19 18:04:34 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_signals(struct sigaction *signals)
{
	signals->sa_flags = SA_SIGINFO;
	signals->sa_sigaction = sig_handler;
	sigemptyset(&signals->sa_mask);
	sigaddset(&signals->sa_mask, SIGQUIT);
	sigaction(SIGINT, signals, NULL);
	sigaction(SIGQUIT, signals, NULL);
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	wait_p_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)signum;
    if (signum == SIGQUIT)
        printf("Quit (core dumped)\n");
    else if (signum == SIGINT)
        printf("\n");
}