/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:53:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/06 14:41:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_char_join(char *base_str, char to_join)
{
	size_t	i;
	char	*new_str;

	if (!to_join)
		return (NULL);
	new_str = malloc((ft_strlen(base_str) + 2) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	if (base_str)
	{
		while (base_str[i])
		{
			if (base_str[i + 1] == '$' && ft_not_single_quoted(base_str, i + 1))
				break ;
			new_str[i] = base_str[i];
			i++;
		}
	}
	new_str[i] = to_join;
	new_str[i + 1] = '\0';
	free(base_str);
	return (new_str);
}

char	*ft_join_var(t_list **env, char *final_input, char *input)
{
	char	*new_str;
	t_list	*env_var;

	env_var = ft_find_var(env, input);
	if (env_var->var_name[0] == '?')
	{
		new_str = ft_join_xstatus(final_input, env_var, input);
		if (!new_str)
			return (NULL);
	}
	else
	{
		new_str = ft_join_other_var(final_input, env_var);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

char	*ft_join_other_var(char *final_input, t_list *env_var)
{
	char	*new_str;

	int (i) = 0;
	int (j) = 0;
	new_str = malloc((ft_strlen(final_input) + ft_strlen(env_var->content) + 1)
			* sizeof(char));
	if (!new_str)
		return (NULL);
	if (final_input)
	{
		while (final_input[j])
		{
			new_str[j] = final_input[j];
			j++;
		}
		free(final_input);
	}
	while (env_var->content[i])
	{
		new_str[j] = env_var->content[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	ft_get_join_len(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

char	*ft_join_xstatus(char *final_input, t_list *x_var, char *input)
{
	char	*itoa;
	int		j;
	int		i;
	char	*new_str;
	int		input_len;

	itoa = ft_itoa(x_var->xit_status);
	if (!itoa)
		return (NULL);
	input_len = ft_get_join_len(input);
	new_str = malloc((ft_strlen(final_input) + ft_strlen(itoa)
				+ (ft_strlen(input) - 2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	j = 0;
	if (final_input)
		ft_join_helper(&j, new_str, final_input);
	i = 0;
	ft_join_helper2(itoa, new_str, &i, &j);
	if (input_len > 2)
		ft_join_helper3(input, new_str, &i, &j);
	new_str[j] = '\0';
	return (free(itoa), new_str);
}
