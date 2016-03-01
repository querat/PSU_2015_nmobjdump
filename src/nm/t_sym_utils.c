/*
** t_sym_utils.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Feb 28 16:12:39 2016 querat_g
** Last update Sun Feb 28 16:14:38 2016 querat_g
*/

#include <stdlib.h>
#include "nmobjdump.h"

char	*skip_underscores(char *str)
{
  if (!str)
    return (NULL);

  while ((*str) && (*str) == '_')
    ++str;

  return (str);
}

int	count_underscores(char *str)
{
  int		count;

  count = 0;
  if (!str)
    return (0);
  while ((*str) && (*str) == '_')
    {
      ++str;
      ++count;
    }
  return (count);
}
