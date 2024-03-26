/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:45:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/03/26 13:59:52 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SIZE 4096
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   STRUCT                                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

typedef struct s_token
{
	t_ttype			type;
	char			*token;
	char			*file_redir;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*file_redir_in;
	struct s_token	*file_redir_out;
	int				order;
}					t_token;

typedef struct s_ast
{
	t_token			*token;

	struct s_ast	*daddy;
	struct s_ast	*right;
	struct s_ast	*left;
	int				here_doc;
}					t_ast;

typedef struct s_exec
{
	int				fd[2];
	int				saved_fd[2];
	int				last;
}					t_exec;

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   CD                                       */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_cd(char *path, t_list **env);
int					ft_replace_pwd(t_list **env);
int					ft_set_pwd(t_list **env);
int					old_pwd_use(char *path, t_list **env);
int					back_home(char *path, t_list **env);
int					cdpath_find(char *path, t_list **env);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 DEBUG                                      */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void				ft_print_expandables(int *vars, int vars_number);
int					ft_count_tokens(char const *s);
char				**ft_token_split(char const *s);
void				ft_add_token(char *element, const char *src, size_t index,
						size_t len);
int					ft_tokenlen(const char *str, int index);
void				ft_print_tokens(char **tokens);
int					ft_is_separator(char c);
int					ft_is_operator(char c);
int					ft_go_next(const char *str, int index);
t_ttype				ft_define_ttype(char *token, char *previous_token);
char				*ft_print_type(t_ttype type);
int					ft_is_option(char *token);
int					ft_is_file(char *token);
void				ft_print_list(t_list **env_list);
int					ft_tablen(char **tab);
void				ft_print_tab(char **tokens);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 ECHO                                       */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_echo(char **str, char *brut_input, t_ast *ast);
int					ft_is_n_option(char *str);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                  ENV                                       */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_list				*ft_convert_env(char **env);
int					ft_print_env(t_list *env);
t_list				*ft_exit_variable(void);
void				ft_update_xstatus(t_list **env, int x_status);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   EXEC                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					exec_shell_command(t_ast *command, t_list **env_list,
						char **env, t_ast *ast);
char				*add_slash(char *cmd1);
void				ft_free_char_tab(char **str);
char				**redo_env(t_list *env);
int					exec_command(char **command, char **env, t_list **env_list,
						t_ast *ast);
int					do_redirections(t_ast *command, int saved_std[2]);
int					configure_fd_out(int fd_out, char *token, char *file);
int					configure_fd_in(int fd_in, char *token, char *file);
int					launch_here_doc(char *limiter, int saved_std[2]);
void				here_doc(char *limiter, int fd[2]);
char				*check_valid_command(char **cmd_split, char *path);
char				*take_path(char **env);
void				ft_add_front(t_token **command, t_token **curr);
int					manage_built_in(char **command, t_list **env_list,
						char *brut_input, t_ast *ast);
int					exec_built_in(char **command, t_list **env_list,
						char *brut_input, t_ast *ast);
void				ft_close_fd(int fd[2]);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   EXIT                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_exit(char **command, t_list **env_list);
int					ft_isnumber(char *str);
void				ft_end_minishell(t_list **env_list);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 EXPAND                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_contain_variables(char *input);
int					*ft_is_expandable(char *input, int variable_count);
int					ft_decr_incr(int condition);
int					ft_should_expand(int single_quotes, int double_quotes);
void				ft_testing_expand(char *input);
char				*ft_char_join(char *base_str, char to_join);
t_list				*ft_find_var(t_list **env, char *input);
char				*ft_join_var(t_list **env, char *final_input, char *input);
char				*ft_expand(char *input, t_list **env);
char				*ft_join_xstatus(char *final_input, t_list *x_var,
						char *input);
