/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:45:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/06 14:24:37 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define FALSE 0
# define TRUE 1

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

typedef int	t_bool;

typedef struct s_parsed_input
{
	char	*cmd;
	char	*cmd_args;
}			t_parsed_input;

// PROMPT //
char		*ft_extract_hostname(char *session_manager);
char		*trim_pwd(char *pwd);
char		*ft_build_prompt(void);

// ENV CMD //
t_list		*ft_convert_env(char **env);
void		ft_print_env(t_list *env);

// UNSET CMD //
t_list		**ft_unset(t_list **env_list, char *var_to_del);

// EXPORT CMD //
void		ft_replace_var(t_list **env_list, char *new_var);
int			ft_var_exists(t_list **env_list, char *var);
void		ft_export(t_list **env_list, char *new_var);
int			ft_correct_format(char *new_var);
int			forbidden_char(char c);

// PARSING //
int			ft_unclosed_input(char *input);
int			ft_not_quoted(char *input, int char_index);
int			ft_not_single_quoted(char *input, int char_index);
int			ft_not_double_quoted(char *input, int char_index);

// LST UTILS //
void		ft_free_list(t_list **list);
void		ft_delete_last(t_list *env_node);
void		ft_delete_connect(t_list *env_node);

#endif