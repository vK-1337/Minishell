/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:52:17 by udumas            #+#    #+#             */
/*   Updated: 2024/02/09 09:37:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cd (char *path, t_list **env)
{
    char *current_directory;
    int SIZE;

    SIZE = 1024;
    ft_set_pwd(env);
    if (old_pwd_use(&path, env) == 1)
        return (0);
    if (chdir(path) == -1)
    {
        printf("cd: %s: No such file or directory\n", path);
        return (0);
    }
    else
    {
        current_directory = malloc(sizeof (char) * SIZE);
        while (getcwd(current_directory, SIZE) == NULL)
        {
            free(current_directory);
            SIZE = SIZE * 2;
            current_directory = malloc(sizeof (char) * SIZE);
        }
        ft_replace_pwd(env, current_directory);
        free(current_directory);
    }
    return (1);
}

void ft_replace_pwd(t_list **env, char *current_directory)
{
    t_list *pwd;
    t_list *old_pwd;

    old_pwd = ft_find_var(env, "$OLDPWD");
    if (old_pwd == NULL)
    {
        ft_lstadd_back(env, ft_lstnew("OLDPWD", 1));
        old_pwd = ft_find_var(env, "$OLDPWD");
    }
    free(old_pwd->content);
    pwd = ft_find_var(env, "$PWD");
    old_pwd->content = ft_strdup(pwd->content, 1);
    free(pwd->content);
    pwd->content = ft_strdup(current_directory, 1);
}

void ft_set_pwd(t_list **env)
{
    t_list *pwd;
    char *current_directory;
    int SIZE;

    SIZE = 1024;
    pwd = ft_find_var(env, "$PWD");
    if (pwd == NULL)
    {
        ft_lstadd_back(env, ft_lstnew("PWD", 1));
        pwd = ft_find_var(env, "$PWD");
    }
    else
        free(pwd->content);
    current_directory = malloc(sizeof (char) * SIZE);
    while (getcwd(current_directory, SIZE) == NULL)
    {
        free(current_directory);
        SIZE = SIZE * 2;
        current_directory = malloc(sizeof (char) * SIZE);
    }
    pwd->content = ft_strdup(current_directory, 1);
    free(current_directory);
}

int old_pwd_use(char **path, t_list **env)
{
    t_list *old_pwd;
    char *old_pwd_content;

    while (**path == ' ')
        (**path)++;
    if (ft_strncmp(*path, "-", 1) == 0)
    {
        old_pwd = ft_find_var(env, "$OLDPWD");

        if (old_pwd == NULL || old_pwd->content == NULL)
        {
            printf("cd: OLDPWD not set\n");
            return (1);
        }
        else
        {
            old_pwd_content = ft_strdup(old_pwd->content, 1);
            if (ft_cd(old_pwd->content, env) == 1)
                printf("%s\n", old_pwd_content);
            free(old_pwd_content);
            return (1);
        }
    }
    return (0);
}