char				*ft_join_other_var(char *final_input, t_list *env_var);
void				ft_join_helper(int *j, char *new_str, char *final_input);
void				ft_expand_helper1(t_norme *vars, char *input, t_list **env);
void				ft_expand_helper2(t_norme *vars, char *input, t_list **env);
void				is_expandable_helper(t_norme *vars, char *input);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                  EXPORT                                    */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void				ft_is_prev_greaterforbidden_char(char c);
void				ft_display_export(t_list **env_list);
t_list				*ft_copy_env_node(t_list *env_node);
int					ft_is_prev_greater(char *curr_var, char *prev_var);
void				ft_swapback_nodes(t_list *prev, t_list *curr);
t_list				**ft_sort_nodes(t_list **env_list);
t_list				**ft_copy_env_list(t_list **env_list);
void				ft_replace_var(t_list **env_list, char *new_var);
int					ft_var_exists(t_list **env_list, char *var);
int					ft_export(t_list **env_list, char *new_var);
int					ft_correct_format(char *new_var);
int					ft_forbidden_char(char c);
int					ft_contain_equal(char *new_var);
void				ft_expand_helper1(t_norme *vars, char *input, t_list **env);
void				ft_expand_helper2(t_norme *vars, char *input, t_list **env);
void				is_expandable_helper(t_norme *vars, char *input);
int					ft_before_equal(char *new_var, int i);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                             INPUT TREATMENT                                */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_unclosed_input(char *input);
void				ft_unclosed_input_helper(t_norme *vars);
int					ft_not_quoted(char *input, int char_index);
int					ft_not_single_quoted(char *input, int char_index);
int					ft_not_double_quoted(char *input, int char_index);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                  LEXER                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_token				*ft_lexer(char *input, t_list **env);
int					ft_count_tokens(char const *s);
char				**ft_token_split(char const *s);
void				ft_add_token(char *element, const char *src, size_t index,
						size_t len);
int					ft_tokenlen(const char *str, int index);
void				ft_print_tokens(char **tokens);
int					ft_is_separator(char c);
int					ft_is_operator(char c);
int					ft_go_next(const char *str, int index);
int					ft_go_next_parenthesis(const char *str, int index);
t_token				*ft_convert_tokens(char **tokens, t_list **env);
int					ft_empty_expand(char *token, t_list **env);
t_ttype				ft_define_ttype(char *token, char *previous_token);
char				*ft_print_type(t_ttype type);
int					ft_is_option(char *token);
int					ft_is_file(char *token);
void				*ft_reunite_tokens(t_token **tokens);
void				*ft_join_options(t_token **tokens, t_token *curr,
						t_token *next);
void				ft_join_file_path(t_token *curr, t_token *next);
void				*ft_join_export(t_token **tokens, t_token *curr,
						t_token *next);
void				ft_reunite_redirection(t_token **tokens);
void				ft_initialize_redirection(t_token **tokens);
int					ft_redirections(t_token **listed_tokens, t_list *env);
int					ft_open_solo_fd(t_token **tokens, t_list *env);
t_token				*ft_clean_tokens(t_token **tokens);
int					file_redir(t_token *token);
int					ft_open_fd(t_token **tokens);
int					check_only_operator(t_token **tokens);
void				ft_clean_operator(t_token **tokens);
void				update_token_link(t_token *curr);
int					handle_fd(t_token *curr, t_token **tokens);
void				ft_front(t_token **command);
void				ft_back(t_token **command);
t_token				*ft_handle_operator_path_file(t_token **tokens,
						t_token *curr, t_token *next);
t_token				*ft_handle_option(t_token **tokens, t_token *curr,
						t_token *next);
t_token				*ft_handle_command_export(t_token **tokens, t_token *curr);
t_token				*ft_handle_next_token(t_token **tokens, t_token *curr,
						t_token *next);
int					ft_check_first_redir(char **tokens, t_ttype *type);
t_ttype				ft_define_first_token_type(char **tokens,
						int first_type_redir, t_ttype type);
t_ttype				ft_define_subsequent_token_type(char **tokens, int i,
						int first_type_redir, t_ttype previous_type);
int					ft_only_spaces_between(char *token);
int					ft_token_empty(char *token);
int					ft_contain_quotes(char *token);
int					ft_count_quotes(char *input);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                  SYNTAX                                    */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					check_syntax(char *input);
int					ft_syntax_parenthesis(char *input);
int					ft_only_spaces(char *input);
int					ft_is_space(char c);
int					ft_only_spaces_behind(char *input, int index);
int					ft_syntax_pipes(char *input);
int					ft_syntax_redir(char *input);
int					ft_pipes_synt_error(char *input, int index);
int					ft_rredir_synt_err(char *input, int index, char redir_char);
int					ft_spaces_parenthesis(char *str);
int					ft_syntax_parenthesis(char *input);
int					ft_not_quoted(char *input, int char_index);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 LST UTILS                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void				ft_free_list(t_list **list);
void				ft_delete_last(t_list *env_node);
void				ft_delete_connect(t_list *env_node);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                  PROMPT                                    */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

