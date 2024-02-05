/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:45:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/05 20:58:33 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define false 0
# define true 1

typedef int	bool;

typedef struct s_parsed_input
{
	char	*cmd;
	char	*cmd_args;
}			t_parsed_input;

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// PROMPT //
char		*ft_extract_hostname(char *session_manager);
char		*trim_pwd(char *pwd);
char		*ft_build_prompt(void);

// ENV CMD //
t_list *ft_convert_env(char **env);
void ft_print_env(t_list *env);
t_list **ft_unset(t_list **env_list, char*var_to_del);

// PARSING //
int			ft_unclosed_input(char *input);
int			ft_not_quoted(char *input, int char_index);
int			ft_not_single_quoted(char *input, int char_index);
int			ft_not_double_quoted(char *input, int char_index);

#endif