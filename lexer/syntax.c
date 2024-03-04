/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:21:00 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/04 11:38:58 by vda-conc         ###   ########.fr       */
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
    while (input[i])
    {
        if (input[i] == '>')
        {
            if (ft_rredir_synt_err(input, i, '>'))
                return (0);
        }
        else if (input[i] == '<')
        {
            if (ft_rredir_synt_err(input, i, '<'))
                return (0);
        }
        i++;
    }
    return (1);
}

int ft_rredir_synt_err(char *input, int index, char redir_char)
{
    if (!input[index + 1] || (input[index + 1] == redir_char && !input[index + 2]))
            return (printf("minishell: syntax error near unexpected token `newline'\n"), 1);
    if (!input[index + 1] || (input[index + 1] == redir_char && input[index + 2] == redir_char))
    {
        if (input[index + 3] && input[index + 3] == redir_char)
            return (printf("minishell: syntax error near unexpected token `%c%c'\n", redir_char, redir_char), 1);
        else
            return (printf("minishell: syntax error near unexpected token `%c'\n", redir_char), 1);
    }
    return (0);
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
        if (!ft_pipes_synt_error(input, i))
            return (0);
        i++;
    }
    return (1);
}

int ft_pipes_synt_error(char *input, int index)
{
    if (input[index] == '|' && !input[index + 1])
            return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
    else if (input[index] == '|' && input[index + 1] == '|' && !input[index + 2])
        return (printf("minishell: syntax error near unexpected token `||'\n"), 0);
    else if (input[index] == '|')
    {
        if (ft_only_spaces_behind(input, index - 1))
        {
            if (input[index + 1] && input[index + 1] == '|')
                return (printf("minishell: syntax error near unexpected token `||'\n"), 0);
            else
                return (printf("minishell: syntax error near unexpected token `|'\n"), 0);
        }
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
        {
            if (ft_spaces_parenthesis(input[i + 1]) == 1)
                return (printf("minishell: syntax error near unexpected token `('\n"), 0);
            parenthesis++;
        }
		else if (input[i] == 41 && ft_not_quoted(input, i))
			parenthesis--;
		i++;
	}
	if (parenthesis < 0)
		return (printf("minishell: syntax error near unexpected token `)'\n"), 0);
	return (1);
}

int ft_spaces_parenthesis(char *str)    
{
    int i;

    i = 0;
    while (str[i] != ')')
    {
        if (!ft_is_space(str[i]))
            return (0);
        i++;
    }
    return (1);
}