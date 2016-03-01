/*
** main.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Feb 16 09:20:51 2016 querat_g
** Last update Tue Feb 23 09:50:00 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include "nmobjdump.h"

bool	objdump(char *path)
{
  t_obj		obj;

  if (!t_obj_const(&obj, path))
    return (false);
  dump_sections_headers_table(&obj);
  t_obj_dest(&obj);
  return (true);
}

int	main(int ac, char **argv)
{
  off_t	i;

  i = 1;
  if (ac < 2)
    return (!objdump("a.out"));
  while (argv[i])
    {
      objdump(argv[i]);
      ++i;
    }
  return (0);
}
