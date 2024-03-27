/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:13:22 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/27 07:56:03 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_handle_next_token(t_token **tokens, t_token *curr, t_token *next)
{
	if (next->next && next->next->type == COMMAND && curr->type == COMMAND
		&& strncmp(curr->token, "export", 6) == 0)
		return (ft_handle_command_export(tokens, curr));
	else if (curr->type == OPTION && next->type == OPTION)
		return (ft_handle_option(tokens, curr, next));
	else if (curr->type == OPERATOR && next->type == PATH_FILE)
		return (ft_handle_operator_path_file(tokens, curr, next));
	else
		return (curr->next);
}
