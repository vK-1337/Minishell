/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:43:24 by udumas            #+#    #+#             */
/*   Updated: 2024/03/08 10:12:20 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *remove_parenthesis(t_token **token);

int	parenthesis(t_ast *ast, t_list *env_list)
{
    t_ast *new_ast;
    int exit_status;
    char *new_token;
    
	new_token = remove_parenthesis(&ast->token);
    create_ast_list(&new_ast, ft_lexer(new_token, &env_list));
    if (!new_ast)
    {
        printf("Memory error\n");
        return (-1);
    }
    exit_status = launch_ast_recursive(new_ast, env_list);
    ft_free_ast(new_ast);
    return (exit_status);
}

char 	*remove_parenthesis(t_token **token)
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
