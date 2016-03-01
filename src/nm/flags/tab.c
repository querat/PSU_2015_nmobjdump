/*
** tab_functions1.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 24 17:17:53 2016 querat_g
** Last update Fri Feb 26 15:57:02 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

static char	(*functab[16])(t_obj*, Elf64_Sym*) =
{
  &w_flag,
  &d_maj_flag,
  &u_min_flag,
  &t_maj_flag,
  &r_maj_flag,
  &v_flag,
  &u_maj_flag,
  &a_maj_flag,
  &c_maj_flag,
  &b_maj_flag,
  &unknown_flag,
  NULL
};

char	lower_case(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (c + 32);
  return (c);
}

char	get_flag(t_obj *obj, Elf64_Sym *sym)
{
  int	i;
  char	c;

  if (!obj || !obj->sect || !sym)
    return (' ');

  i = 0;
  while (functab[i])
    {
      if ((c = (functab[i])(obj, sym)))
	{
	  if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
	    return (lower_case(c));
	  return (c);
	}
      i++;
    }
  return (' ');
}

char		unknown_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  (void)sym;
  return ('n');
}
