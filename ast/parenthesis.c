/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:43:24 by udumas            #+#    #+#             */
/*   Updated: 2024/03/08 09:46:14 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_parenthesis(t_token **token);

int	parenthesis(t_ast *ast, t_list *env_list)
{
    t_ast *new_ast;
    int exit_status;
	remove_parenthesis(&ast->token);
    printf("parenthesis: %s\n", ast->token->token);
    create_ast_list(&new_ast, ft_lexer(ast->token->token, &env_list));
    if (!new_ast)
    {
        printf("Memory error\n");
        return (-1);
    }
    read_ast(new_ast, 0);
    exit_status = launch_ast_recursive(new_ast, env_list);
    ft_free_ast(new_ast);
    return (exit_status);
}

void	remove_parenthesis(t_token **token)
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
	free((*token)->token);
	(*token)->token = new_token;
}
