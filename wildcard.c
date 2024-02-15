/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:45:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/15 20:28:58 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "/home/vda-conc/Documents/Projects/Minishell/minishell.h"
int	ft_contain_wildcards(char *input);
int	ft_decr_incr(int condition);
int ft_pattern_match(char *pattern, char *name);
int ft_starting_match(char *pattern, char *name);
int ft_ending_match(char *pattern, char *name);
int ft_both_match(char *pattern, char *name);
size_t	ft_strlen(const char *str);

// ! GERER LE CAS QUAND ON A PAR EXEMPLE *c*.c

int	main(int ac, char**av)
{
	struct dirent	*de;
	DIR				*dr;

    (void)ac;
	dr = opendir(".");
	if (dr == NULL)
	{
		printf("Could not open current directory");
		return (0);
	}
	while ((de = readdir(dr)) != NULL)
    {
        if (ft_pattern_match(av[1], de->d_name))
		    printf("%s ", de->d_name);
    }
	closedir(dr);
	return (0);
}

int	ft_contain_wildcards(char *input)
{
	int i;
	int single_quotes;
	int double_quotes;

	i = 0;
	single_quotes = 0;
	single_quotes = 0;
	while (input[i])
	{
		if (input[i] == 34)
            single_quotes += ft_decr_incr(single_quotes);
		if (input[i] == 39)
            double_quotes += ft_decr_incr(double_quotes);
		if (input[i] == 42 && !double_quotes && !single_quotes)
			return (1);
        i++;
	}
    return (0);
}

int ft_pattern_match(char *pattern, char *name)
{
    int wildcard_index;
    int patt_len;
    int after_wild;

    patt_len = ft_strlen(pattern);
    wildcard_index = 0;
    while (pattern[wildcard_index] != 42)
        wildcard_index++;
    after_wild = patt_len - wildcard_index;
    if (wildcard_index == (ft_strlen(pattern) - 1))
            return (ft_starting_match(pattern, name));
    else if (wildcard_index == 0)
            return (ft_ending_match(pattern, name));
    else
            return (ft_both_match(pattern, name));
}

int ft_starting_match(char *pattern, char *name)
{
    int i;

    i = 0;
    if (name[0] == '.')
        return (0);
    while (pattern[i] != '*' && name[i])
    {
        if (pattern[i] != name[i])
            return (0);
        i++;
    }
    return (1);
}

int ft_ending_match(char *pattern, char *name)
{
    int patt_len;
    int name_len;

    name_len = ft_strlen(name) - 1;
    patt_len = ft_strlen(pattern) - 1;
    if (name[0] == '.')
        return (0);
    while (pattern[patt_len] != '*' && name[name_len])
    {
        if (pattern[patt_len] != name[name_len])
            return (0);
        patt_len--;
        name_len--;
    }
    return (1);
}

int ft_both_match(char *pattern, char *name)
{
    if (ft_starting_match(pattern, name) && ft_ending_match(pattern, name))
        return (1);
    return (0);
}

int	ft_decr_incr(int condition)
{
	if (condition == 1)
		return (-1);
	else if (condition == 0)
		return (1);
	return (1337);
}
// ! GERER LE CAS QUAND ON A PAR EXEMPLE *c*.c

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}