/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:34:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/10 11:43:27 by vda-conc         ###   ########.fr       */
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
