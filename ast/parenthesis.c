/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:43:24 by udumas            #+#    #+#             */
/*   Updated: 2024/04/03 16:36:21 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_parenthesis(t_token **token);

int	parenthesis(t_ast *ast, t_list **env_list, int *exit_status)
{
	t_ast	*new_ast;
	char	*new_token;
	int		fd[2];
	t_token	*lexer;

	initialize_fd_ast(fd, &new_ast);
	new_token = remove_parenthesis(&ast->token);
	lexer = ft_lexer(new_token, env_list);
	if (!lexer)
		return (free(new_token), ft_close_fd(fd), -1917);
	if (lexer && lexer->type == ERROR)
		return (ft_tokenlstclear(&lexer), free(new_token), ft_close_fd(fd),
			-1917);
	if (create_ast_list(&new_ast, lexer) == NULL)
		return (ft_tokenlstclear(&lexer), -1917);
	if (!new_ast)
		return (ft_close_fd(fd), free(new_token), ft_tokenlstclear(&lexer),
			-1917);
	do_redirections(ast, *env_list);
	*exit_status = launch_ast_recursive(new_ast, env_list, exit_status);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	return (ft_close_fd(fd), ft_free_ast(&new_ast), free(new_token),
		*exit_status);
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
