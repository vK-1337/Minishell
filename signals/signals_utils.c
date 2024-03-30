/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:07:20 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 07:08:06 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here_doc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	ft_here_doc_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
}
