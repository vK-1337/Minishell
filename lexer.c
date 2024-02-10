/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:34:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/10 14:05:33 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_lexer(char *input, t_list **env)
{
  char *expanded_input;
  char **tokens;
  // t_list *listed_tokens;

  expanded_input = ft_expand(input, env);
  tokens = ft_token_split(expanded_input);
  free(expanded_input);
  ft_print_tokens(tokens);
  // listed_tokens = ft_convert_tokens(tokens);
  return (NULL);
}

// t_list *ft_convert_tokens(char **tokens)
// {
//   // todo Iterate through all tokens
//   // todo put the content inside token_node->content
//   // todo token_node.type = ft_define_ttype(node.content)
//   // todo do it again.
// }