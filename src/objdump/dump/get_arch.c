/*
** get_arch.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Feb 21 11:48:18 2016 querat_g
** Last update Mon Feb 22 15:54:14 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

static char	s_tab[8][64] =
  {
    "x386",
    "x860",
    "x960",
    "arm",
    "x86-64",
    ""
  };

static int	m_tab[8] =
  {
    3,
    7,
    19,
    40,
    62,
    -1
  };

char		*get_arch(t_obj *obj)
{
  int		i;

  if (!obj)
    return (NULL);
  i = 0;
  while (s_tab[i])
    {
      if (obj->head.e_machine == m_tab[i])
	return (strdup(s_tab[i]));
      ++i;
    }
  return (NULL);
}

bool		fdata_get_arch(t_fdata *data, t_obj *obj)
{
  if (!data || !obj)
    return (false);
  data->arch = NULL;
  data->arch = get_arch(obj);
  if (!data->arch)
    return (false);
  return (true);
}
