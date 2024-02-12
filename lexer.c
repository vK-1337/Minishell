/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:34:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/12 17:53:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_lexer(char *input, t_list **env)
{
  char *expanded_input;
  char **tokens;
  t_list *listed_tokens;

  expanded_input = ft_expand(input, env);
  tokens = ft_token_split(expanded_input);
  ft_print_tokens(tokens);
  listed_tokens = ft_convert_tokens(tokens);
  return (NULL);
}

t_list *ft_convert_tokens(char **tokens)
{
  int i;
  t_ttype type;
  char *previous_token;
  t_ttype previous_type;

  i = 0;
  previous_token = NULL;
  while (tokens[i])
  {
    if (i == 0)
    {
      if (tokens[i] && tokens[i][0] && !ft_is_operator(tokens[i][0]))
        type = COMMAND;
    }
    else
      type = ft_define_ttype(tokens[i], previous_token);
    printf("Type du token numero |%d| qui contient |%s| => |%s|\n", i + 1, tokens[i], ft_print_type(type));
    previous_token = tokens[i];
    previous_type = type;
    i++;
  }
  return (NULL);
}

t_ttype ft_define_ttype(char *token, char* previous_token)
{
  int i;
  int j;

  i = 0;
  j = 0;
  if (!token)
    return (0);
  if (ft_is_operator(token[i]))
    return (OPERATOR);
  if (token[i] == 34 || token[i] == 39)
    i++;
  if (ft_is_option(token))
    return (OPTION);
  if (previous_token)
  {
    if (previous_token[j] == 34 || previous_token[j] == 39)
      j++;
    if (previous_token[j] == '>' || previous_token[j] == '<')
      return (PATH_FILE);
    if (previous_token[j] == 38 || previous_token[j] == 124)
      return (COMMAND);
  }
  return (CMD_ARG);
}

int ft_is_file(char *token)
{
  int i;

  i = 0;
  while (token[i])
  {
    if(token[i] == '.')
      return (1);
    i++;
  }
  return (0);
}

int ft_is_option(char *token)
{
  int i;

  i = 0;
  if (token[0] != '-')
    return (0);
  else
    i++;
  while (token[i])
  {
    if (!ft_isalnum(token[i]))
      return (0);
    i++;
  }
  return (1);
}
int ft_is_operator(char c)
{
  if (c == 38 || c == 60 || c == 62 || c == 124)
    return (1);
  return (0);
}

char *ft_print_type(t_ttype type)
{
  if (type == COMMAND)
    return ("Command");
  if (type == OPTION)
    return ("Option");
  if (type == CMD_ARG)
    return ("command arg");
  if (type == OPERATOR)
    return ("Operator");
  if (type == PATH_FILE)
    return ("Path file");
  return ("1337");
}