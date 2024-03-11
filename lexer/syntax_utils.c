/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 02:36:32 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/11 20:37:23 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_space(char c)
{
	if ((c >= 8 && c <= 11) || c == 32)
		return (1);
	return (0);
}

int	ft_only_spaces_behind(char *input, int index)
{
	int	i;

	i = index;
	if (input[i + 1] == input[i])
		i--;
	while (i > 0 && ft_is_space(input[i]))
		i--;
	if (ft_is_operator(input[i]))
		return (1);
	return (0);
}

int	ft_spaces_parenthesis(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ')')
	{
		if (!ft_is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
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