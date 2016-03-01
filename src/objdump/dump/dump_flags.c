/*
** dump_flags.c for  in PSU_2015_nmobjdump/src/objdump/dump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Feb 22 11:22:31 2016 querat_g
** Last update Tue Feb 23 09:33:32 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

static char	*flags_str[] =
  {
    "EXEC_P",
    "HAS_RELOC",
    "HAS_SYMS",
    "DYNAMIC",
    "D_PAGED",
    NULL
  };

static int	flags_mac[8] =
  {
    EXEC_P,
    HAS_RELOC,
    HAS_SYMS,
    DYNAMIC,
    D_PAGED
  };

void		dump_flags(t_fdata *data)
{
  int		i;
  bool		first;

  if (!data)
    return ;
  i = 0;
  first = true;
  while (flags_str[i])
    {
      if ((data->flag & flags_mac[i]))
	{
	  if (!first)
	    printf(", ");
	  printf("%s", flags_str[i]);
	  first = false;
	}
      ++i;
    }
  printf("\n");
}
