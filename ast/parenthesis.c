/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:43:24 by udumas            #+#    #+#             */
/*   Updated: 2024/03/11 20:51:35 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_parenthesis(t_token **token);

void	parenthesis(t_ast *ast, t_list *env_list, int *exit_status)
{
	t_ast	*new_ast;
	char	*new_token;

	new_token = remove_parenthesis(&ast->token);
	new_ast = NULL;
	if (create_ast_list(&new_ast, ft_lexer(new_token, &env_list)) == NULL)
	{
		*exit_status = -1917;
		return ;
	}
	launch_ast_recursive(new_ast, env_list, exit_status);
	ft_free_ast(new_ast);
}

char	*remove_parenthesis(t_token **token)
{
	int		i;
	int		j;
	char	*new_token;

	i = 1;
	j = 0;
	new_token = malloc(sizeof(char) * ft_strlen((*token)->token) - 1);
	printf("token: %s\n", (*token)->token);
	while ((*token)->token[i + 1] != '\0')
		new_token[j++] = (*token)->token[i++];
	new_token[j] = '\0';
	return (new_token);
}
