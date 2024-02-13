/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:17:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/02/13 10:08:46 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ! FOR ECHO WE WILL NEED TO HANDLE -N OPTION.
// ! THAT IMPLICATES TO HANDLE -N INSIDE ARGUMENT
// ? What is the behavior of echo -n "hello" ?
// * It should not print a new line after "hello"


// ? What is the behavior of echo when -nnnnnnnnnn is passed as argument ?
// ? Or multiple -n -n -n -n -n are passed as arguments ?
// * It should print the string as usual, but not print a new line at the end.
// * No matter how many -n are passed the behavior should be the same as if only one -n was passed.

ft_echo(char *str)
{
  printf("%s\n", str);
}
// ft_trim_echo_args(char *args)
// {

// }

int ft_detect_n_option(char *args)
{
  int i;

  i = 0;
  while (args[i])
  {
    if (args[i] != '-' && args[i] != 110 && args[i] != ' ')
      break;
    if (args[i] == '-' && args[i + 1] == 110)
      return (1);
    i++;
  }
  return (0);
}
