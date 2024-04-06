/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:10:30 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/05 17:11:12 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	final_free(char **prompt, int *last_exit_status, t_list **env_list)
{
	free(*prompt);
	*last_exit_status = ft_find_var(env_list, "$?")->xit_status;
	ft_free_list(env_list);
	rl_clear_history();
}
