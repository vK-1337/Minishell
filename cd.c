/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:37:38 by udumas            #+#    #+#             */
/*   Updated: 2024/02/07 16:15:27 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_directory(char **prompt, char *command)
{
    char *current_directory;

    current_directory = malloc(sizeof(char) * SIZE);
    command = command + 2;
    while (*command == ' ')
        command++;
    if (chdir(command) == -1)
        printf("cd: %s: No such file or directory\n", command);
    else
    {
        free(*prompt);
        getcwd(current_directory, SIZE);
        printf("%s\n", current_directory);
        *prompt = ft_build_prompt();
    }
    return ;
}