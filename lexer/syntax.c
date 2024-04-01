/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:44:19 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/01 13:43:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_syntax_redir(char *input)
{
	int	i;

	i = 0;
	while (ft_is_space(input[i]))
		i++;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			i += ft_go_next(input, i);
		if ((size_t)i > ft_strlen(input))
			break ;
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
		if ((size_t)++i > ft_strlen(input))
			break ;
	}
	return (1);
}

int	ft_rredir_synt_err(char *input, int index, char redir_char)
{
	if (!input[index + 1] || (input[index + 1] == redir_char && !input[index
			+ 2]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ",
			STDERR_FILENO);
		ft_putstr_fd("`newline'\n", STDERR_FILENO);
		return (1);
	}
	if (!input[index + 1] || (input[index + 1] == redir_char && input[index
			+ 2] == redir_char))
	{
		if (input[index + 3] && input[index + 3] == redir_char)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `",
				STDERR_FILENO);
			ft_putchar_fd(redir_char, STDERR_FILENO);
			return (ft_putchar_fd(redir_char, STDERR_FILENO),
				ft_putstr_fd("'\n", STDERR_FILENO), 1);
		}
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `",
				STDERR_FILENO);
		ft_putchar_fd(redir_char, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_syntax_pipes(char *input)
{
	int	i;

	i = 0;
	while (ft_is_space(input[i]))
		i++;
	if (input[i] == '|')
	{
		if (input[i + 1] && input[i + 1] == '|')
			return (ft_print_err_message("||"), 0);
		else
			return (ft_print_err_message("|"), 0);
	}
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			i += ft_go_next(input, i);
		if ((size_t)i > ft_strlen(input))
			break ;
		if (!ft_pipes_synt_error(input, i))
			return (0);
		i++;
		if ((size_t)i > ft_strlen(input))
			break ;
	}
	return (1);
}

int	ft_pipes_synt_error(char *input, int index)
{
	if (!input[index])
		return (1);
	if (input[index] == '|' && !input[index + 1])
	{
		ft_print_err_message("|");
		return (0);
	}
	else if (input[index] == '|' && input[index + 1] == '|' && !input[index
		+ 2])
	{
		ft_print_err_message("||");
		return (0);
	}
	else if (input[index] == '|')
	{
		if (ft_only_spaces_behind(input, index - 1))
		{
			if (input[index + 1] && input[index + 1] == '|')
				return (ft_print_err_message("|"), 0);
			else
				return (ft_print_err_message("||"), 0);
		}
	}
	return (1);
}

int	ft_syntax_parenthesis(char *input)
{
	int	i;
	int	parenthesis;

	parenthesis = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == 40 && ft_not_quoted(input, i))
		{
			if (ft_spaces_parenthesis(&input[i + 1]) == 1)
			{
				ft_print_err_message("(");
				return (0);
			}
			parenthesis++;
		}
		else if (input[i] == 41 && ft_not_quoted(input, i))
			parenthesis--;
		i++;
	}
	if (parenthesis < 0)
		return (ft_print_err_message(")"), 0);
	return (1);
}
