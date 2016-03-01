/*
** main.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Feb 16 09:20:51 2016 querat_g
** Last update Sun Feb 28 16:08:46 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"
#include "list.h"

bool	push_sym_to_list(t_obj *obj, Elf64_Sym *sym, char flag)
{
  t_sym	*my_sym;

  my_sym = calloc(1, sizeof(t_sym));
  if (!my_sym)
    return (false);
  my_sym->flag = flag;
  if (sym->st_shndx < obj->head.e_shnum)
    my_sym->addr = sym->st_value;
  my_sym->name = safe_str_get(obj, sym->st_name);
  if (!my_sym->name)
    return (free(my_sym), false);
  if (!obj->symlist->prepend(&obj->symlist, my_sym))
    return (false);
  return (true);
}

bool	fill_sym_list(t_obj *obj)
{
  Elf64_Sym	*cur;
  t_sect	*sect;
  size_t	symoff;
  char		flag;

  if (!(obj->symlist = new_list()))
    return (false);
  sect = get_t_sect(obj, ".symtab");
  symoff = 0;
  while ((cur = get_next_sym(sect, &symoff)))
    {
      if (cur->st_name)
	{
	  flag = get_flag(obj, cur);
	  if (!push_sym_to_list(obj, cur, flag))
	    return (obj->symlist->destruct(&obj->symlist, &t_sym_dest), false);
	}
      free(cur);
    }
  return (true);
}

bool	nm_core(t_obj *obj)
{
  if (!fill_sym_list(obj))
    return (false);

  obj->symlist->sort(obj->symlist, &t_sym_cmp);
  obj->symlist->print(obj->symlist, &t_sym_print);
  obj->symlist->destruct(&obj->symlist, &t_sym_dest);

  return (true);
}

bool	nm(char *path)
{
  t_obj		obj;
  bool		status;

  if (!t_obj_const(&obj, path))
    return (false);

  if (!set_sym_tables_into_t_obj(&obj))
    {
      dprintf(2, "nm: %s: no symbols\n", (obj.path) ? obj.path : "");
      t_obj_dest(&obj);
      return (false);
    }

  status = nm_core(&obj);

  t_obj_dest(&obj);
  return (status);
}

int	main(int ac, char **argv)
{
  off_t	i;

  i = 1;
  if (ac < 2)
    return (!nm("a.out"));
  if (ac < 3)
    return (!nm(argv[1]));
  while (argv[i])
    {
      printf("\n%s:\n", argv[i]);
      nm(argv[i]);
      ++i;
    }
  return (0);
}
