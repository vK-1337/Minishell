/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:21:00 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/29 14:15:54 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(char *input)
{
	if (ft_only_spaces(input))
		return (0);
	if (!ft_syntax_parenthesis(input))
		return (0);
	if (!ft_syntax_pipes(input))
	    return (0);
	if (!ft_syntax_redir(input))
	    return (0);
    return (1);
}

int ft_syntax_redir(char *input)
{
    int i;

    i = 0;
    while (ft_is_space(input[i]))
        i++;
    if (input[i] == '>')
    {
        if (!input[i + 1] || (input[i + 1] == '>' && !input[i + 2]))
            return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
    }
    else if (input[i] == '<')
    {
        if (!input[i + 1] || (input[i + 1] == '<' && !input[i + 2]))
            return (printf("minishell: syntax error near unexpected token `newline'\n"), 0);
    }
    return (1);
}

int ft_syntax_pipes(char *input)
{
    int i;

    i = 0;
    while (ft_is_space(input[i]))
        i++;
    if (input[i] == '|')
    {
        if (input[i + 1] && input[i + 1] == '|')
            return (printf("minishell: syntax error near unexpected token `||'\n"), 0);
        else
            return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
    }
    while (input[i])
    {
        if (input[i] == '|' && !input[i + 1])
            return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
        else if (input[i] == '|' && input[i + 1] == '|' && !input[i + 2])
            return (printf("minishell: syntax error near unexpected token `||'\n"), 0);
        else if (input[i] == '|')
        {
            if (ft_only_spaces_behind(input, i - 1))
            {
                if (input[i + 1] && input[i + 1] == '|')
                    return (printf("minishell: syntax error near unexpected token `||'\n"), 0);
                else
                    return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
            }
        }
        i++;
    }
    return (1);
}

int ft_only_spaces_behind(char *input, int index)
{
    int i;

    i = index;
    if (input[i + 1] == input[i])
        i--;
    while (i > 0 && ft_is_space(input[i]))
        i--;
    if (ft_is_operator(input[i]))
        return (1);
    return (0);
}

int ft_is_space(char c)
{
    if ((c >= 8 && c <= 11) || c == 32)
        return (1);
    return (0);
}

int	ft_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '\b' && input[i] != '\t' && input[i] != '\n'
			&& input[i] != '\v' && input[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	ft_syntax_parenthesis(char *input)
{
	int i;
	int parenthesis;
	parenthesis = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == 40 && ft_not_quoted(input, i))
			parenthesis++;
		else if (input[i] == 41 && ft_not_quoted(input, i))
			parenthesis--;
		i++;
	}
	if (parenthesis < 0)
		return (printf("minishell: syntax error near unexpected token `)'\n"), 0);
	return (1);
}