char				*ft_extract_hostname(char *session_manager);
char				*trim_pwd(char *pwd);
char				*ft_build_prompt(t_list **env);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   PWD                                      */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_pwd(void);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 SIGNALS                                    */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void				ft_init_signals(void);
void				ft_change_signals(void);
void				sig_handler(int signum);
void				wait_p_handler(int signum);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                             TOKEN LST UTILS                                */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void				ft_tokenlstclear(t_token **lst);
void				ft_tokenlstadd_back(t_token **lst, t_token *new);
void				ft_tokenlstadd_front(t_token **lst, t_token *new);
void				ft_tokenlstdelone(t_token **lst);
void				ft_tokenlstiter(t_token *lst, void (*f)(void *));
t_token				*ft_tokenlstlast(t_token *lst);
t_token				*ft_tokenlstmap(t_token *lst, void *(*f)(void *),
						void (*del)(void *));
t_token				*ft_tokenlstnew(void *content, t_ttype type);
int					ft_tokenlstsize(t_list *lst);
void				ft_print_token_list(t_token **tokens);
int					handle_quotes(const char *str, int index, int delimiter);
int					handle_parentheses(const char *str, int index);
int					handle_non_space_delimiter(const char *str, int index,
						int delimiter);
int					handle_space_delimiter(const char *str, int index,
						int delimiter);
void				ft_handle_brackets(int *i, char *input, t_list **env,
						char **final_input);
int					determine_return_value(int delimiter, int i);
void				ft_helper1(int *i, int *count, char const *s);
void				ft_helper2(int *i, int *count, char const *s);
void				ft_helper3(int *i, int *count, char const *s);
void				ft_helper4(int *i, int *count);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                  UNSET                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_unset(t_list **env_list, char *var_to_del);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 WILDCARD                                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					ft_contain_wildcards(char *input);
int					ft_decr_incr(int condition);
int					ft_pattern_match(char *pattern, char *name);
int					ft_starting_match(char *pattern, char *name);
int					ft_ending_match(char *pattern, char *name);
int					ft_both_match(char *pattern, char *name);
size_t				ft_strlen(const char *str);
int					ft_next_char_found(char pattern_char, char *name);
int					ft_match_multiple_wc(char *pattern, char *name);
int					ft_match_single_wc(char *pattern, char *name);
int					ft_replace_wildcards(char **token);
char				*ft_join_match_helper(char *prev_new_token, char *de_name,
						int count, int total_count);
void				ft_trim_quotes(char **input);
int					ft_count_matches(char **token, int (*ft_match)(char *,
							char *));

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                 AST                                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void				*create_ast_list(t_ast **node, t_token *token_list);
void				read_ast(t_ast *node, int depth);
int					is(char *token, char *comp);
void				ft_free_ast(t_ast **ast);
int					launch_ast(char *input, t_list **env_list,
						int *exit_status);
int					launch_ast_recursive(t_ast *ast, t_list **env_list,
						int *exit_status);
int					create_redirection(t_ast *node, t_list **env_list);
char				*build_command(t_ast *node);
int					right_pipe(t_ast *node, t_list **env_list, t_exec **exec);
int					left_pipe(t_ast *node, t_list **env_list, t_exec **exec);
int					pipe_chain(char **env, t_ast *command, t_list **env_list,
						t_exec **exec);
void				handle_error(int err, char *msg);
void				parenthesis(t_ast *ast, t_list **env_list,
						int *exit_status);
int					file_redir(t_token *token);
t_token				*get_last_strongest_operator(t_token *token_list);
void				send_to_build(t_ast **node, int direction);
t_token				*get_first_strongest_operator(t_token *token_list);
t_ast				*build_tree(t_ast **node, t_token *strongest);
t_ast				*init_branch(t_ast *parent, t_token *token, int is_left);
int					do_pipe_redirections(t_ast *command, t_exec **exec);
void				export_and_wildcard(t_ast *ast, t_list *env_list);
int					last_pipe(char **env, t_ast *command, t_list **env_list,
						t_exec **exec);
void				export_and_wc_helper(t_token *travel, t_list *env_list);
void				export_and_wc_helper2(t_token *travel, t_list *env_list);

#endif