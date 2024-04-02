/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:58:48 by vda-conc          #+#    #+#             */
/*   Updated: 2024/04/02 16:03:57 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_list **env_list, char **vars)
{
	t_norme	t_vars;

	t_vars.j = 0;
	t_vars.i = 1;
	if (!env_list)
		return (1);
	if (!vars[1])
		return (ft_display_export(env_list), 1);
	while (vars[t_vars.i])
	{
		if (ft_correct_format(vars[t_vars.i]))
		{
			if (ft_var_exists(env_list, vars[t_vars.i]))
				ft_replace_var(env_list, vars[t_vars.i]);
			else if (ft_contain_equal(vars[t_vars.i]))
				ft_lstadd_back(env_list, ft_lstnew(vars[t_vars.i], 1, 1));
			else
				ft_lstadd_back(env_list, ft_lstnew(vars[t_vars.i], 1, 0));
		}
		else
			t_vars.j = 1;
		t_vars.i++;
	}
	ft_free_char_tab(vars);
	return (t_vars.j);
}

int	ft_contain_equal(char *new_var)
{
	int	i;

	i = 0;
	if (!new_var)
		return (0);
	while (new_var[i])
	{
		if (new_var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_correct_format(char *new_var)
{
	int	i;

	i = 0;
	if (!new_var)
		return (0);
	if (!(ft_isalpha(new_var[i])) && new_var[i] != '_')
	{
		ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	while (new_var[i])
	{
		if (ft_forbidden_char(new_var[i]) && ft_before_equal(new_var, i))
		{
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_before_equal(char *new_var, int i)
{
	while (i)
	{
		if (new_var[i] == '=')
			return (0);
		i--;
	}
	return (1);
}

int	ft_forbidden_char(char c)
{
	int		i;
	char	*charset;

	i = 0;
	charset = "!@#$%^&*(){}[]|;:<>,?/-";
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	**ft_export_input(char *input)
{
	char	**vars;
	char	**final_vars;
	int		total_vars;
	int		i;
    int     j;

	i = 1;
    j = 1;
	vars = ft_split(input, ' ');
	total_vars = ft_count_vars(vars);
    printf("total_vars = %d\n", total_vars);
	final_vars = malloc((total_vars + 3) * sizeof(char *));
	if (!vars)
		return (NULL);
    final_vars[0] = ft_strdup(vars[0]);
	while (vars[i])
	{
		final_vars[j] = ft_strdup(vars[i]);
		if (vars[i + 1] && !ft_contain_equal(vars[i + 1]))
		{
			final_vars[j] = ft_strjoin(final_vars[j], " ", 1);
			final_vars[j] = ft_strjoin(final_vars[j], vars[i + 1], 1);
            i++;
		}
        j++;
		i++;
	}
    printf("i = %d\n", i);
    printf("j = %d\n", j);
	final_vars[j] = NULL;
    ft_free_char_tab(vars);
	return (final_vars);
}

int	ft_count_vars(char **vars)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (vars[i])
	{
		if (ft_contain_equal(vars[i]))
			j++;
		i++;
	}
	return (j);
}