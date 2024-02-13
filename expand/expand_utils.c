/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:53:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/13 10:08:05 by vda-conc         ###   ########.fr       */
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
	int		i;
	int		j;
	int		var_len;
	char	*new_str;
	t_list	*env_var;

	i = 0;
	env_var = ft_find_var(env, input);
	var_len = ft_strlen(env_var->content);
	new_str = malloc((ft_strlen(final_input) + var_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	j = 0;
	if (final_input)
	{
		while (final_input[j])
		{
			new_str[j] = final_input[j];
			j++;
		}
	}
	while (env_var->content[i])
	{
		new_str[j] = env_var->content[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	free(final_input);
	return (new_str);
}

t_list	*ft_find_var(t_list **env, char *input)
{
	int		i;
	t_list	*curr;

	i = 0;
	input++;
	while (input[i])
	{
		if (!ft_isalnum(input[i]))
			break ;
		i++;
	}
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->var_name, input, i) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	ft_print_expandables(int *vars, int vars_number)
{
	int	i;

	i = 0;
	while (i < vars_number)
	{
		printf("\nVariable numero %d => %s\n", i,
			vars[i] == 0 ? "Not expandable" : "Expandable");
		i++;
	}
}
