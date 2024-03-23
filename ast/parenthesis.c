/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:43:24 by udumas            #+#    #+#             */
/*   Updated: 2024/03/23 12:06:29 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_parenthesis(t_token **token);

void	parenthesis(t_ast *ast, t_list **env_list, int *exit_status)
{
	t_ast	*new_ast;
	char	*new_token;
	int	fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	new_token = remove_parenthesis(&ast->token);
	new_ast = NULL;
	if (create_ast_list(&new_ast, ft_lexer(new_token, env_list)) == NULL)
	{
		*exit_status = -1917;
		return ;
	}
	do_redirections(ast, NULL);
	launch_ast_recursive(new_ast, env_list, exit_status);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	ft_free_ast(&new_ast);
}

char	*remove_parenthesis(t_token **token)
{
	int		i;
	int		j;
	char	*new_token;

	i = 1;
	j = 0;
	new_token = malloc(sizeof(char) * ft_strlen((*token)->token) - 1);
	while ((*token)->token[i + 1] != '\0')
		new_token[j++] = (*token)->token[i++];
	new_token[j] = '\0';
	return (new_token);
}
