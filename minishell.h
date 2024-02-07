/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:45:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/07 15:50:21 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define FALSE 0
# define TRUE 1
# define SIZE 150
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

// EXPAND //
int ft_contain_variables(char *input);
int *ft_is_expandable(char *input, int variable_count);
int ft_decr_incr(int condition);
int ft_should_expand(int single_quotes, int double_quotes);
void ft_testing_expand(char *input);
char *ft_char_join(char *base_str, char to_join);
t_list *ft_find_var(t_list **env, char* input);
char *ft_join_var(t_list **env, char *final_input, char *input);
char *ft_expand(char *input, t_list **env);

// CD CMD //
void change_directory(char **path, char *command);

// DEBUG //
void ft_print_expandables(int *vars, int vars_number);

#endif